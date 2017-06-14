# $FreeBSD: projects/vps/tools/regression/sbin/dhclient/Makefile 257008 2013-10-23 19:02:26Z will $

.PATH:	${.CURDIR}/../../../../sbin/dhclient

SRCS=	alloc.c convert.c hash.c options.c tables.c			\
	fake.c								\
	option-domain-search.c

CFLAGS+= -I${.CURDIR}/../../../../sbin/dhclient
LDADD=	-lutil

PROG=	option-domain-search

NO_MAN=
WARNS?=	2

.include <bsd.prog.mk>
