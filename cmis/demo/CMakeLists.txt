cmake_minimum_required(VERSION 3.15)
project(CMIS-demo)

set(CMAKE_CXX_STANDARD 23)
# msvc /std:c++latest
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

add_executable(CMIS-demo demo.cpp)