#!/bin/bash

# check the number of arguments
[ $# -ne 2 ] && echo "USAGE: $0 MODE CORES" && exit 1

# assign the arguments
CORES=$2; MODE=$1; [ $MODE == "STATIC" ] && STATIC=1 || STATIC=0; [ $MODE == "SHARED" ] && SHARED=1 || SHARED=0; [ $SHARED -eq 0 ] && [ $STATIC -eq 0 ] && echo "INVALID MODE" && exit 1

# make the folders
mkdir -p external && mkdir -p external/include && mkdir -p external/lib

# download argparse
wget -q -O external/include/argparse.hpp https://raw.githubusercontent.com/p-ranav/argparse/master/include/argparse/argparse.hpp

# download gmp
wget -O external/libgmp.tar.xz https://gmplib.org/download/gmp/gmp-6.3.0.tar.xz

# unpack the archives
cd external && for ARCHIVE in *.tar.xz; do tar -xf $ARCHIVE --warning=no-unknown-keyword; done; cd ..

# compile gmp
cd external/gmp-6.3.0 && ./configure \
    --enable-cxx \
    --prefix="$PWD/install" \
    --enable-shared=$SHARED \
    --enable-static=$STATIC \
&& make -j$CORES && make install && cp -r install/* .. && cd ../..
