# $FreeBSD: projects/vps/usr.sbin/bsdconfig/share/media/Makefile 257008 2013-10-23 19:02:26Z will $

NO_OBJ=

FILESDIR=	${SHAREDIR}/bsdconfig/media
FILES=		any.subr cdrom.subr common.subr directory.subr dos.subr \
		floppy.subr ftp.subr http.subr httpproxy.subr network.subr \
		nfs.subr options.subr tcpip.subr ufs.subr usb.subr

beforeinstall:
	mkdir -p ${DESTDIR}${FILESDIR}

.include <bsd.prog.mk>
