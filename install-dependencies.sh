#!/bin/bash

if command -v apt >/dev/null; then
  # For apt-based distros (ex: Debian, Ubuntu, etc.)
  apt update
  apt install ninja-build cmake gcc g++ make libi2c-dev libboost-all-dev protobuf-compiler libsystemd-dev -y
elif command -v pacman >/dev/null; then
  # Arch based
  pacman -S ninja cmake gcc boost boost-libs make i2c-tools protobuf systemd-libs
elif command -v zypper >/dev/null; then
  # openSUSE
  zypper install ninja cmake-full gcc boost-devel make libi2c0-devel protobuf-devel systemd-devel
else
  echo "Your distro doesn't seem to be supported."
fi
