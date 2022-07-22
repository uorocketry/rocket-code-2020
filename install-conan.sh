#!/bin/bash

rm -rf build
mkdir -p build && cd build
conan install ..  --build=missing  --profile "${1:-default}"
cmake .. -B . -G "${2:-Ninja}" -DCMAKE_BUILD_TYPE=Release