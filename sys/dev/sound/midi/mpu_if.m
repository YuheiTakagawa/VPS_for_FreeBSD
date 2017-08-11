#-
# Copyright (c) 2003 Mathew Kanner
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
# $FreeBSD: projects/vps/sys/dev/sound/midi/mpu_if.m 166971 2007-02-25 13:51:52Z netchild $
#

#include <dev/sound/midi/midi.h>

INTERFACE mpu;

METHOD int inqsize {
	struct snd_midi *_kobj;
	void   *_cookie;
};

METHOD int outqsize {
	struct snd_midi *_kobj;
	void   *_cookie;
};

METHOD int init {
	struct snd_midi *_kobj;
	void   *_cookie;
};

METHOD void callbackp {
	struct snd_midi *_kobj;
	void   *_cookie;
	int	_flags;
};

METHOD void callback {
	struct snd_midi *_kobj;
	void   *_cookie;
	int	_flags;
};

METHOD const char * provider {
	struct snd_midi *_kobj;
	void   *_cookie;
};

METHOD const char * descr {
	struct snd_midi *_kobj;
	void   *_cookie;
	int	_verbosity;
};

METHOD int uninit {
	struct snd_midi *_kobj;
	void   *_cookie;
};
