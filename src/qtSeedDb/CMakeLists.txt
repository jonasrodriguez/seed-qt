# DB as static library
file(GLOB_RECURSE SEED_DB_SRC "*.cpp")
file(GLOB_RECURSE SEED_DB_HDR "*.h")
add_library(${SEED_DB} STATIC ${SEED_DB_SRC} ${SEED_DB_HDR})
target_link_libraries(${SEED_DB} Qt5::Core Qt5::Quick Qt5::Sql)
