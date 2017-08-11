# $FreeBSD: projects/vps/sys/modules/yarrow_rng/Makefile 253786 2013-07-29 20:58:09Z obrien $

.PATH: ${.CURDIR}/../../dev/random
.PATH: ${.CURDIR}/../../crypto/rijndael

KMOD=	yarrow_rng

SRCS+=	\
	hash.c \
	randomdev_soft.c \
	rijndael-alg-fst.c \
	rijndael-api-fst.c \
	yarrow.c

SRCS+=	bus_if.h device_if.h

CFLAGS+= -I${.CURDIR}/../..

.include <bsd.kmod.mk>
