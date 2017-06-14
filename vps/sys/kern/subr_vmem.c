/*-
 * Copyright (c)2006,2007,2008,2009 YAMAMOTO Takashi,
 * Copyright (c) 2013 EMC Corp.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * From:
 *	$NetBSD: vmem_impl.h,v 1.2 2013/01/29 21:26:24 para Exp $
 *	$NetBSD: subr_vmem.c,v 1.83 2013/03/06 11:20:10 yamt Exp $
 */

/*
 * reference:
 * -	Magazines and Vmem: Extending the Slab Allocator
 *	to Many CPUs and Arbitrary Resources
 *	http://www.usenix.org/event/usenix01/bonwick.html
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD: projects/vps/sys/kern/subr_vmem.c 257008 2013-10-23 19:02:26Z will $");

#include "opt_ddb.h"

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/queue.h>
#include <sys/callout.h>
#include <sys/hash.h>
#include <sys/lock.h>
#include <sys/malloc.h>
#include <sys/mutex.h>
#include <sys/smp.h>
#include <sys/condvar.h>
#include <sys/taskqueue.h>
#include <sys/vmem.h>

#include <vm/uma.h>
#include <vm/vm.h>
#include <vm/pmap.h>
#include <vm/vm_map.h>
#include <vm/vm_kern.h>
#include <vm/vm_extern.h>
#include <vm/vm_param.h>
#include <vm/vm_pageout.h>

#define	VMEM_MAXORDER		(sizeof(vmem_size_t) * NBBY)

#define	VMEM_HASHSIZE_MIN	16
#define	VMEM_HASHSIZE_MAX	131072

#define	VMEM_QCACHE_IDX_MAX	16

#define	VMEM_FITMASK	(M_BESTFIT | M_FIRSTFIT)

#define	VMEM_FLAGS						\
    (M_NOWAIT | M_WAITOK | M_USE_RESERVE | M_NOVM | M_BESTFIT | M_FIRSTFIT)

#define	BT_FLAGS	(M_NOWAIT | M_WAITOK | M_USE_RESERVE | M_NOVM)

#define	QC_NAME_MAX	16

/*
 * Data structures private to vmem.
 */
MALLOC_DEFINE(M_VMEM, "vmem", "vmem internal structures");

typedef struct vmem_btag bt_t;

TAILQ_HEAD(vmem_seglist, vmem_btag);
LIST_HEAD(vmem_freelist, vmem_btag);
LIST_HEAD(vmem_hashlist, vmem_btag);

struct qcache {
	uma_zone_t	qc_cache;
	vmem_t 		*qc_vmem;
	vmem_size_t	qc_size;
	char		qc_name[QC_NAME_MAX];
};
typedef struct qcache qcache_t;
#define	QC_POOL_TO_QCACHE(pool)	((qcache_t *)(pool->pr_qcache))

#define	VMEM_NAME_MAX	16

/* vmem arena */
struct vmem {
	struct mtx_padalign	vm_lock;
	struct cv		vm_cv;
	char			vm_name[VMEM_NAME_MAX+1];
	LIST_ENTRY(vmem)	vm_alllist;
	struct vmem_hashlist	vm_hash0[VMEM_HASHSIZE_MIN];
	struct vmem_freelist	vm_freelist[VMEM_MAXORDER];
	struct vmem_seglist	vm_seglist;
	struct vmem_hashlist	*vm_hashlist;
	vmem_size_t		vm_hashsize;

	/* Constant after init */
	vmem_size_t		vm_qcache_max;
	vmem_size_t		vm_quantum_mask;
	vmem_size_t		vm_import_quantum;
	int			vm_quantum_shift;

	/* Written on alloc/free */
	LIST_HEAD(, vmem_btag)	vm_freetags;
	int			vm_nfreetags;
	int			vm_nbusytag;
	vmem_size_t		vm_inuse;
	vmem_size_t		vm_size;

	/* Used on import. */
	vmem_import_t		*vm_importfn;
	vmem_release_t		*vm_releasefn;
	void			*vm_arg;

	/* Space exhaustion callback. */
	vmem_reclaim_t		*vm_reclaimfn;

	/* quantum cache */
	qcache_t		vm_qcache[VMEM_QCACHE_IDX_MAX];
};

/* boundary tag */
struct vmem_btag {
	TAILQ_ENTRY(vmem_btag) bt_seglist;
	union {
		LIST_ENTRY(vmem_btag) u_freelist; /* BT_TYPE_FREE */
		LIST_ENTRY(vmem_btag) u_hashlist; /* BT_TYPE_BUSY */
	} bt_u;
#define	bt_hashlist	bt_u.u_hashlist
#define	bt_freelist	bt_u.u_freelist
	vmem_addr_t	bt_start;
	vmem_size_t	bt_size;
	int		bt_type;
};

#define	BT_TYPE_SPAN		1	/* Allocated from importfn */
#define	BT_TYPE_SPAN_STATIC	2	/* vmem_add() or create. */
#define	BT_TYPE_FREE		3	/* Available space. */
#define	BT_TYPE_BUSY		4	/* Used space. */
#define	BT_ISSPAN_P(bt)	((bt)->bt_type <= BT_TYPE_SPAN_STATIC)

#define	BT_END(bt)	((bt)->bt_start + (bt)->bt_size - 1)

#if defined(DIAGNOSTIC)
static void vmem_check(vmem_t *);
#endif

static struct callout	vmem_periodic_ch;
static int		vmem_periodic_interval;
static struct task	vmem_periodic_wk;

static struct mtx_padalign vmem_list_lock;
static LIST_HEAD(, vmem) vmem_list = LIST_HEAD_INITIALIZER(vmem_list);

