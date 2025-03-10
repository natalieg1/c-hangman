#ifndef HANGMAN_WORD_LIST_H
#define HANGMAN_WORD_LIST_H

#include <string>
#include <vector>

class WordList {
public:
    WordList();
    
    // Get a random word
    std::string getRandomWord();
    
    // Get a random word with length between min and max
    std::string getRandomWord(int minLength, int maxLength);
    
    // Add a word to the list
    void addWord(const std::string& word);
    
    // Load words from file
    bool loadFromFile(const std::string& filename);
    
    // Get the number of words
    size_t size() const;

private:
    std::vector<std::string> words_;
    
    // Load default words if no file is available
    void loadDefaultWords();
};

#endif // HANGMAN_WORD_LIST_H