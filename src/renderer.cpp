#include "renderer.h"
#include <sstream>
#include <iostream>
#include <limits>

Renderer::Renderer(Game& game) : game_(game) {
}

void Renderer::run() {
    bool running = true;
    
    while (running) {
        clearScreen();
        
        if (showMenu_) {
            displayMenu();
        } else {
            displayGameScreen();
        }
        
        // Get input
        std::cout << "> ";
        std::getline(std::cin, input_);
        
        if (input_ == "exit" || input_ == "quit") {
            running = false;
        } else {
            processInput();
        }
    }
}

void Renderer::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

std::string Renderer::renderHangman() const {
    const int attempts = game_.getRemainingAttempts();
    const int maxAttempts = 6;  // Assuming max attempts is 6 for rendering purposes
    
    std::vector<std::string> hangmanStates = {
        // State 0: Start
        "  +---+\n"
        "  |   |\n"
        "      |\n"
        "      |\n"
        "      |\n"
        "      |\n"
        "=========",
        
        // State 1: Head
        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        "      |\n"
        "      |\n"
        "      |\n"
        "=========",
        
        // State 2: Head and Torso
        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        "  |   |\n"
        "      |\n"
        "      |\n"
        "=========",
        
        // State 3: Head, Torso, and One Arm
        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        " /|   |\n"
        "      |\n"
        "      |\n"
        "=========",
        
        // State 4: Head, Torso, and Both Arms
        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        " /|\\  |\n"
        "      |\n"
        "      |\n"
        "=========",
        
        // State 5: Head, Torso, Both Arms, and One Leg
        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        " /|\\  |\n"
        " /    |\n"
        "      |\n"
        "=========",
        
        // State 6: Full Hangman (Game Over)
        "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        " /|\\  |\n"
        " / \\  |\n"
        "      |\n"
        "========="
    };
    
    // Calculate which state to show based on remaining attempts
    int stateIndex = maxAttempts - attempts;
    if (stateIndex < 0) stateIndex = 0;
    if (stateIndex >= hangmanStates.size()) stateIndex = hangmanStates.size() - 1;
    
    return hangmanStates[stateIndex];
}

void Renderer::displayWord() const {
    std::cout << "Word: " << game_.getDisplayWord() << std::endl;
}

void Renderer::displayGuessedLetters() const {
    std::stringstream wrongGuesses;
    wrongGuesses << "Wrong: ";
    
    for (char c : game_.getWrongGuesses()) {
        wrongGuesses << c << " ";
    }
    
    std::cout << wrongGuesses.str() << std::endl;
}

void Renderer::displayGameInfo() const {
    std::cout << "Attempts remaining: " << game_.getRemainingAttempts() << std::endl;
    std::cout << "Score: " << game_.getScore() << std::endl;
}

void Renderer::displayStatusMessage() const {
    std::string message;
    
    switch (game_.getState()) {
        case Game::GameState::WON:
            message = "Congratulations! You guessed the word!";
            break;
        case Game::GameState::LOST:
            message = "Game over! The word was: " + game_.getWord();
            break;
        default:
            message = "Guess a letter...";
            break;
    }
    
    std::cout << message << std::endl;
}

void Renderer::processInput() {
    if (input_.empty()) {
        return;
    }
    
    char guess = input_[0];
    input_ = "";  // Clear input
    
    // Check for special commands
    if (guess == 'q' || guess == 'Q') {
        showMenu_ = true;
        return;
    }
    
    if ((guess == 'n' || guess == 'N') && 
        (game_.getState() == Game::GameState::WON || 
         game_.getState() == Game::GameState::LOST)) {
        startNewGame();
        return;
    }
    
    // Process letter guess
    if (game_.getState() == Game::GameState::IN_PROGRESS) {
        game_.makeGuess(guess);
    }
}

void Renderer::startNewGame() {
    game_.setDifficulty(selectedDifficulty_);
    game_.newGame();
}

void Renderer::displayMenu() {
    std::cout << "===== HANGMAN MENU =====" << std::endl;
    std::cout << "Select difficulty:" << std::endl;
    std::cout << "1. Easy" << std::endl;
    std::cout << "2. Medium" << std::endl;
    std::cout << "3. Hard" << std::endl;
    std::cout << "4. Back to game" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "======================" << std::endl;
    
    if (input_ == "1") {
        selectedDifficulty_ = Game::Difficulty::EASY;
        startNewGame();
        showMenu_ = false;
    } else if (input_ == "2") {
        selectedDifficulty_ = Game::Difficulty::MEDIUM;
        startNewGame();
        showMenu_ = false;
    } else if (input_ == "3") {
        selectedDifficulty_ = Game::Difficulty::HARD;
        startNewGame();
        showMenu_ = false;
    } else if (input_ == "4") {
        showMenu_ = false;
    } else if (input_ == "5") {
        exit(0);
    }
}

void Renderer::displayGameScreen() {
    std::cout << "===== HANGMAN =====" << std::endl;
    std::cout << renderHangman() << std::endl;
    displayWord();
    displayGuessedLetters();
    displayGameInfo();
    std::cout << "----------------" << std::endl;
    displayStatusMessage();
    
    if (game_.getState() != Game::GameState::IN_PROGRESS) {
        std::cout << "Press 'n' for new game or 'q' for menu" << std::endl;
    } else {
        std::cout << "Enter a letter (or 'q' for menu): ";
    }
    
    std::cout << std::endl;
    std::cout << "Instructions:" << std::endl;
    std::cout << "• Type a letter and press Enter to guess" << std::endl;
    std::cout << "• Press 'q' for menu" << std::endl;
    std::cout << "• Press 'n' for new game after winning/losing" << std::endl;
}
