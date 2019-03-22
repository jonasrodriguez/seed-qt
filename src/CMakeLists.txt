# include files
include_directories(qtSeedUI qtSeedComms qtSeedDb qtSeedBusiness)

# DB as static library
set(SEED_DB qtSeedDb)
add_subdirectory(qtSeedDb)

# Comms as static library
set(SEED_COMMS qtSeedComms)
add_subdirectory(qtSeedComms)

# Business as static library
set(SEED_BUSI qtSeedBusiness)
add_subdirectory(qtSeedBusiness)

# Add UI files
file(GLOB_RECURSE SRC "qtSeedUI/*.cpp" "main.cpp")
file(GLOB_RECURSE HDR "qtSeedUI/*.h")
file(GLOB_RECURSE QRC "qtSeedUI/*.qrc"  )

add_executable(${PROJECT_NAME} ${SRC} ${HDR} ${QRC})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick Qt5::Sql)
target_link_libraries(${PROJECT_NAME} ${SEED_BUSI} ${SEED_COMMS} ${SEED_DB})
