cmake_minimum_required(VERSION 3.2)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(${SOURCE_DIR}/qtSeedDb ${SOURCE_DIR}/qtSeedBusiness ${SOURCE_DIR}/qtSeedComms)

add_executable(TestComms TestComms.cpp)
target_link_libraries(TestComms ${GTEST_LIBRARIES} pthread)
target_link_libraries(TestComms qtSeedComms qtSeedDb qtSeedBusiness)
