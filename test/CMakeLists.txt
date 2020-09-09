cmake_minimum_required(VERSION 3.2)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(${SOURCE_DIR}/qtSeedDb ${SOURCE_DIR}/qtSeedComms ${SOURCE_DIR}/qtSeedApp)

# Comms Test
add_executable(TestComms TestComms.cpp)
target_link_libraries(TestComms ${GTEST_LIBRARIES} pthread)
target_link_libraries(TestComms qtSeedComms qtSeedDb)

# Comms Test
add_executable(TestDb TestDb.cpp)
target_link_libraries(TestDb ${GTEST_LIBRARIES} pthread)
target_link_libraries(TestDb qtSeedComms qtSeedDb)
