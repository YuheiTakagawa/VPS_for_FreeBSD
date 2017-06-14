# $FreeBSD: projects/vps/gnu/usr.bin/patch/Makefile 257008 2013-10-23 19:02:26Z will $

.include <bsd.own.mk>

.if ${MK_GNU_PATCH} == "yes"
PROG=	patch
.else
PROG=	gnupatch
CLEANFILES+= gnupatch.1

gnupatch.1: patch.1
	cp ${.ALLSRC} ${.TARGET}
.endif

SRCS=   backupfile.c inp.c patch.c pch.c util.c version.c
CFLAGS+=-DHAVE_CONFIG_H

.include <bsd.prog.mk>
