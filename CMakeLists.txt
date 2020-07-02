cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(tsw-logger)

add_definitions(-DRAPIDJSON_HAS_STDSTRING)

set(CMAKE_CXX_FLAGS "-Wall")

file(GLOB "${PROJECT_NAME}_HEADERS" include/tsw_logger/*.h)
file(GLOB "${PROJECT_NAME}_SRC" impl/*.cpp impl/*.h impl/**/*.cpp impl/**/*.h)

add_subdirectory(third_party/baical_p7)

add_library("${PROJECT_NAME}" SHARED "${${PROJECT_NAME}_HEADERS}" "${${PROJECT_NAME}_SRC}")
target_include_directories("${PROJECT_NAME}" PUBLIC "include")
target_link_libraries("${PROJECT_NAME}" p7)

