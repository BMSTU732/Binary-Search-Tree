cmake_minimum_required(VERSION 2.8.7)
project(BinarySearchTree)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES examples/main.cpp include/BinarySearchTree.h sources/BinarySearchTree.cpp)
add_executable(BinarySearchTree ${SOURCE_FILES})
add_executable(tests ${TESTS_SOURCE})
