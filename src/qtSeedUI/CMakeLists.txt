# DB as static library
set(SEED_UI qtSeedUI)
file(GLOB_RECURSE SEED_UI_SRC "*.cpp")
file(GLOB_RECURSE SEED_UI_HDR "*.h")
file(GLOB_RECURSE SEED_UI_QRC "*.qrc"  )
add_library(${SEED_UI} STATIC ${SEED_UI_SRC} ${SEED_UI_HDR} ${SEED_UI_QRC})
target_link_libraries(${SEED_UI} Qt5::Core Qt5::Quick Qt5::Sql)
