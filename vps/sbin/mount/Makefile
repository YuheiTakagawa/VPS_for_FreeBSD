#	@(#)Makefile	8.6 (Berkeley) 5/8/95
# $FreeBSD: projects/vps/sbin/mount/Makefile 257008 2013-10-23 19:02:26Z will $

PROG=	mount
SRCS=	mount.c mount_fs.c getmntopts.c vfslist.c
MAN=	mount.8 mount.conf.8
# We do NOT install the getmntopts.3 man page.

DPADD=	${LIBUTIL}
LDADD=	-lutil

.include <bsd.prog.mk>
