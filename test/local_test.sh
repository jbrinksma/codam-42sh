#!/bin/sh
./vsh_tests
return=$(echo $?)
if [ "$return" == "0" ]
then
	echo "Test succeeded"
	exit 0
else
	echo "Test failed"
	exit 42
fi
