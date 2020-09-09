cmake_minimum_required(VERSION 3.2)

project(seed-qt)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBS_DIR ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBS_DIR})
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

find_package(Qt5 COMPONENTS Core Quick Sql REQUIRED)

# Add src
add_subdirectory(${CMAKE_SOURCE_DIR}/src)

# Add test
add_subdirectory(${CMAKE_SOURCE_DIR}/test)
