# $FreeBSD: projects/vps/sys/modules/netgraph/ipfw/Makefile 225586 2011-09-15 12:28:17Z ae $

.include <bsd.own.mk>

KMOD=	ng_ipfw
SRCS= 	ng_ipfw.c opt_inet.h opt_inet6.h

.if !defined(KERNBUILDDIR)

.if ${MK_INET_SUPPORT} != "no"
opt_inet.h:
	echo "#define INET 1" > ${.TARGET}
.endif
.if ${MK_INET6_SUPPORT} != "no"
opt_inet6.h:
	echo "#define INET6 1" > ${.TARGET}
.endif
.endif

.include <bsd.kmod.mk>
