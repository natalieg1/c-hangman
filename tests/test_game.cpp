#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/game.h"
#include <string>

TEST_CASE("Game initialization") {
    Game game;
    
    CHECK(game.getState() == Game::GameState::IN_PROGRESS);
    CHECK(game.getRemainingAttempts() > 0);
    CHECK(!game.getWord().empty());
    CHECK(game.getScore() == 0);
}

TEST_CASE("Game guess mechanics") {
    Game game;
    std::string word = game.getWord();
    
    // Test correct guess
    char correctLetter = word[0];
    bool guessResult = game.makeGuess(correctLetter);
    CHECK(guessResult);
    CHECK(game.getAllGuesses().count(correctLetter) == 1);
    
    // Test wrong guess
    char wrongLetter = 'z';
    // Make sure our wrong letter isn't in the word
    while (word.find(wrongLetter) != std::string::npos) {
        wrongLetter--;
    }
    
    int initialAttempts = game.getRemainingAttempts();
    guessResult = game.makeGuess(wrongLetter);
    CHECK(guessResult);
    CHECK(game.getAllGuesses().count(wrongLetter) == 1);
    CHECK(game.getRemainingAttempts() == initialAttempts - 1);
    
    // Test duplicate guess
    guessResult = game.makeGuess(correctLetter);
    CHECK(!guessResult);  // Should return false for duplicate
}

TEST_CASE("Game state changes") {
    Game game;
    std::string word = game.getWord();
    
    // Force a loss
    int maxAttempts = game.getRemainingAttempts();
    char wrongLetter = 'z';
    
    for (int i = 0; i < maxAttempts; i++) {
        // Make sure our wrong letter isn't in the word
        while (word.find(wrongLetter) != std::string::npos) {
            wrongLetter--;
        }
        
        game.makeGuess(wrongLetter--);
    }
    
    CHECK(game.getState() == Game::GameState::LOST);
    
    // New game and force a win
    game.newGame();
    word = game.getWord();
    
    // Guess all letters in the word
    for (char c : word) {
        if (game.getAllGuesses().count(c) == 0) {
            game.makeGuess(c);
        }
    }
    
    CHECK(game.getState() == Game::GameState::WON);
    CHECK(game.getScore() > 0);
}

TEST_CASE("Difficulty settings") {
    Game easyGame(Game::Difficulty::EASY);
    Game mediumGame(Game::Difficulty::MEDIUM);
    Game hardGame(Game::Difficulty::HARD);
    
    // Easy should have more attempts than hard
    CHECK(easyGame.getRemainingAttempts() > hardGame.getRemainingAttempts());
}