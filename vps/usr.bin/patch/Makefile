#	$OpenBSD: Makefile,v 1.4 2005/05/16 15:22:46 espie Exp $
# $FreeBSD: projects/vps/usr.bin/patch/Makefile 257008 2013-10-23 19:02:26Z will $

.include <bsd.own.mk>

.if ${MK_GNU_PATCH} == "yes"
PROG=	bsdpatch
CLEANFILES+= bsdpatch.1

bsdpatch.1: patch.1
	cp ${.ALLSRC} ${.TARGET}
.else
PROG=	patch
.endif

SRCS=	backupfile.c inp.c mkpath.c patch.c pch.c util.c

.include <bsd.prog.mk>
