#!/bin/bash

git submodule update --init
mkdir -p build
cd build
cmake .. -G "${1:-Ninja}"
cmake --build ./ --target "${2:-MainLoop}"