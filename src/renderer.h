#ifndef HANGMAN_RENDERER_H
#define HANGMAN_RENDERER_H

#include "game.h"
#include <string>
#include <iostream>

class Renderer {
public:
    Renderer(Game& game);
    
    // Start the UI
    void run();

private:
    Game& game_;
    std::string input_;
    bool showMenu_{false};
    Game::Difficulty selectedDifficulty_{Game::Difficulty::MEDIUM};
    
    // Create the hangman ASCII art
    std::string renderHangman() const;
    
    // Render the word display
    void displayWord() const;
    
    // Render the guessed letters
    void displayGuessedLetters() const;
    
    // Render game info (score, attempts)
    void displayGameInfo() const;
    
    // Render game status message
    void displayStatusMessage() const;
    
    // Process input
    void processInput();
    
    // Start a new game
    void startNewGame();
    
    // Display menu
    void displayMenu();
    
    // Display main game screen
    void displayGameScreen();
    
    // Clear screen (platform-dependent)
    void clearScreen();
};

#endif // HANGMAN_RENDERER_H