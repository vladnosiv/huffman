cmake_minimum_required(VERSION 3.0)

project(HuffmanArchiverTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

include_directories("../include/")

set(SOURCE_FILES TestMain.cpp TestHuffmanArchiver.cpp ../src/HuffmanArchiver.cpp ../src/Huffman.cpp ../src/bin_manip.cpp)

add_executable(test_hw_03 ${SOURCE_FILES})
