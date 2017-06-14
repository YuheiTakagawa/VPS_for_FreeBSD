# $FreeBSD: projects/vps/gnu/usr.bin/dialog/Makefile 257008 2013-10-23 19:02:26Z will $

DIALOG=	${.CURDIR}/../../../contrib/dialog
PROG=   dialog

DPADD=	${LIBDIALOG} ${LIBNCURSESW} ${LIBM}
LDADD=	-ldialog -lncursesw -lm
CFLAGS+= -I${.CURDIR} -I${DIALOG}
.PATH:	${DIALOG}

WARNS?= 6

.include <bsd.prog.mk>
