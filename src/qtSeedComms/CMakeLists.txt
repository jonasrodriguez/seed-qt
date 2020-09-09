# Comms as static library
file(GLOB_RECURSE SEED_COMMS_SRC "*.cpp")
file(GLOB_RECURSE SEED_COMMS_HDR "*.h")
add_library(${SEED_COMMS} STATIC ${SEED_COMMS_SRC} ${SEED_COMMS_HDR})
target_link_libraries(${SEED_COMMS} Qt5::Core Qt5::Quick Qt5::Sql)
