/**
 * @file main.cpp
 * @brief Entry point for the SFML Mining Game
 * 
 * This file demonstrates the basic structure of an SFML application:
 * - Simple main function with exception handling
 * - Game object creation and lifecycle management
 * - Clean program termination
 * 
 * The main function in game development is typically kept minimal,
 * with most logic delegated to a main Game class for better organization.
 */

#include <iostream>
#include <stdexcept>
#include "Game.h"

/**
 * @brief Main entry point for the SFML Mining Game
 * 
 * This function demonstrates proper C++ application structure:
 * - Exception handling for graceful error recovery
 * - Resource management through RAII
 * - Clear separation between initialization and execution
 * 
 * @return 0 on successful execution, non-zero on error
 */
int main() {
    try {
        // Create the main game object
        // This handles all SFML initialization and resource loading
        Game game;
        
        // Run the main game loop
        // This method doesn't return until the game exits
        game.run();
        
        // Clean exit
        std::cout << "Game ended successfully!" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        // Handle any errors that occur during game initialization or execution
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Press Enter to exit..." << std::endl;
        std::cin.get();
        return -1;
        
    } catch (...) {
        // Handle any other unexpected errors
        std::cerr << "An unknown error occurred!" << std::endl;
        std::cerr << "Press Enter to exit..." << std::endl;
        std::cin.get();
        return -1;
    }
}