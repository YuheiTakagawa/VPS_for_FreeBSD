# $FreeBSD: projects/vps/sys/modules/dtrace/sdt/Makefile 179065 2008-05-17 02:31:19Z jb $

.PATH: ${.CURDIR}/../../../cddl/dev/sdt

KMOD=		sdt
SRCS=		sdt.c
SRCS+=		vnode_if.h

CFLAGS+=	-I${.CURDIR}/../../../cddl/compat/opensolaris \
		-I${.CURDIR}/../../../cddl/contrib/opensolaris/uts/common \
		-I${.CURDIR}/../../..

.include <bsd.kmod.mk>
