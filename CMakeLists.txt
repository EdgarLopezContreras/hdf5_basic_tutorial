cmake_minimum_required(VERSION 3.10)
project(writing_hdf5)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

find_package(HDF5 REQUIRED COMPONENTS CXX)

if(NOT HDF5_FOUND)
    message(FATAL_ERROR "HDF5 was not found.")
endif()

include_directories(${HDF5_INCLUDE_DIRS})
    
add_executable(writing_hdf5_example writing_hdf5_example.cpp)
add_executable(reading_hdf5_example reading_hdf5_example.cpp)

target_link_libraries(writing_hdf5_example PRIVATE ${HDF5_LIBRARIES})
target_link_libraries(reading_hdf5_example PRIVATE ${HDF5_LIBRARIES})