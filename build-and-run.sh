#!/bin/bash

cd ./sbgEcom/projects/unix
cmake -G 'Unix Makefiles'
make

cd ../../bin

./MainLoop