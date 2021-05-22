#!/usr/bin/env bash

set -euf -o pipefail

# Download and build boost for arm following the guide:
# https://github.com/Yadoms/yadoms/wiki/Cross-compile-for-raspberry-PI

if [ -z "$RPI_TOOLS" ]; then
  echo "RPI_TOOLS not specified, exiting..." > /dev/stderr
  exit 1
fi

BOOST_VERSION=1.76.0
BOOST_DIRECTORY="boost_${BOOST_VERSION//\./_}"

curl -fLO "https://sourceforge.net/projects/boost/files/boost/$BOOST_VERSION/$BOOST_DIRECTORY.tar.bz2"

tar xjf "$BOOST_DIRECTORY.tar.bz2"

cd "$BOOST_DIRECTORY"

./bootstrap.sh

CONFIG_JAM=$(mktemp)

echo "using gcc : arm : $RPI_TOOLS/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-g++ ;" > "$CONFIG_JAM"

./b2 --user-config="$CONFIG_JAM" --with-system --with-filesystem --no-samples --no-tests toolset=gcc-arm link=static cxxflags=-fPIC

rm "$CONFIG_JAM"
