# $FreeBSD: projects/vps/sys/modules/pfsync/Makefile 240494 2012-09-14 11:51:49Z glebius $

.include <bsd.own.mk>

.PATH: ${.CURDIR}/../../netpfil/pf

KMOD=	pfsync
SRCS=	if_pfsync.c \
	opt_pf.h opt_inet.h opt_inet6.h
SRCS+=	bus_if.h device_if.h

.if defined(KERNBUILDDIR)
MKDEP+=		-include ${KERNBUILDDIR}/opt_global.h
.else
.if ${MK_INET_SUPPORT} != "no"
opt_inet.h:
	echo "#define INET 1" > ${.TARGET}
.endif

.if ${MK_INET6_SUPPORT} != "no"
opt_inet6.h:
	echo "#define INET6 1" > ${.TARGET}
.endif

.if defined(VIMAGE)
opt_global.h:
	echo "#define VIMAGE 1" >> ${.TARGET}
CFLAGS+=	-include opt_global.h
MKDEP+=		-include opt_global.h
.endif
.endif

.include <bsd.kmod.mk>
