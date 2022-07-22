#!/bin/bash

cmake -B build -S . -G "${1:-Ninja}"
cmake --build build --target "${2:-MainLoop}"