/* ---- misc */
#define	VMEM_CONDVAR_INIT(vm, wchan)	cv_init(&vm->vm_cv, wchan)
#define	VMEM_CONDVAR_DESTROY(vm)	cv_destroy(&vm->vm_cv)
#define	VMEM_CONDVAR_WAIT(vm)		cv_wait(&vm->vm_cv, &vm->vm_lock)
#define	VMEM_CONDVAR_BROADCAST(vm)	cv_broadcast(&vm->vm_cv)


#define	VMEM_LOCK(vm)		mtx_lock(&vm->vm_lock)
#define	VMEM_TRYLOCK(vm)	mtx_trylock(&vm->vm_lock)
#define	VMEM_UNLOCK(vm)		mtx_unlock(&vm->vm_lock)
#define	VMEM_LOCK_INIT(vm, name) mtx_init(&vm->vm_lock, (name), NULL, MTX_DEF)
#define	VMEM_LOCK_DESTROY(vm)	mtx_destroy(&vm->vm_lock)
#define	VMEM_ASSERT_LOCKED(vm)	mtx_assert(&vm->vm_lock, MA_OWNED);

#define	VMEM_ALIGNUP(addr, align)	(-(-(addr) & -(align)))

#define	VMEM_CROSS_P(addr1, addr2, boundary) \
	((((addr1) ^ (addr2)) & -(boundary)) != 0)

#define	ORDER2SIZE(order)	((vmem_size_t)1 << (order))
#define	SIZE2ORDER(size)	((int)flsl(size) - 1)

/*
 * Maximum number of boundary tags that may be required to satisfy an
 * allocation.  Two may be required to import.  Another two may be
 * required to clip edges.
 */
#define	BT_MAXALLOC	4

/*
 * Max free limits the number of locally cached boundary tags.  We
 * just want to avoid hitting the zone allocator for every call.
 */
#define BT_MAXFREE	(BT_MAXALLOC * 8)

/* Allocator for boundary tags. */
static uma_zone_t vmem_bt_zone;

/* boot time arena storage. */
static struct vmem buffer_arena_storage;
static struct vmem transient_arena_storage;
vmem_t *buffer_arena = &buffer_arena_storage;
vmem_t *transient_arena = &transient_arena_storage;

/*
 * Fill the vmem's boundary tag cache.  We guarantee that boundary tag
 * allocation will not fail once bt_fill() passes.  To do so we cache
 * at least the maximum possible tag allocations in the arena.
 */
static int
bt_fill(vmem_t *vm, int flags)
{
	bt_t *bt;

	VMEM_ASSERT_LOCKED(vm);

	/*
	 * Loop until we meet the reserve.  To minimize the lock shuffle
	 * and prevent simultaneous fills we first try a NOWAIT regardless
	 * of the caller's flags.  Specify M_NOVM so we don't recurse while
	 * holding a vmem lock.
	 */
	while (vm->vm_nfreetags < BT_MAXALLOC) {
		bt = uma_zalloc(vmem_bt_zone,
		    (flags & M_USE_RESERVE) | M_NOWAIT | M_NOVM);
		if (bt == NULL) {
			VMEM_UNLOCK(vm);
			bt = uma_zalloc(vmem_bt_zone, flags);
			VMEM_LOCK(vm);
			if (bt == NULL && (flags & M_NOWAIT) != 0)
				break;
		}
		LIST_INSERT_HEAD(&vm->vm_freetags, bt, bt_freelist);
		vm->vm_nfreetags++;
	}

	if (vm->vm_nfreetags < BT_MAXALLOC)
		return ENOMEM;

	return 0;
}

/*
 * Pop a tag off of the freetag stack.
 */
static bt_t *
bt_alloc(vmem_t *vm)
{
	bt_t *bt;

	VMEM_ASSERT_LOCKED(vm);
	bt = LIST_FIRST(&vm->vm_freetags);
	MPASS(bt != NULL);
	LIST_REMOVE(bt, bt_freelist);
	vm->vm_nfreetags--;

	return bt;
}

/*
 * Trim the per-vmem free list.  Returns with the lock released to
 * avoid allocator recursions.
 */
static void
bt_freetrim(vmem_t *vm, int freelimit)
{
	LIST_HEAD(, vmem_btag) freetags;
	bt_t *bt;

	LIST_INIT(&freetags);
	VMEM_ASSERT_LOCKED(vm);
	while (vm->vm_nfreetags > freelimit) {
		bt = LIST_FIRST(&vm->vm_freetags);
		LIST_REMOVE(bt, bt_freelist);
		vm->vm_nfreetags--;
		LIST_INSERT_HEAD(&freetags, bt, bt_freelist);
	}
	VMEM_UNLOCK(vm);
	while ((bt = LIST_FIRST(&freetags)) != NULL) {
		LIST_REMOVE(bt, bt_freelist);
		uma_zfree(vmem_bt_zone, bt);
	}
}

static inline void
bt_free(vmem_t *vm, bt_t *bt)
{

	VMEM_ASSERT_LOCKED(vm);
	MPASS(LIST_FIRST(&vm->vm_freetags) != bt);
	LIST_INSERT_HEAD(&vm->vm_freetags, bt, bt_freelist);
	vm->vm_nfreetags++;
}

/*
 * freelist[0] ... [1, 1]
 * freelist[1] ... [2, 3]
 * freelist[2] ... [4, 7]
 * freelist[3] ... [8, 15]
 *  :
 * freelist[n] ... [(1 << n), (1 << (n + 1)) - 1]
 *  :
 */

