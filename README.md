# 1. HDF5 Basic Tutorial

*Author: Edgar López-Contreras*  
*Date: April 2025*

## 1.1. What is HDF5?

A file format designed to store large amounts of data with a hierarchical structure, similar to a file system with folders and files. It has support for C, C++, Fortran, Python, Julia, R, Java, and others.

### 1.1.1. Advantages
- Hierarchical structure: groups (similar to folders) and datasets (similar to files).
- Stored in binary format.
- Compression support: gzip, szip, etc.
- Chunking: datasets can be stored in blocks of desired size.
- Efficient random and sequential reading.
- Each group and dataset can have additional data (metadata).
- Support for multiple data types (numbers, text, images, matrices, etc.).
- Parallel reading and writing support.

## 1.2. Basic Implementation in C++

### 1.2.1. Installation

To install the C and C++ libraries on Ubuntu:

```bash
sudo apt install libhdf5-dev libhdf5-cpp-dev
```

### 1.2.2. Writing Example Code

An example of a writing code is `writing_hdf5_example.cpp`.

### 1.2.3. Reading Example Code

An example of a reading code is `reading_hdf5_example.cpp`.

## 1.3. Compiling

The easiest way to compile these codes is via CMake, for example with `CMakeLists.txt`.

## 1.4. Visualizing Data

After compiling `writing_hdf5_example.cpp` and running the compiled program, the file `data.h5` will be created. To visualize its content, run the compiled program from `reading_hdf5_example.cpp`. You can also use the H5Web extension in VS Code.

## 1.5. Complete Process

You can run the bash code `hdf5_examples.sh` to compile and run the codes.

## 1.6. Credits
This project uses HDF5, developed and maintained by The HDF Group (https://www.hdfgroup.org), 
under a BSD-style license.
