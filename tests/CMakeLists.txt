cmake_minimum_required(VERSION 3.14)

# Download doctest
include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)

# Add the test executable
add_executable(test_game
    test_game.cpp
    ${CMAKE_SOURCE_DIR}/src/game.cpp
    ${CMAKE_SOURCE_DIR}/src/word_list.cpp
)

# Include directories
target_include_directories(test_game PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${doctest_SOURCE_DIR}/doctest
)

# Link libraries
target_link_libraries(test_game PRIVATE
    doctest::doctest
)

# Copy assets to the test build directory
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Register tests
include(CTest)
add_test(NAME GameTests COMMAND test_game)