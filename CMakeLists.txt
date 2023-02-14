cmake_minimum_required(VERSION 3.14)

project(ckzg LANGUAGES C)

# set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_C_STANDARD 11)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/blst.cmake)

add_subdirectory(src)
include_directories(inc)
