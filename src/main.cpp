#include "game.h"
#include "renderer.h"
#include <iostream>

int main() {
    try {
        // Create game with default (medium) difficulty
        Game game;
        
        // Create and run the UI
        Renderer renderer(game);
        renderer.run();
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}