cmake_minimum_required(VERSION 3.2)

project(seed-qt)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Sql REQUIRED)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} REQUIRED)

# Add src
add_subdirectory(${CMAKE_SOURCE_DIR}/src)

# Add test
add_subdirectory(${CMAKE_SOURCE_DIR}/test)
