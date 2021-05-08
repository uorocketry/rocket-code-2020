#!/bin/bash

set -euf -o pipefail

./build.sh "$1" "$2" && ./run.sh