# $FreeBSD: projects/vps/sys/modules/ext2fs/Makefile 257008 2013-10-23 19:02:26Z will $

.PATH:	${.CURDIR}/../../fs/ext2fs
KMOD=	ext2fs
SRCS=	opt_ddb.h opt_directio.h opt_quota.h opt_suiddir.h vnode_if.h \
	ext2_alloc.c ext2_balloc.c ext2_bmap.c ext2_hash.c ext2_htree.c \
	ext2_inode.c ext2_inode_cnv.c ext2_lookup.c ext2_subr.c ext2_vfsops.c \
	ext2_vnops.c

.include <bsd.kmod.mk>
