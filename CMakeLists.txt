cmake_minimum_required(VERSION 2.6)
project(libdsmr)

set (CMAKE_CXX_STANDARD 17)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(dsmr SHARED
	source/defaultparser.cpp
	source/fields.cpp
)

add_executable(dsmr_2 examples/dsmr_2.cpp)
add_executable(dsmr_4 examples/dsmr_4.cpp)

