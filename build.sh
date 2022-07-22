#!/bin/bash

# Args: Profile Generator Target

./install-conan.sh ${1} ${2}
cmake --build build --target "${3:-MainLoop}"