static struct vmem_freelist *
bt_freehead_tofree(vmem_t *vm, vmem_size_t size)
{
	const vmem_size_t qsize = size >> vm->vm_quantum_shift;
	const int idx = SIZE2ORDER(qsize);

	MPASS(size != 0 && qsize != 0);
	MPASS((size & vm->vm_quantum_mask) == 0);
	MPASS(idx >= 0);
	MPASS(idx < VMEM_MAXORDER);

	return &vm->vm_freelist[idx];
}

/*
 * bt_freehead_toalloc: return the freelist for the given size and allocation
 * strategy.
 *
 * For M_FIRSTFIT, return the list in which any blocks are large enough
 * for the requested size.  otherwise, return the list which can have blocks
 * large enough for the requested size.
 */
static struct vmem_freelist *
bt_freehead_toalloc(vmem_t *vm, vmem_size_t size, int strat)
{
	const vmem_size_t qsize = size >> vm->vm_quantum_shift;
	int idx = SIZE2ORDER(qsize);

	MPASS(size != 0 && qsize != 0);
	MPASS((size & vm->vm_quantum_mask) == 0);

	if (strat == M_FIRSTFIT && ORDER2SIZE(idx) != qsize) {
		idx++;
		/* check too large request? */
	}
	MPASS(idx >= 0);
	MPASS(idx < VMEM_MAXORDER);

	return &vm->vm_freelist[idx];
}

/* ---- boundary tag hash */

static struct vmem_hashlist *
bt_hashhead(vmem_t *vm, vmem_addr_t addr)
{
	struct vmem_hashlist *list;
	unsigned int hash;

	hash = hash32_buf(&addr, sizeof(addr), 0);
	list = &vm->vm_hashlist[hash % vm->vm_hashsize];

	return list;
}

static bt_t *
bt_lookupbusy(vmem_t *vm, vmem_addr_t addr)
{
	struct vmem_hashlist *list;
	bt_t *bt;

	VMEM_ASSERT_LOCKED(vm);
	list = bt_hashhead(vm, addr); 
	LIST_FOREACH(bt, list, bt_hashlist) {
		if (bt->bt_start == addr) {
			break;
		}
	}

	return bt;
}

static void
bt_rembusy(vmem_t *vm, bt_t *bt)
{

	VMEM_ASSERT_LOCKED(vm);
	MPASS(vm->vm_nbusytag > 0);
	vm->vm_inuse -= bt->bt_size;
	vm->vm_nbusytag--;
	LIST_REMOVE(bt, bt_hashlist);
}

static void
bt_insbusy(vmem_t *vm, bt_t *bt)
{
	struct vmem_hashlist *list;

	VMEM_ASSERT_LOCKED(vm);
	MPASS(bt->bt_type == BT_TYPE_BUSY);

	list = bt_hashhead(vm, bt->bt_start);
	LIST_INSERT_HEAD(list, bt, bt_hashlist);
	vm->vm_nbusytag++;
	vm->vm_inuse += bt->bt_size;
}

/* ---- boundary tag list */

static void
bt_remseg(vmem_t *vm, bt_t *bt)
{

	TAILQ_REMOVE(&vm->vm_seglist, bt, bt_seglist);
	bt_free(vm, bt);
}

static void
bt_insseg(vmem_t *vm, bt_t *bt, bt_t *prev)
{

	TAILQ_INSERT_AFTER(&vm->vm_seglist, prev, bt, bt_seglist);
}

static void
bt_insseg_tail(vmem_t *vm, bt_t *bt)
{

	TAILQ_INSERT_TAIL(&vm->vm_seglist, bt, bt_seglist);
}

static void
bt_remfree(vmem_t *vm, bt_t *bt)
{

	MPASS(bt->bt_type == BT_TYPE_FREE);

	LIST_REMOVE(bt, bt_freelist);
}

static void
bt_insfree(vmem_t *vm, bt_t *bt)
{
	struct vmem_freelist *list;

	list = bt_freehead_tofree(vm, bt->bt_size);
	LIST_INSERT_HEAD(list, bt, bt_freelist);
}

/* ---- vmem internal functions */

/*
 * Import from the arena into the quantum cache in UMA.
 */
static int
qc_import(void *arg, void **store, int cnt, int flags)
{
	qcache_t *qc;
	vmem_addr_t addr;
	int i;

	qc = arg;
	flags |= M_BESTFIT;
	for (i = 0; i < cnt; i++) {
		if (vmem_xalloc(qc->qc_vmem, qc->qc_size, 0, 0, 0,
		    VMEM_ADDR_MIN, VMEM_ADDR_MAX, flags, &addr) != 0)
			break;
		store[i] = (void *)addr;
		/* Only guarantee one allocation. */
		flags &= ~M_WAITOK;
		flags |= M_NOWAIT;
	}
	return i;
}

/*
 * Release memory from the UMA cache to the arena.
 */
static void
qc_release(void *arg, void **store, int cnt)
{
	qcache_t *qc;
	int i;

	qc = arg;
	for (i = 0; i < cnt; i++)
		vmem_xfree(qc->qc_vmem, (vmem_addr_t)store[i], qc->qc_size);
}

