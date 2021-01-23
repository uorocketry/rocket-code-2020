mkdir -p output

TEST_PATH=/tests/octoberSky/

export TESTING=1
export TARGET_UPDATE_DURATION_NS=0
export LOG_PATH="../..${TEST_PATH}output/"
export TESTING_INPUT_FILE="../..${TEST_PATH}result.txt"

cd ../../
./build-and-run.sh

cd .${TEST_PATH}

for file in ./output-expected/*; do
    diff "$file" "./output/${file##*/}" || FAIL=1
done

rm -rf output

if [ $FAIL = "1" ]; then
    exit 1
fi