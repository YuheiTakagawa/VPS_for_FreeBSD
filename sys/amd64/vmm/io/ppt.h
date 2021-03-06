/*-
 * Copyright (c) 2011 NetApp, Inc.
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
 * THIS SOFTWARE IS PROVIDED BY NETAPP, INC ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL NETAPP, INC OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: projects/vps/sys/amd64/vmm/io/ppt.h 245678 2013-01-20 03:42:49Z neel $
 */

#ifndef _IO_PPT_H_
#define	_IO_PPT_H_

int	ppt_assign_device(struct vm *vm, int bus, int slot, int func);
int	ppt_unassign_device(struct vm *vm, int bus, int slot, int func);
int	ppt_unassign_all(struct vm *vm);
int	ppt_map_mmio(struct vm *vm, int bus, int slot, int func,
		     vm_paddr_t gpa, size_t len, vm_paddr_t hpa);
int	ppt_setup_msi(struct vm *vm, int vcpu, int bus, int slot, int func,
		      int destcpu, int vector, int numvec);
int	ppt_setup_msix(struct vm *vm, int vcpu, int bus, int slot, int func,
		       int idx, uint32_t msg, uint32_t vector_control, uint64_t addr);
#endif
