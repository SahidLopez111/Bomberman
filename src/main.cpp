#include "../include/Game.hpp"
#include <iostream>

/**
 * @brief Main entry point of the Bomberman game
 * @return Exit code (0 for success)
 */
int main() {
    std::cout << "=== Bomberman Game ===" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  Arrow Keys - Move" << std::endl;
    std::cout << "  Space - Place Bomb" << std::endl;
    std::cout << "=====================" << std::endl;
    
    // Create game instance
    Game game(800, 600);
    
    // Initialize game
    if (!game.initialize()) {
        std::cerr << "Failed to initialize game!" << std::endl;
        return 1;
    }
    
    // Run game loop
    game.run();
    
    std::cout << "Game ended. Thanks for playing!" << std::endl;
    
    return 0;
}

