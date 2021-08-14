#!/usr/bin/env bash

set -euf -o pipefail

# Download and build boost for arm following the guide:
# https://github.com/Yadoms/yadoms/wiki/Cross-compile-for-raspberry-PI

LIBI2C_VERSION=4.3
LIBI2C_DIRECTORY="i2c-tools-$LIBI2C_VERSION"

curl -fLO "https://mirrors.edge.kernel.org/pub/software/utils/i2c-tools/$LIBI2C_DIRECTORY.tar.gz"

tar -xf "$LIBI2C_DIRECTORY.tar.gz"

cd "$LIBI2C_DIRECTORY"

make