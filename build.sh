#!/bin/sh

set -e

for c in *.c
do
    o=$( basename "${c}" .c )
    gcc -g -O2 -std=gnu99 -fPIC -DPIC \
        -DHAVE_CONFIG_H -I. -I../.. -I../../include \
        -o ${o}.o -c ${c}
done

name=baddisk

gcc -shared -O2 -fPIC -DPIC \
-Wl,-soname \
-Wl,nbdkit-${name}-plugin.so \
-o nbdkit-${name}-plugin.so \
*.o
