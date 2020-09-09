# include files
include_directories(qtSeedDb qtSeedComms qtSeedApp)

# DB as static library
set(SEED_DB qtSeedDb)
add_subdirectory(qtSeedDb)

# Comms as static library
set(SEED_COMMS qtSeedComms)
add_subdirectory(qtSeedComms)

# Seed Application
add_subdirectory(qtSeedApp)
