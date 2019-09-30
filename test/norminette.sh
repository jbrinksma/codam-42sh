#!/bin/sh
python $HOME/norminette+/run.py --version
output=$(python $HOME/norminette+/run.py $GITHUB_WORKSPACE/includes $GITHUB_WORKSPACE/libft $GITHUB_WORKSPACE/srcs | grep -E '^Error' -B 1)
if [ "$output" = "" ]
then
    exit 0
else
    echo "$output"
    exit 42
fi
