#include "game.h"
#include "word_list.h"
#include <algorithm>

Game::Game() : Game(Difficulty::MEDIUM) {}

Game::Game(Difficulty difficulty) 
    : state_(GameState::IN_PROGRESS), 
      score_(0),
      difficulty_(difficulty) {
    newGame();
}

void Game::newGame() {
    WordList wordList;
    
    // Select word based on difficulty
    switch (difficulty_) {
        case Difficulty::EASY:
            word_ = wordList.getRandomWord(4, 6);
            remainingAttempts_ = 8;
            break;
        case Difficulty::MEDIUM:
            word_ = wordList.getRandomWord(6, 9);
            remainingAttempts_ = 6;
            break;
        case Difficulty::HARD:
            word_ = wordList.getRandomWord(9, 15);
            remainingAttempts_ = 5;
            break;
    }
    
    // Convert word to lowercase
    std::transform(word_.begin(), word_.end(), word_.begin(), 
                  [](unsigned char c){ return std::tolower(c); });
    
    // Reset game state
    correctGuesses_.clear();
    wrongGuesses_.clear();
    allGuesses_.clear();
    state_ = GameState::IN_PROGRESS;
    
    // Initialize display word
    updateDisplayWord();
}

bool Game::makeGuess(char letter) {
    // Convert to lowercase
    letter = std::tolower(letter);
    
    // Check if already guessed
    if (allGuesses_.find(letter) != allGuesses_.end()) {
        return false;
    }
    
    // Add to guesses
    allGuesses_.insert(letter);
    
    // Check if letter is in the word
    if (word_.find(letter) != std::string::npos) {
        correctGuesses_.insert(letter);
    } else {
        wrongGuesses_.insert(letter);
        remainingAttempts_--;
    }
    
    // Update game state
    updateGameState();
    updateDisplayWord();
    
    return true;
}

void Game::updateGameState() {
    // Check if player has won
    bool allLettersGuessed = true;
    for (char c : word_) {
        if (correctGuesses_.find(c) == correctGuesses_.end()) {
            allLettersGuessed = false;
            break;
        }
    }
    
    if (allLettersGuessed) {
        state_ = GameState::WON;
        score_ += word_.length() * 10;
        
        // Bonus points for remaining attempts
        score_ += remainingAttempts_ * 5;
        
        // Difficulty bonus
        switch (difficulty_) {
            case Difficulty::EASY:
                score_ += 10;
                break;
            case Difficulty::MEDIUM:
                score_ += 25;
                break;
            case Difficulty::HARD:
                score_ += 50;
                break;
        }
    } else if (remainingAttempts_ <= 0) {
        state_ = GameState::LOST;
    }
}

void Game::updateDisplayWord() {
    displayWord_ = "";
    for (char c : word_) {
        if (correctGuesses_.find(c) != correctGuesses_.end()) {
            displayWord_ += c;
        } else {
            displayWord_ += "_";
        }
        displayWord_ += " ";
    }
}

Game::GameState Game::getState() const {
    return state_;
}

std::string Game::getWord() const {
    return word_;
}

std::string Game::getDisplayWord() const {
    return displayWord_;
}

const std::set<char>& Game::getWrongGuesses() const {
    return wrongGuesses_;
}

const std::set<char>& Game::getAllGuesses() const {
    return allGuesses_;
}

int Game::getRemainingAttempts() const {
    return remainingAttempts_;
}

int Game::getScore() const {
    return score_;
}

void Game::setDifficulty(Difficulty difficulty) {
    difficulty_ = difficulty;
}