static void
qc_init(vmem_t *vm, vmem_size_t qcache_max)
{
	qcache_t *qc;
	vmem_size_t size;
	int qcache_idx_max;
	int i;

	MPASS((qcache_max & vm->vm_quantum_mask) == 0);
	qcache_idx_max = MIN(qcache_max >> vm->vm_quantum_shift,
	    VMEM_QCACHE_IDX_MAX);
	vm->vm_qcache_max = qcache_idx_max << vm->vm_quantum_shift;
	for (i = 0; i < qcache_idx_max; i++) {
		qc = &vm->vm_qcache[i];
		size = (i + 1) << vm->vm_quantum_shift;
		snprintf(qc->qc_name, sizeof(qc->qc_name), "%s-%zu",
		    vm->vm_name, size);
		qc->qc_vmem = vm;
		qc->qc_size = size;
		qc->qc_cache = uma_zcache_create(qc->qc_name, size,
		    NULL, NULL, NULL, NULL, qc_import, qc_release, qc,
		    UMA_ZONE_VM);
		MPASS(qc->qc_cache);
	}
}

static void
qc_destroy(vmem_t *vm)
{
	int qcache_idx_max;
	int i;

	qcache_idx_max = vm->vm_qcache_max >> vm->vm_quantum_shift;
	for (i = 0; i < qcache_idx_max; i++)
		uma_zdestroy(vm->vm_qcache[i].qc_cache);
}

static void
qc_drain(vmem_t *vm)
{
	int qcache_idx_max;
	int i;

	qcache_idx_max = vm->vm_qcache_max >> vm->vm_quantum_shift;
	for (i = 0; i < qcache_idx_max; i++)
		zone_drain(vm->vm_qcache[i].qc_cache);
}

void
vmem_startup(void)
{

	mtx_init(&vmem_list_lock, "vmem list lock", NULL, MTX_DEF);
	vmem_bt_zone = uma_zcreate("vmem btag",
	    sizeof(struct vmem_btag), NULL, NULL, NULL, NULL,
	    UMA_ALIGN_PTR, UMA_ZONE_VM);
}

/* ---- rehash */

static int
vmem_rehash(vmem_t *vm, vmem_size_t newhashsize)
{
	bt_t *bt;
	int i;
	struct vmem_hashlist *newhashlist;
	struct vmem_hashlist *oldhashlist;
	vmem_size_t oldhashsize;

	MPASS(newhashsize > 0);

	newhashlist = malloc(sizeof(struct vmem_hashlist) * newhashsize,
	    M_VMEM, M_NOWAIT);
	if (newhashlist == NULL)
		return ENOMEM;
	for (i = 0; i < newhashsize; i++) {
		LIST_INIT(&newhashlist[i]);
	}

	VMEM_LOCK(vm);
	oldhashlist = vm->vm_hashlist;
	oldhashsize = vm->vm_hashsize;
	vm->vm_hashlist = newhashlist;
	vm->vm_hashsize = newhashsize;
	if (oldhashlist == NULL) {
		VMEM_UNLOCK(vm);
		return 0;
	}
	for (i = 0; i < oldhashsize; i++) {
		while ((bt = LIST_FIRST(&oldhashlist[i])) != NULL) {
			bt_rembusy(vm, bt);
			bt_insbusy(vm, bt);
		}
	}
	VMEM_UNLOCK(vm);

	if (oldhashlist != vm->vm_hash0) {
		free(oldhashlist, M_VMEM);
	}

	return 0;
}

static void
vmem_periodic_kick(void *dummy)
{

	taskqueue_enqueue(taskqueue_thread, &vmem_periodic_wk);
}

static void
vmem_periodic(void *unused, int pending)
{
	vmem_t *vm;
	vmem_size_t desired;
	vmem_size_t current;

	mtx_lock(&vmem_list_lock);
	LIST_FOREACH(vm, &vmem_list, vm_alllist) {
#ifdef DIAGNOSTIC
		/* Convenient time to verify vmem state. */
		VMEM_LOCK(vm);
		vmem_check(vm);
		VMEM_UNLOCK(vm);
#endif
		desired = 1 << flsl(vm->vm_nbusytag);
		desired = MIN(MAX(desired, VMEM_HASHSIZE_MIN),
		    VMEM_HASHSIZE_MAX);
		current = vm->vm_hashsize;

		/* Grow in powers of two.  Shrink less aggressively. */
		if (desired >= current * 2 || desired * 4 <= current)
			vmem_rehash(vm, desired);
	}
	mtx_unlock(&vmem_list_lock);

	callout_reset(&vmem_periodic_ch, vmem_periodic_interval,
	    vmem_periodic_kick, NULL);
}

static void
vmem_start_callout(void *unused)
{

	TASK_INIT(&vmem_periodic_wk, 0, vmem_periodic, NULL);
	vmem_periodic_interval = hz * 10;
	callout_init(&vmem_periodic_ch, CALLOUT_MPSAFE);
	callout_reset(&vmem_periodic_ch, vmem_periodic_interval,
	    vmem_periodic_kick, NULL);
}
SYSINIT(vfs, SI_SUB_CONFIGURE, SI_ORDER_ANY, vmem_start_callout, NULL);

static void
vmem_add1(vmem_t *vm, vmem_addr_t addr, vmem_size_t size, int type)
{
	bt_t *btspan;
	bt_t *btfree;

	MPASS(type == BT_TYPE_SPAN || type == BT_TYPE_SPAN_STATIC);

	btspan = bt_alloc(vm);
	btspan->bt_type = type;
	btspan->bt_start = addr;
	btspan->bt_size = size;

	btfree = bt_alloc(vm);
	btfree->bt_type = BT_TYPE_FREE;
	btfree->bt_start = addr;
	btfree->bt_size = size;

	bt_insseg_tail(vm, btspan);
	bt_insseg(vm, btfree, btspan);
	bt_insfree(vm, btfree);
	vm->vm_size += size;
}

