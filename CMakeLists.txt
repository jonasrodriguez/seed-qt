cmake_minimum_required(VERSION 3.1)

project(QTSeed LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Sql REQUIRED)

# include
include_directories(${CMAKE_SOURCE_DIR}/interfaces ${CMAKE_SOURCE_DIR}/src/qtSeedUI ${CMAKE_SOURCE_DIR}/src/qtSeedBusiness)
include_directories(${CMAKE_SOURCE_DIR}/src/qtSeedComms ${CMAKE_SOURCE_DIR}/src/qtSeedDb)

# Looking for files
file(GLOB_RECURSE SRC "src/*.cpp" )
file(GLOB_RECURSE HDR "src/*.h" "interfaces/*.h" )
file(GLOB_RECURSE QRC "src/*qrc")

add_executable(${PROJECT_NAME} ${SRC} ${HDR} ${QRC})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick Qt5::Sql)
