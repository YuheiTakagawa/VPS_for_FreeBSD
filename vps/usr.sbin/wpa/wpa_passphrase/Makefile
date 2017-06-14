# $FreeBSD: projects/vps/usr.sbin/wpa/wpa_passphrase/Makefile 257008 2013-10-23 19:02:26Z will $

.include "${.CURDIR}/../Makefile.inc"

.PATH.c:${WPA_SUPPLICANT_DISTDIR}

PROG=	wpa_passphrase
SRCS=	common.c md5-internal.c md5.c os_unix.c sha1-internal.c sha1-pbkdf2.c sha1.c \
	wpa_passphrase.c

CFLAGS+= -DINTERNAL_SHA1
CFLAGS+= -DINTERNAL_MD5

MAN=	wpa_passphrase.8

.include <bsd.prog.mk>
