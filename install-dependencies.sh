#!/bin/bash

if command -v apt >/dev/null; then
  # For apt-based distros (ex: Debian, Ubuntu, etc.)
  apt update
  apt install ninja-build cmake gcc g++ make libi2c-dev libboost-all-dev protobuf-compiler -y
else
  echo "Your distro doesn't seem to be supported."
fi