static void
vmem_destroy1(vmem_t *vm)
{
	bt_t *bt;

	/*
	 * Drain per-cpu quantum caches.
	 */
	qc_destroy(vm);

	/*
	 * The vmem should now only contain empty segments.
	 */
	VMEM_LOCK(vm);
	MPASS(vm->vm_nbusytag == 0);

	while ((bt = TAILQ_FIRST(&vm->vm_seglist)) != NULL)
		bt_remseg(vm, bt);

	if (vm->vm_hashlist != NULL && vm->vm_hashlist != vm->vm_hash0)
		free(vm->vm_hashlist, M_VMEM);

	bt_freetrim(vm, 0);

	VMEM_CONDVAR_DESTROY(vm);
	VMEM_LOCK_DESTROY(vm);
	free(vm, M_VMEM);
}

static int
vmem_import(vmem_t *vm, vmem_size_t size, int flags)
{
	vmem_addr_t addr;
	int error;

	if (vm->vm_importfn == NULL)
		return EINVAL;

	size = roundup(size, vm->vm_import_quantum);

	/*
	 * Hide MAXALLOC tags so we're guaranteed to be able to add this
	 * span and the tag we want to allocate from it.
	 */
	MPASS(vm->vm_nfreetags >= BT_MAXALLOC);
	vm->vm_nfreetags -= BT_MAXALLOC;
	VMEM_UNLOCK(vm);
	error = (vm->vm_importfn)(vm->vm_arg, size, flags, &addr);
	VMEM_LOCK(vm);
	vm->vm_nfreetags += BT_MAXALLOC;
	if (error)
		return ENOMEM;

	vmem_add1(vm, addr, size, BT_TYPE_SPAN);

	return 0;
}

/*
 * vmem_fit: check if a bt can satisfy the given restrictions.
 *
 * it's a caller's responsibility to ensure the region is big enough
 * before calling us.
 */
static int
vmem_fit(const bt_t *bt, vmem_size_t size, vmem_size_t align,
    vmem_size_t phase, vmem_size_t nocross, vmem_addr_t minaddr,
    vmem_addr_t maxaddr, vmem_addr_t *addrp)
{
	vmem_addr_t start;
	vmem_addr_t end;

	MPASS(size > 0);
	MPASS(bt->bt_size >= size); /* caller's responsibility */

	/*
	 * XXX assumption: vmem_addr_t and vmem_size_t are
	 * unsigned integer of the same size.
	 */

	start = bt->bt_start;
	if (start < minaddr) {
		start = minaddr;
	}
	end = BT_END(bt);
	if (end > maxaddr)
		end = maxaddr;
	if (start > end) 
		return (ENOMEM);

	start = VMEM_ALIGNUP(start - phase, align) + phase;
	if (start < bt->bt_start)
		start += align;
	if (VMEM_CROSS_P(start, start + size - 1, nocross)) {
		MPASS(align < nocross);
		start = VMEM_ALIGNUP(start - phase, nocross) + phase;
	}
	if (start <= end && end - start >= size - 1) {
		MPASS((start & (align - 1)) == phase);
		MPASS(!VMEM_CROSS_P(start, start + size - 1, nocross));
		MPASS(minaddr <= start);
		MPASS(maxaddr == 0 || start + size - 1 <= maxaddr);
		MPASS(bt->bt_start <= start);
		MPASS(BT_END(bt) - start >= size - 1);
		*addrp = start;

		return (0);
	}
	return (ENOMEM);
}

/*
 * vmem_clip:  Trim the boundary tag edges to the requested start and size.
 */
static void
vmem_clip(vmem_t *vm, bt_t *bt, vmem_addr_t start, vmem_size_t size)
{
	bt_t *btnew;
	bt_t *btprev;

	VMEM_ASSERT_LOCKED(vm);
	MPASS(bt->bt_type == BT_TYPE_FREE);
	MPASS(bt->bt_size >= size);
	bt_remfree(vm, bt);
	if (bt->bt_start != start) {
		btprev = bt_alloc(vm);
		btprev->bt_type = BT_TYPE_FREE;
		btprev->bt_start = bt->bt_start;
		btprev->bt_size = start - bt->bt_start;
		bt->bt_start = start;
		bt->bt_size -= btprev->bt_size;
		bt_insfree(vm, btprev);
		bt_insseg(vm, btprev,
		    TAILQ_PREV(bt, vmem_seglist, bt_seglist));
	}
	MPASS(bt->bt_start == start);
	if (bt->bt_size != size && bt->bt_size - size > vm->vm_quantum_mask) {
		/* split */
		btnew = bt_alloc(vm);
		btnew->bt_type = BT_TYPE_BUSY;
		btnew->bt_start = bt->bt_start;
		btnew->bt_size = size;
		bt->bt_start = bt->bt_start + size;
		bt->bt_size -= size;
		bt_insfree(vm, bt);
		bt_insseg(vm, btnew,
		    TAILQ_PREV(bt, vmem_seglist, bt_seglist));
		bt_insbusy(vm, btnew);
		bt = btnew;
	} else {
		bt->bt_type = BT_TYPE_BUSY;
		bt_insbusy(vm, bt);
	}
	MPASS(bt->bt_size >= size);
	bt->bt_type = BT_TYPE_BUSY;
}

/* ---- vmem API */

void
vmem_set_import(vmem_t *vm, vmem_import_t *importfn,
     vmem_release_t *releasefn, void *arg, vmem_size_t import_quantum)
{

	VMEM_LOCK(vm);
	vm->vm_importfn = importfn;
	vm->vm_releasefn = releasefn;
	vm->vm_arg = arg;
	vm->vm_import_quantum = import_quantum;
	VMEM_UNLOCK(vm);
}

