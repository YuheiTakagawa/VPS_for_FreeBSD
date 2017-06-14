/*-
 * Copyright (c) 2011-2012 Stefan Bethke.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: projects/vps/sys/dev/etherswitch/etherswitch.c 250381 2013-05-08 20:46:54Z adrian $
 */

#include <sys/param.h>
#include <sys/bus.h>
#include <sys/conf.h>
#include <sys/fcntl.h>
#include <sys/lock.h>
#include <sys/kernel.h>
#include <sys/malloc.h>
#include <sys/module.h>
#include <sys/socket.h>
#include <sys/sx.h>
#include <sys/systm.h>
#include <sys/uio.h>

#include <net/if.h>

#include <dev/etherswitch/etherswitch.h>

#include "etherswitch_if.h"

#define BUFSIZE 1024

struct etherswitch_softc {
	device_t sc_dev;
	int sc_count;

	struct cdev *sc_devnode;
	struct sx sc_lock;
};

#define	SWITCH_LOCK(sc)			sx_xlock(&(sc)->sc_lock)
#define	SWITCH_UNLOCK(sc)			sx_xunlock(&(sc)->sc_lock)

static int etherswitch_probe(device_t);
static int etherswitch_attach(device_t);
static int etherswitch_detach(device_t);
static void etherswitch_identify(driver_t *driver, device_t parent);

devclass_t etherswitch_devclass;

static device_method_t etherswitch_methods[] = {
	/* device interface */
	DEVMETHOD(device_identify,	etherswitch_identify),
	DEVMETHOD(device_probe,		etherswitch_probe),
	DEVMETHOD(device_attach,	etherswitch_attach),
	DEVMETHOD(device_detach,	etherswitch_detach),

	{ 0, 0 }
};

driver_t etherswitch_driver = {
	"etherswitch",
	etherswitch_methods,
	sizeof(struct etherswitch_softc),
};

static	d_open_t	etherswitchopen;
static	d_close_t	etherswitchclose;
static	d_write_t	etherswitchwrite;
static	d_read_t	etherswitchread;
static	d_ioctl_t	etherswitchioctl;

static struct cdevsw etherswitch_cdevsw = {
	.d_version =	D_VERSION,
	.d_flags =	D_TRACKCLOSE,
	.d_open =	etherswitchopen,
	.d_close =	etherswitchclose,
	.d_read =	etherswitchread,
	.d_write =	etherswitchwrite,
	.d_ioctl =	etherswitchioctl,
	.d_name =	"etherswitch",
};

static void
etherswitch_identify(driver_t *driver, device_t parent)
{
	if (device_find_child(parent, "etherswitch", -1) == NULL)
		BUS_ADD_CHILD(parent, 0, "etherswitch", -1);
}

static int
etherswitch_probe(device_t dev)
{
	device_set_desc(dev, "Switch controller");

	return (0);
}
	
static int
etherswitch_attach(device_t dev)
{
	struct etherswitch_softc *sc = (struct etherswitch_softc *)device_get_softc(dev);

	sc->sc_dev = dev;
	sx_init(&sc->sc_lock, "etherswitch");
	sc->sc_devnode = make_dev(&etherswitch_cdevsw, device_get_unit(dev),
			UID_ROOT, GID_WHEEL,
			0600, "etherswitch%d", device_get_unit(dev));
	if (sc->sc_devnode == NULL) {
		device_printf(dev, "failed to create character device\n");
		sx_destroy(&sc->sc_lock);
		return (ENXIO);
	}
	sc->sc_devnode->si_drv1 = sc;

	return (0);
}

static int
etherswitch_detach(device_t dev)
{
	struct etherswitch_softc *sc = (struct etherswitch_softc *)device_get_softc(dev);

	if (sc->sc_devnode)
		destroy_dev(sc->sc_devnode);
	sx_destroy(&sc->sc_lock);

	return (0);
}

