#!/usr/bin/env bash

set -euf -o pipefail

if [ -z "$RPI_TOOLS" ]; then
  echo "RPI_TOOLS not specified, exiting..." >> /dev/stderr
  exit 1
fi

if [ -z "$BOOST_DIRECTORY" ]; then
  echo "BOOST_DIRECTORY not specified, exiting..." >> /dev/stderr
  exit 1
fi

mkdir -p build-arm
cd build-arm
cmake .. -G "${1:-Ninja}" -DCMAKE_TOOLCHAIN_FILE=../toolchain-rpi.cmake
cmake --build ./ --target "${2:-all}"