void
vmem_set_reclaim(vmem_t *vm, vmem_reclaim_t *reclaimfn)
{

	VMEM_LOCK(vm);
	vm->vm_reclaimfn = reclaimfn;
	VMEM_UNLOCK(vm);
}

/*
 * vmem_init: Initializes vmem arena.
 */
vmem_t *
vmem_init(vmem_t *vm, const char *name, vmem_addr_t base, vmem_size_t size,
    vmem_size_t quantum, vmem_size_t qcache_max, int flags)
{
	int i;

	MPASS(quantum > 0);

	bzero(vm, sizeof(*vm));

	VMEM_CONDVAR_INIT(vm, name);
	VMEM_LOCK_INIT(vm, name);
	vm->vm_nfreetags = 0;
	LIST_INIT(&vm->vm_freetags);
	strlcpy(vm->vm_name, name, sizeof(vm->vm_name));
	vm->vm_quantum_mask = quantum - 1;
	vm->vm_quantum_shift = SIZE2ORDER(quantum);
	MPASS(ORDER2SIZE(vm->vm_quantum_shift) == quantum);
	vm->vm_nbusytag = 0;
	vm->vm_size = 0;
	vm->vm_inuse = 0;
	qc_init(vm, qcache_max);

	TAILQ_INIT(&vm->vm_seglist);
	for (i = 0; i < VMEM_MAXORDER; i++) {
		LIST_INIT(&vm->vm_freelist[i]);
	}
	memset(&vm->vm_hash0, 0, sizeof(vm->vm_hash0));
	vm->vm_hashsize = VMEM_HASHSIZE_MIN;
	vm->vm_hashlist = vm->vm_hash0;

	if (size != 0) {
		if (vmem_add(vm, base, size, flags) != 0) {
			vmem_destroy1(vm);
			return NULL;
		}
	}

	mtx_lock(&vmem_list_lock);
	LIST_INSERT_HEAD(&vmem_list, vm, vm_alllist);
	mtx_unlock(&vmem_list_lock);

	return vm;
}

/*
 * vmem_create: create an arena.
 */
vmem_t *
vmem_create(const char *name, vmem_addr_t base, vmem_size_t size,
    vmem_size_t quantum, vmem_size_t qcache_max, int flags)
{

	vmem_t *vm;

	vm = malloc(sizeof(*vm), M_VMEM, flags & (M_WAITOK|M_NOWAIT));
	if (vm == NULL)
		return (NULL);
	if (vmem_init(vm, name, base, size, quantum, qcache_max,
	    flags) == NULL) {
		free(vm, M_VMEM);
		return (NULL);
	}
	return (vm);
}

void
vmem_destroy(vmem_t *vm)
{

	mtx_lock(&vmem_list_lock);
	LIST_REMOVE(vm, vm_alllist);
	mtx_unlock(&vmem_list_lock);

	vmem_destroy1(vm);
}

vmem_size_t
vmem_roundup_size(vmem_t *vm, vmem_size_t size)
{

	return (size + vm->vm_quantum_mask) & ~vm->vm_quantum_mask;
}

/*
 * vmem_alloc: allocate resource from the arena.
 */
int
vmem_alloc(vmem_t *vm, vmem_size_t size, int flags, vmem_addr_t *addrp)
{
	const int strat __unused = flags & VMEM_FITMASK;
	qcache_t *qc;

	flags &= VMEM_FLAGS;
	MPASS(size > 0);
	MPASS(strat == M_BESTFIT || strat == M_FIRSTFIT);
	if ((flags & M_NOWAIT) == 0)
		WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL, "vmem_alloc");

	if (size <= vm->vm_qcache_max) {
		qc = &vm->vm_qcache[(size - 1) >> vm->vm_quantum_shift];
		*addrp = (vmem_addr_t)uma_zalloc(qc->qc_cache, flags);
		if (*addrp == 0)
			return (ENOMEM);
		return (0);
	}

	return vmem_xalloc(vm, size, 0, 0, 0, VMEM_ADDR_MIN, VMEM_ADDR_MAX,
	    flags, addrp);
}

