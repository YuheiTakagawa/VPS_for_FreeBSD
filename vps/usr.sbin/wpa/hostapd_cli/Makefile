# $FreeBSD: projects/vps/usr.sbin/wpa/hostapd_cli/Makefile 257008 2013-10-23 19:02:26Z will $

.include "${.CURDIR}/../Makefile.inc"

.PATH.c:${HOSTAPD_DISTDIR}

PROG=	hostapd_cli
SRCS=	common.c edit.c eloop.c hostapd_cli.c os_unix.c wpa_ctrl.c wpa_debug.c

CFLAGS+= -DCONFIG_CTRL_IFACE
CFLAGS+= -DCONFIG_CTRL_IFACE_UNIX

MAN=	hostapd_cli.8

.include <bsd.prog.mk>
