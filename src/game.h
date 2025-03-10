#ifndef HANGMAN_GAME_H
#define HANGMAN_GAME_H

#include <string>
#include <set>
#include <vector>

class Game {
public:
    enum class GameState {
        IN_PROGRESS,
        WON,
        LOST
    };

    enum class Difficulty {
        EASY,
        MEDIUM,
        HARD
    };

    Game();
    explicit Game(Difficulty difficulty);
    
    // Start a new game
    void newGame();
    
    // Make a guess
    bool makeGuess(char letter);
    
    // Get current game state
    GameState getState() const;
    
    // Get the word to guess
    std::string getWord() const;
    
    // Get the current display word (with _ for unguessed letters)
    std::string getDisplayWord() const;
    
    // Get wrong guesses
    const std::set<char>& getWrongGuesses() const;
    
    // Get all guesses
    const std::set<char>& getAllGuesses() const;
    
    // Get remaining attempts
    int getRemainingAttempts() const;
    
    // Get total score
    int getScore() const;
    
    // Set difficulty
    void setDifficulty(Difficulty difficulty);

private:
    std::string word_;
    std::set<char> correctGuesses_;
    std::set<char> wrongGuesses_;
    std::set<char> allGuesses_;
    GameState state_;
    int remainingAttempts_;
    int score_;
    Difficulty difficulty_;
    
    void updateGameState();
    void updateDisplayWord();
    std::string displayWord_;
};

#endif // HANGMAN_GAME_H