int
vmem_xalloc(vmem_t *vm, const vmem_size_t size0, vmem_size_t align,
    const vmem_size_t phase, const vmem_size_t nocross,
    const vmem_addr_t minaddr, const vmem_addr_t maxaddr, int flags,
    vmem_addr_t *addrp)
{
	const vmem_size_t size = vmem_roundup_size(vm, size0);
	struct vmem_freelist *list;
	struct vmem_freelist *first;
	struct vmem_freelist *end;
	vmem_size_t avail;
	bt_t *bt;
	int error;
	int strat;

	flags &= VMEM_FLAGS;
	strat = flags & VMEM_FITMASK;
	MPASS(size0 > 0);
	MPASS(size > 0);
	MPASS(strat == M_BESTFIT || strat == M_FIRSTFIT);
	MPASS((flags & (M_NOWAIT|M_WAITOK)) != (M_NOWAIT|M_WAITOK));
	if ((flags & M_NOWAIT) == 0)
		WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL, "vmem_xalloc");
	MPASS((align & vm->vm_quantum_mask) == 0);
	MPASS((align & (align - 1)) == 0);
	MPASS((phase & vm->vm_quantum_mask) == 0);
	MPASS((nocross & vm->vm_quantum_mask) == 0);
	MPASS((nocross & (nocross - 1)) == 0);
	MPASS((align == 0 && phase == 0) || phase < align);
	MPASS(nocross == 0 || nocross >= size);
	MPASS(minaddr <= maxaddr);
	MPASS(!VMEM_CROSS_P(phase, phase + size - 1, nocross));

	if (align == 0)
		align = vm->vm_quantum_mask + 1;

	*addrp = 0;
	end = &vm->vm_freelist[VMEM_MAXORDER];
	/*
	 * choose a free block from which we allocate.
	 */
	first = bt_freehead_toalloc(vm, size, strat);
	VMEM_LOCK(vm);
	for (;;) {
		/*
		 * Make sure we have enough tags to complete the
		 * operation.
		 */
		if (vm->vm_nfreetags < BT_MAXALLOC &&
		    bt_fill(vm, flags) != 0) {
			error = ENOMEM;
			break;
		}
		/*
	 	 * Scan freelists looking for a tag that satisfies the
		 * allocation.  If we're doing BESTFIT we may encounter
		 * sizes below the request.  If we're doing FIRSTFIT we
		 * inspect only the first element from each list.
		 */
		for (list = first; list < end; list++) {
			LIST_FOREACH(bt, list, bt_freelist) {
				if (bt->bt_size >= size) {
					error = vmem_fit(bt, size, align, phase,
					    nocross, minaddr, maxaddr, addrp);
					if (error == 0) {
						vmem_clip(vm, bt, *addrp, size);
						goto out;
					}
				}
				/* FIRST skips to the next list. */
				if (strat == M_FIRSTFIT)
					break;
			}
		}
		/*
		 * Retry if the fast algorithm failed.
		 */
		if (strat == M_FIRSTFIT) {
			strat = M_BESTFIT;
			first = bt_freehead_toalloc(vm, size, strat);
			continue;
		}
		/*
		 * XXX it is possible to fail to meet restrictions with the
		 * imported region.  It is up to the user to specify the
		 * import quantum such that it can satisfy any allocation.
		 */
		if (vmem_import(vm, size, flags) == 0)
			continue;

		/*
		 * Try to free some space from the quantum cache or reclaim
		 * functions if available.
		 */
		if (vm->vm_qcache_max != 0 || vm->vm_reclaimfn != NULL) {
			avail = vm->vm_size - vm->vm_inuse;
			VMEM_UNLOCK(vm);
			if (vm->vm_qcache_max != 0)
				qc_drain(vm);
			if (vm->vm_reclaimfn != NULL)
				vm->vm_reclaimfn(vm, flags);
			VMEM_LOCK(vm);
			/* If we were successful retry even NOWAIT. */
			if (vm->vm_size - vm->vm_inuse > avail)
				continue;
		}
		if ((flags & M_NOWAIT) != 0) {
			error = ENOMEM;
			break;
		}
		VMEM_CONDVAR_WAIT(vm);
	}
out:
	VMEM_UNLOCK(vm);
	if (error != 0 && (flags & M_NOWAIT) == 0)
		panic("failed to allocate waiting allocation\n");

	return (error);
}

/*
 * vmem_free: free the resource to the arena.
 */
void
vmem_free(vmem_t *vm, vmem_addr_t addr, vmem_size_t size)
{
	qcache_t *qc;
	MPASS(size > 0);

	if (size <= vm->vm_qcache_max) {
		qc = &vm->vm_qcache[(size - 1) >> vm->vm_quantum_shift];
		uma_zfree(qc->qc_cache, (void *)addr);
	} else
		vmem_xfree(vm, addr, size);
}

void
vmem_xfree(vmem_t *vm, vmem_addr_t addr, vmem_size_t size)
{
	bt_t *bt;
	bt_t *t;

	MPASS(size > 0);

	VMEM_LOCK(vm);
	bt = bt_lookupbusy(vm, addr);
	MPASS(bt != NULL);
	MPASS(bt->bt_start == addr);
	MPASS(bt->bt_size == vmem_roundup_size(vm, size) ||
	    bt->bt_size - vmem_roundup_size(vm, size) <= vm->vm_quantum_mask);
	MPASS(bt->bt_type == BT_TYPE_BUSY);
	bt_rembusy(vm, bt);
	bt->bt_type = BT_TYPE_FREE;

	/* coalesce */
	t = TAILQ_NEXT(bt, bt_seglist);
	if (t != NULL && t->bt_type == BT_TYPE_FREE) {
		MPASS(BT_END(bt) < t->bt_start);	/* YYY */
		bt->bt_size += t->bt_size;
		bt_remfree(vm, t);
		bt_remseg(vm, t);
	}
	t = TAILQ_PREV(bt, vmem_seglist, bt_seglist);
	if (t != NULL && t->bt_type == BT_TYPE_FREE) {
		MPASS(BT_END(t) < bt->bt_start);	/* YYY */
		bt->bt_size += t->bt_size;
		bt->bt_start = t->bt_start;
		bt_remfree(vm, t);
		bt_remseg(vm, t);
	}

	t = TAILQ_PREV(bt, vmem_seglist, bt_seglist);
	MPASS(t != NULL);
	MPASS(BT_ISSPAN_P(t) || t->bt_type == BT_TYPE_BUSY);
	if (vm->vm_releasefn != NULL && t->bt_type == BT_TYPE_SPAN &&
	    t->bt_size == bt->bt_size) {
		vmem_addr_t spanaddr;
		vmem_size_t spansize;

		MPASS(t->bt_start == bt->bt_start);
		spanaddr = bt->bt_start;
		spansize = bt->bt_size;
		bt_remseg(vm, bt);
		bt_remseg(vm, t);
		vm->vm_size -= spansize;
		VMEM_CONDVAR_BROADCAST(vm);
		bt_freetrim(vm, BT_MAXFREE);
		(*vm->vm_releasefn)(vm->vm_arg, spanaddr, spansize);
	} else {
		bt_insfree(vm, bt);
		VMEM_CONDVAR_BROADCAST(vm);
		bt_freetrim(vm, BT_MAXFREE);
	}
}

