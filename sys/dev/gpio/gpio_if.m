#-
# Copyright (c) 2009 Oleksandr Tymoshenko <gonzo@freebsd.org>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#
# $FreeBSD: projects/vps/sys/dev/gpio/gpio_if.m 213237 2010-09-28 03:24:53Z gonzo $
#

#include <sys/bus.h>
#include <sys/gpio.h>

INTERFACE gpio;

#
# Get total number of pins
#
METHOD int pin_max {
	device_t dev;
	int *npins;
};

#
# Set value of pin specifed by pin_num 
#
METHOD int pin_set {
	device_t dev;
	uint32_t pin_num;
	uint32_t pin_value;
};

#
# Get value of pin specifed by pin_num 
#
METHOD int pin_get {
	device_t dev;
	uint32_t pin_num;
	uint32_t *pin_value;
};

#
# Toggle value of pin specifed by pin_num 
#
METHOD int pin_toggle {
	device_t dev;
	uint32_t pin_num;
};

#
# Get pin capabilities
#
METHOD int pin_getcaps {
	device_t dev;
	uint32_t pin_num;
	uint32_t *caps;
};

#
# Get pin flags
#
METHOD int pin_getflags {
	device_t dev;
	uint32_t pin_num;
	uint32_t *flags;
};

#
# Get pin name
#
METHOD int pin_getname {
	device_t dev;
	uint32_t pin_num;
	char *name;
};

#
# Set current configuration and capabilities
#
METHOD int pin_setflags {
	device_t dev;
	uint32_t pin_num;
	uint32_t flags;
};
