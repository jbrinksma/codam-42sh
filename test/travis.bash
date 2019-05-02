#!/bin/bash

# exit when any command fails
set -e
# keep track of the last executed command
trap 'last_command=$current_command; current_command=$BASH_COMMAND' DEBUG
# echo an error message before exiting
trap 'echo "\"${last_command}\" command filed with exit code $?."' EXIT

#get first argument
os=$1

if [ $os == "macos" ]
then
	HOMEBREW_NO_AUTO_UPDATE=1 brew install snaipe/soft/criterion
	make test_norm
	make test_coverage
	bash <(curl -s https://codecov.io/bash)
elif [ $os == "linux" ]
then
	sudo add-apt-repository -y ppa:snaipewastaken/ppa
	sudo apt-get update
	sudo apt-get install -y criterion-dev
	make test
else
	echo "OS not found!"
	exit 42
fi
