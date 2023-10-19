#!/bin/bash

# Clean and build the tests
make -s clean && make -s tests

# Define the directory and an array of executable names
dir=./tests/
exes=("lsh" "cube" "cluster")

# Iterate through the executable names and run the tests
for exe in "${exes[@]}"
do
    "$dir$exe"_test
done

# Clean up
make -s clean