#!/bin/bash
echo "1000"
for i in {1..1000}
	do
		echo $((1 + RANDOM % 100));
	done
