#!/bin/sh
python ~/norminette+/run.py --version
output=$(python ~/norminette+/run.py $TRAVIS_BUILD_DIR/makefile $TRAVIS_BUILD_DIR/includes $TRAVIS_BUILD_DIR/srcs | grep -E '^Error' -B 1)
if [ "$output" = "" ]
then
    exit 0
else
    echo "$output"
    exit 42
fi
