#!/bin/bash

cd ./sbgECom/projects/unix
cmake -G 'Unix Makefiles'
make

cd ../../bin

./MainLoop