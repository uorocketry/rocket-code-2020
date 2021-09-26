#!/bin/bash

shopt -s globstar

GLOBIGNORE='libraries/**'

clang-format -i **/*.cpp **/*.h **/*.proto
