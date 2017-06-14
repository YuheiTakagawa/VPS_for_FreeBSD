# $FreeBSD: projects/vps/sbin/nvmecontrol/Makefile 257008 2013-10-23 19:02:26Z will $

PROG=	nvmecontrol
SRCS=	nvmecontrol.c devlist.c firmware.c identify.c logpage.c	\
	perftest.c reset.c nvme_util.c
MAN=	nvmecontrol.8

.PATH:	${.CURDIR}/../../sys/dev/nvme

.include <bsd.prog.mk>
