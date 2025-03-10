#include "word_list.h"
#include <fstream>
#include <random>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <sstream>

WordList::WordList() {
    try {
        if (!loadFromFile("assets/words.txt")) {
            loadDefaultWords();
        }
    } catch (const std::exception& e) {
        loadDefaultWords();
    }
}

std::string WordList::getRandomWord() {
    if (words_.empty()) {
        throw std::runtime_error("Word list is empty");
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, words_.size() - 1);
    
    return words_[distrib(gen)];
}

std::string WordList::getRandomWord(int minLength, int maxLength) {
    if (words_.empty()) {
        throw std::runtime_error("Word list is empty");
    }
    
    std::vector<std::string> filteredWords;
    std::copy_if(words_.begin(), words_.end(), std::back_inserter(filteredWords),
                 [minLength, maxLength](const std::string& word) {
                     return word.length() >= minLength && word.length() <= maxLength;
                 });
    
    if (filteredWords.empty()) {
        return getRandomWord();  // Fallback to any word if no matching length
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, filteredWords.size() - 1);
    
    return filteredWords[distrib(gen)];
}

void WordList::addWord(const std::string& word) {
    if (!word.empty()) {
        words_.push_back(word);
    }
}

bool WordList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    try {
        std::string line;
        while (std::getline(file, line)) {
            // Skip empty lines
            if (line.empty()) {
                continue;
            }
            
            // Remove whitespace
            line.erase(std::remove_if(line.begin(), line.end(), 
                                    [](unsigned char c) { return std::isspace(c); }),
                     line.end());
            
            if (!line.empty()) {
                addWord(line);
            }
        }
    } catch (const std::exception& e) {
        return false;
    }
    
    return !words_.empty();
}

size_t WordList::size() const {
    return words_.size();
}

void WordList::loadDefaultWords() {
    // Default word list if file loading fails
    const std::vector<std::string> defaultWords = {
        "computer", "programming", "hangman", "algorithm", "variable",
        "function", "keyboard", "monitor", "software", "hardware",
        "network", "database", "language", "compiler", "debugging",
        "interface", "library", "terminal", "memory", "storage",
        "pointer", "array", "loop", "condition", "structure",
        "binary", "integer", "floating", "boolean", "character"
    };
    
    words_ = defaultWords;
}
