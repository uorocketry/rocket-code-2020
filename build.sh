#!/bin/bash

set -euf -o pipefail

mkdir -p build
cd build
cmake .. -G "${1:-Ninja}"
cmake --build ./ --target "${2:-all}"