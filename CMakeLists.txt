cmake_minimum_required(VERSION 3.3)
project(DBC_v4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp main.h UnionFindSets.h)
add_executable(DBC_v4 ${SOURCE_FILES})