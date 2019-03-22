# Business as static library
file(GLOB_RECURSE SEED_BUSI_SRC "*.cpp")
file(GLOB_RECURSE SEED_BUSI_HDR "*.h")
add_library(${SEED_BUSI} STATIC ${SEED_BUSI_SRC} ${SEED_BUSI_HDR})
target_link_libraries(${SEED_BUSI} Qt5::Core Qt5::Quick Qt5::Sql)
