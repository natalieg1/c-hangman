cmake_minimum_required(VERSION 3.14)
project(hangman VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(hangman
    src/main.cpp
    src/game.cpp
    src/word_list.cpp
    src/renderer.cpp
)

# Include directories
target_include_directories(hangman PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Copy assets to the build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Add tests
option(BUILD_TESTS "Build test programs" OFF)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

# Install targets
install(TARGETS hangman
    RUNTIME DESTINATION bin
)