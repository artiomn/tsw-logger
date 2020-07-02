cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(tsw_logger)

add_definitions(-DRAPIDJSON_HAS_STDSTRING)

set(CMAKE_CXX_FLAGS "-Wall")

file(GLOB headers include/tsw_logger/*.h)
file(GLOB src impl/*.cpp impl/*.h impl/**/*.cpp impl/**/*.h)

target_link_libraries(${PROJECT_NAME} P7_static)

