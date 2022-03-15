#!/bin/bash

export USE_GPIO=1
./build.sh Ninja tests
./build/unitTesting/tests