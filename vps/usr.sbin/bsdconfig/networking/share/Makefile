# $FreeBSD: projects/vps/usr.sbin/bsdconfig/networking/share/Makefile 257008 2013-10-23 19:02:26Z will $

NO_OBJ=

FILESDIR=	${SHAREDIR}/bsdconfig/networking
FILES=		common.subr device.subr hostname.subr ipaddr.subr media.subr \
		netmask.subr resolv.subr routing.subr services.subr

beforeinstall:
	mkdir -p ${DESTDIR}${FILESDIR}

.include <bsd.prog.mk>
