#!/bin/sh
# $FreeBSD: projects/vps/tools/regression/lib/msun/test-lround.t 140089 2005-01-11 23:13:36Z das $

cd `dirname $0`

executable=`basename $0 .t`

make $executable 2>&1 > /dev/null

exec ./$executable
