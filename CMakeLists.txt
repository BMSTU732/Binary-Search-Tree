cmake_minimum_required(VERSION 2.8.7)
project(BinarySearchTree)
install (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include  DESTINATION include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(TESTS_SOURCES tests/main.cpp tests/find.cpp tests/size.cpp tests/insert.cpp tests/remove.cpp)

add_executable(Tests ${TESTS_SOURCES} tests/main.cpp)

