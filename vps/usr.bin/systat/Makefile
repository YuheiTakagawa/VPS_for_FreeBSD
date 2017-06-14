#	@(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD: projects/vps/usr.bin/systat/Makefile 257008 2013-10-23 19:02:26Z will $

.include <bsd.own.mk>

PROG=	systat
SRCS=	cmds.c cmdtab.c devs.c fetch.c iostat.c keyboard.c main.c \
	netcmds.c netstat.c pigs.c swap.c icmp.c \
	mode.c ip.c tcp.c \
	vmstat.c convtbl.c ifcmds.c ifstat.c

.if ${MK_INET6_SUPPORT} != "no"
SRCS+=	icmp6.c ip6.c
CFLAGS+= -DINET6
.endif

WARNS?=	0

DPADD=	${LIBNCURSESW} ${LIBM} ${LIBDEVSTAT} ${LIBKVM}
LDADD=	-lncursesw -lm -ldevstat -lkvm

.include <bsd.prog.mk>