/*
 * vmem_add:
 *
 */
int
vmem_add(vmem_t *vm, vmem_addr_t addr, vmem_size_t size, int flags)
{
	int error;

	error = 0;
	flags &= VMEM_FLAGS;
	VMEM_LOCK(vm);
	if (vm->vm_nfreetags >= BT_MAXALLOC || bt_fill(vm, flags) == 0)
		vmem_add1(vm, addr, size, BT_TYPE_SPAN_STATIC);
	else
		error = ENOMEM;
	VMEM_UNLOCK(vm);

	return (error);
}

/*
 * vmem_size: information about arenas size
 */
vmem_size_t
vmem_size(vmem_t *vm, int typemask)
{

	switch (typemask) {
	case VMEM_ALLOC:
		return vm->vm_inuse;
	case VMEM_FREE:
		return vm->vm_size - vm->vm_inuse;
	case VMEM_FREE|VMEM_ALLOC:
		return vm->vm_size;
	default:
		panic("vmem_size");
	}
}

/* ---- debug */

#if defined(DDB) || defined(DIAGNOSTIC)

static void bt_dump(const bt_t *, int (*)(const char *, ...)
    __printflike(1, 2));

static const char *
bt_type_string(int type)
{

	switch (type) {
	case BT_TYPE_BUSY:
		return "busy";
	case BT_TYPE_FREE:
		return "free";
	case BT_TYPE_SPAN:
		return "span";
	case BT_TYPE_SPAN_STATIC:
		return "static span";
	default:
		break;
	}
	return "BOGUS";
}

static void
bt_dump(const bt_t *bt, int (*pr)(const char *, ...))
{

	(*pr)("\t%p: %jx %jx, %d(%s)\n",
	    bt, (intmax_t)bt->bt_start, (intmax_t)bt->bt_size,
	    bt->bt_type, bt_type_string(bt->bt_type));
}

static void
vmem_dump(const vmem_t *vm , int (*pr)(const char *, ...) __printflike(1, 2))
{
	const bt_t *bt;
	int i;

	(*pr)("vmem %p '%s'\n", vm, vm->vm_name);
	TAILQ_FOREACH(bt, &vm->vm_seglist, bt_seglist) {
		bt_dump(bt, pr);
	}

	for (i = 0; i < VMEM_MAXORDER; i++) {
		const struct vmem_freelist *fl = &vm->vm_freelist[i];

		if (LIST_EMPTY(fl)) {
			continue;
		}

		(*pr)("freelist[%d]\n", i);
		LIST_FOREACH(bt, fl, bt_freelist) {
			bt_dump(bt, pr);
		}
	}
}

#endif /* defined(DDB) || defined(DIAGNOSTIC) */

#if defined(DDB)
static bt_t *
vmem_whatis_lookup(vmem_t *vm, vmem_addr_t addr)
{
	bt_t *bt;

	TAILQ_FOREACH(bt, &vm->vm_seglist, bt_seglist) {
		if (BT_ISSPAN_P(bt)) {
			continue;
		}
		if (bt->bt_start <= addr && addr <= BT_END(bt)) {
			return bt;
		}
	}

	return NULL;
}

void
vmem_whatis(vmem_addr_t addr, int (*pr)(const char *, ...))
{
	vmem_t *vm;

	LIST_FOREACH(vm, &vmem_list, vm_alllist) {
		bt_t *bt;

		bt = vmem_whatis_lookup(vm, addr);
		if (bt == NULL) {
			continue;
		}
		(*pr)("%p is %p+%zu in VMEM '%s' (%s)\n",
		    (void *)addr, (void *)bt->bt_start,
		    (vmem_size_t)(addr - bt->bt_start), vm->vm_name,
		    (bt->bt_type == BT_TYPE_BUSY) ? "allocated" : "free");
	}
}

void
vmem_printall(const char *modif, int (*pr)(const char *, ...))
{
	const vmem_t *vm;

	LIST_FOREACH(vm, &vmem_list, vm_alllist) {
		vmem_dump(vm, pr);
	}
}

void
vmem_print(vmem_addr_t addr, const char *modif, int (*pr)(const char *, ...))
{
	const vmem_t *vm = (const void *)addr;

	vmem_dump(vm, pr);
}
#endif /* defined(DDB) */

#define vmem_printf printf

#if defined(DIAGNOSTIC)

static bool
vmem_check_sanity(vmem_t *vm)
{
	const bt_t *bt, *bt2;

	MPASS(vm != NULL);

	TAILQ_FOREACH(bt, &vm->vm_seglist, bt_seglist) {
		if (bt->bt_start > BT_END(bt)) {
			printf("corrupted tag\n");
			bt_dump(bt, vmem_printf);
			return false;
		}
	}
	TAILQ_FOREACH(bt, &vm->vm_seglist, bt_seglist) {
		TAILQ_FOREACH(bt2, &vm->vm_seglist, bt_seglist) {
			if (bt == bt2) {
				continue;
			}
			if (BT_ISSPAN_P(bt) != BT_ISSPAN_P(bt2)) {
				continue;
			}
			if (bt->bt_start <= BT_END(bt2) &&
			    bt2->bt_start <= BT_END(bt)) {
				printf("overwrapped tags\n");
				bt_dump(bt, vmem_printf);
				bt_dump(bt2, vmem_printf);
				return false;
			}
		}
	}

	return true;
}

static void
vmem_check(vmem_t *vm)
{

	if (!vmem_check_sanity(vm)) {
		panic("insanity vmem %p", vm);
	}
}

#endif /* defined(DIAGNOSTIC) */