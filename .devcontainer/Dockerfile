FROM mcr.microsoft.com/vscode/devcontainers/base:debian

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    build-essential \
    cmake \
    ninja-build \
    libi2c-dev \
    libboost-all-dev \
    protobuf-compiler \
    libprotobuf-dev \
    libsystemd-dev
