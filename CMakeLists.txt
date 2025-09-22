cmake_minimum_required(VERSION 3.16)
project(MiningGame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML package
find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED sfml-all>=2.6)

# Add source files
set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Player.cpp
    src/Ore.cpp
    src/Inventory.cpp
    src/Shop.cpp
)

# Add header files
set(HEADERS
    include/Game.h
    include/Player.h
    include/Ore.h
    include/Inventory.h
    include/Shop.h
)

# Create executable
add_executable(mining_game ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(mining_game PRIVATE include)

# Link SFML libraries
target_link_libraries(mining_game ${SFML_LIBRARIES})
target_include_directories(mining_game PRIVATE ${SFML_INCLUDE_DIRS})
target_compile_options(mining_game PRIVATE ${SFML_CFLAGS_OTHER})

# Set output directory
set_target_properties(mining_game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)