# Add UI files
file(GLOB_RECURSE SRC "Logic/*.cpp" "Views/*.cpp" "main.cpp")
file(GLOB_RECURSE HDR "Logic/*.h" "Views/*.h")
file(GLOB_RECURSE QRC "qml/*.qrc"  )

add_executable(${PROJECT_NAME} ${SRC} ${HDR} ${QRC})

target_link_libraries(${PROJECT_NAME} ${SEED_COMMS} ${SEED_DB} Qt5::Core Qt5::Quick Qt5::Sql)
