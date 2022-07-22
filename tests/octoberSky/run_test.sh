#!/bin/bash

rm -rf output

mkdir -p output

TEST_PATH=/tests/octoberSky/

export TESTING=1
export TARGET_UPDATE_DURATION_NS=0
export LOG_PATH=".${TEST_PATH}output/"
export TESTING_INPUT_FILE=".${TEST_PATH}input.txt"

cd ../../
./build-and-run.sh "${1}" MainLoop

cd .${TEST_PATH}

FAIL=0
for file in ./output-expected/*; do
    if ! diff "$file" "./output/${file##*/}"; then
        FAIL=1
        printf "\nError in the following file: ${file##*/}\n\n"
    fi
done

if [[ $FAIL = "1" ]]; then
    exit 1
fi