# $FreeBSD: projects/vps/sys/modules/vmm/Makefile 245678 2013-01-20 03:42:49Z neel $

KMOD=	vmm

SRCS=	opt_ddb.h device_if.h bus_if.h pci_if.h

CFLAGS+= -DVMM_KEEP_STATS -DSMP
CFLAGS+= -I${.CURDIR}/../../amd64/vmm	
CFLAGS+= -I${.CURDIR}/../../amd64/vmm/io	
CFLAGS+= -I${.CURDIR}/../../amd64/vmm/intel

# generic vmm support
.PATH: ${.CURDIR}/../../amd64/vmm
SRCS+=	vmm.c		\
	vmm_dev.c	\
	vmm_host.c	\
	vmm_instruction_emul.c	\
	vmm_ipi.c	\
	vmm_lapic.c	\
	vmm_mem.c	\
	vmm_msr.c	\
	vmm_stat.c	\
	vmm_util.c	\
	x86.c		\
	vmm_support.S

.PATH: ${.CURDIR}/../../amd64/vmm/io
SRCS+=	iommu.c		\
	ppt.c           \
	vdev.c		\
	vlapic.c

# intel-specific files
.PATH: ${.CURDIR}/../../amd64/vmm/intel
SRCS+=	ept.c		\
	vmcs.c		\
	vmx_msr.c	\
	vmx.c		\
	vtd.c

# amd-specific files
.PATH: ${.CURDIR}/../../amd64/vmm/amd
SRCS+=	amdv.c

OBJS=	vmx_support.o

CLEANFILES=	vmx_assym.s vmx_genassym.o

vmx_assym.s:    vmx_genassym.o
.if exists(@)
vmx_assym.s:    @/kern/genassym.sh
.endif
	sh @/kern/genassym.sh vmx_genassym.o > ${.TARGET}

vmx_support.o:	vmx_support.S vmx_assym.s
	${CC} -c -x assembler-with-cpp -DLOCORE ${CFLAGS} \
	    ${.IMPSRC} -o ${.TARGET}

vmx_genassym.o: vmx_genassym.c @ machine x86
	${CC} -c ${CFLAGS:N-fno-common} ${.IMPSRC}

.include <bsd.kmod.mk>
