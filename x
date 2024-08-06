#!/bin/sh

SRC="codegen.c"
OUT="codegen"
CC="gcc"
CFLAGS="-Wall -Wextra -Wpedantic -fomit-frame-pointer -ggdb -std=c99"

set -xe

${CC} -o ${OUT} ${SRC} ${CFLAGS}

./${OUT}

#${CC} -o linear_algebra_test test.c ${CFLAGS} -fdata-sections -ffunction-sections -Wl,--gc-sections
#./linear_algebra_test
