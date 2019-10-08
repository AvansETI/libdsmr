cmake_minimum_required(VERSION 2.6)
project(libdsmr)

set (CMAKE_CXX_STANDARD 17)
set(JSON_BuildTests OFF CACHE INTERNAL "")

include_directories(${PROJECT_SOURCE_DIR}/include
	external/json/single_include)

add_subdirectory(external/json)

add_library(dsmr SHARED
	source/defaultparser.cpp
	source/fields.cpp
)

target_link_libraries(dsmr PRIVATE nlohmann_json::nlohmann_json)

add_executable(dsmr_2 examples/dsmr_2.cpp)
target_link_libraries(dsmr_2 PUBLIC dsmr)
add_executable(dsmr_4 examples/dsmr_4.cpp)
target_link_libraries(dsmr_4 PUBLIC dsmr)

