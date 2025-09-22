cmake_minimum_required(VERSION 3.16)
project(SFMLMiningGame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML 3.0.1
find_package(SFML 3.0.1 COMPONENTS graphics window system audio REQUIRED)

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h" "include/*.hpp")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio)

# Copy assets to build directory
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Set properties for better debugging
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Add compile options for better warnings and debugging
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<COMPILER_ID:MSVC>:/W4>
)