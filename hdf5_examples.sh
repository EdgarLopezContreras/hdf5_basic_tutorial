#!/bin/bash

# Compiling
echo "Compiling"
mkdir build
cd build
cmake ..
make
echo "Compiled successfully"

# Creating hdf5 file
cd ..
echo "Running writing example"
./writing_hdf5_example

# Reading hdf5 file
echo "Running reading example"
./reading_hdf5_example