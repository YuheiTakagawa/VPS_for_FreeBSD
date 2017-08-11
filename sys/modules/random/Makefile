# $FreeBSD: projects/vps/sys/modules/random/Makefile 257008 2013-10-23 19:02:26Z will $

.PATH: ${.CURDIR}/../../dev/random

KMOD=	random
SRCS=	randomdev.c probe.c
SRCS+=	bus_if.h device_if.h opt_cpu.h

.include <bsd.kmod.mk>
