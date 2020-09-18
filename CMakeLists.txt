cmake_minimum_required(VERSION 3.0)

project(HuffmanArchiver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

include_directories("include/")

set(SOURCE_FILES src/main.cpp src/Huffman.cpp src/HuffmanArchiver.cpp src/bin_manip.cpp src/CLI.cpp)

add_subdirectory("./test")

add_executable(hw_03 ${SOURCE_FILES})