static int
etherswitchopen(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	struct etherswitch_softc *sc = dev->si_drv1;

	SWITCH_LOCK(sc);
	if (sc->sc_count > 0) {
		SWITCH_UNLOCK(sc);
		return (EBUSY);
	}

	sc->sc_count++;
	SWITCH_UNLOCK(sc);

	return (0);
}

static int
etherswitchclose(struct cdev *dev, int flags, int fmt, struct thread *td)
{
	struct etherswitch_softc *sc = dev->si_drv1;

	SWITCH_LOCK(sc);
	if (sc->sc_count == 0) {
		SWITCH_UNLOCK(sc);
		return (EINVAL);
	}

	sc->sc_count--;

	if (sc->sc_count < 0)
		panic("%s: etherswitch_count < 0!", __func__);
	SWITCH_UNLOCK(sc);

	return (0);
}

static int
etherswitchwrite(struct cdev *dev, struct uio * uio, int ioflag)
{
	return (EINVAL);
}

static int
etherswitchread(struct cdev *dev, struct uio * uio, int ioflag)
{
	return (EINVAL);
}

static int
etherswitchioctl(struct cdev *cdev, u_long cmd, caddr_t data, int flags, struct thread *td)
{
	struct etherswitch_softc *sc = cdev->si_drv1;
	device_t dev = sc->sc_dev;
	device_t etherswitch = device_get_parent(dev);
	etherswitch_conf_t conf;
	etherswitch_info_t *info;
	etherswitch_reg_t *reg;
	etherswitch_phyreg_t *phyreg;
	int error = 0;

	switch (cmd) {
	case IOETHERSWITCHGETINFO:
		info = ETHERSWITCH_GETINFO(etherswitch);
		bcopy(info, data, sizeof(etherswitch_info_t));
		break;
		
	case IOETHERSWITCHGETREG:
		reg = (etherswitch_reg_t *)data;
		ETHERSWITCH_LOCK(etherswitch);
		reg->val = ETHERSWITCH_READREG(etherswitch, reg->reg);
		ETHERSWITCH_UNLOCK(etherswitch);
		break;
	
	case IOETHERSWITCHSETREG:
		reg = (etherswitch_reg_t *)data;
		ETHERSWITCH_LOCK(etherswitch);
		error = ETHERSWITCH_WRITEREG(etherswitch, reg->reg, reg->val);
		ETHERSWITCH_UNLOCK(etherswitch);
		break;

	case IOETHERSWITCHGETPORT:
		error = ETHERSWITCH_GETPORT(etherswitch, (etherswitch_port_t *)data);
		break;

	case IOETHERSWITCHSETPORT:
		error = ETHERSWITCH_SETPORT(etherswitch, (etherswitch_port_t *)data);
		break;

	case IOETHERSWITCHGETVLANGROUP:
		error = ETHERSWITCH_GETVGROUP(etherswitch, (etherswitch_vlangroup_t *)data);
		break;

	case IOETHERSWITCHSETVLANGROUP:
		error = ETHERSWITCH_SETVGROUP(etherswitch, (etherswitch_vlangroup_t *)data);
		break;

	case IOETHERSWITCHGETPHYREG:
		phyreg = (etherswitch_phyreg_t *)data;
		phyreg->val = ETHERSWITCH_READPHYREG(etherswitch, phyreg->phy, phyreg->reg);
		break;
	
	case IOETHERSWITCHSETPHYREG:
		phyreg = (etherswitch_phyreg_t *)data;
		error = ETHERSWITCH_WRITEPHYREG(etherswitch, phyreg->phy, phyreg->reg, phyreg->val);
		break;

	case IOETHERSWITCHGETCONF:
		bzero(&conf, sizeof(etherswitch_conf_t));
		error = ETHERSWITCH_GETCONF(etherswitch, &conf);
		bcopy(&conf, data, sizeof(etherswitch_conf_t));
		break;

	case IOETHERSWITCHSETCONF:
		error = ETHERSWITCH_SETCONF(etherswitch, (etherswitch_conf_t *)data);
		break;

	default:
		error = ENOTTY;
	}

	return (error);
}

MODULE_VERSION(etherswitch, 1);