# Hangman

A simple command-line Hangman game implemented in C++.

## Description

This is a classic Hangman game where players try to guess a word letter by letter. The game randomly selects words from a word list and gives players a limited number of attempts to guess the word correctly.

## Features

- Random word selection from a customizable word list
- ASCII art for the hangman states
- Colorful terminal output using the FTXUI library
- Score tracking
- Difficulty levels

## Dependencies

- [CMake](https://cmake.org/) (>=3.14)
- C++17 compatible compiler

## Installation

### Prerequisites

1. Install CMake:
   - Windows: Download and install from [cmake.org](https://cmake.org/download/)
   - macOS: `brew install cmake`
   - Ubuntu/Debian: `sudo apt-get install cmake`

### Building the Project

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/hangman.git
   cd hangman
   ```

2. Configure and build with CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

## Usage

After building, run the executable:

```bash
# From the build directory
./hangman
```

### Game Controls

- Type a letter and press Enter to make a guess
- Press 'q' to quit the current game
- Press 'n' for a new game after winning or losing

## Project Structure

```
hangman/
├── CMakeLists.txt            # Main CMake configuration
├── src/                      # Source files
│   ├── main.cpp              # Entry point
│   ├── game.cpp              # Game logic
│   ├── game.h                # Game header
│   ├── word_list.cpp         # Word list management
│   ├── word_list.h           # Word list header
│   ├── renderer.cpp          # Display rendering
│   └── renderer.h            # Renderer header
├── assets/                   # Game assets
│   └── words.json            # Word list
├── include/                  # External includes (if any)
├── tests/                    # Unit tests
│   ├── CMakeLists.txt        # Test configuration
│   └── test_game.cpp         # Game tests
└── vcpkg.json                # vcpkg manifest for dependencies
```
