#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Player.h"
#include "Ore.h"
#include "Inventory.h"
#include "Shop.h"

/**
 * Main Game class that manages the entire mining game
 * This class follows the typical game loop pattern:
 * 1. Handle input (keyboard, mouse)
 * 2. Update game state (player movement, ore spawning, etc.)
 * 3. Render everything to the screen
 */
class Game {
private:
    // SFML window for rendering the game
    sf::RenderWindow window;
    
    // Game objects
    std::unique_ptr<Player> player;           // The player character
    std::unique_ptr<Inventory> inventory;     // Player's ore inventory
    std::unique_ptr<Shop> shop;               // Shop for upgrades
    std::vector<std::unique_ptr<Ore>> ores;   // All ores in the game world
    
    // Game state flags
    bool showShop;                            // Whether the shop is currently open
    
    // Ore spawning system
    sf::Clock oreSpawnClock;                  // Timer for spawning new ores
    float oreSpawnInterval;                   // How often to spawn ores (in seconds)
    
    // UI elements
    sf::Font font;                            // Font for text rendering
    sf::Text instructionText;                // Instructions for the player
    sf::Text inventoryText;                   // Display inventory contents
    
    // Constants for game balance
    static const int WINDOW_WIDTH = 1024;
    static const int WINDOW_HEIGHT = 768;
    static const int MAX_ORES = 50;          // Maximum ores on screen at once

public:
    /**
     * Constructor initializes the game window and all game objects
     */
    Game();
    
    /**
     * Main game loop - runs until the window is closed
     * This is where the magic happens!
     */
    void run();

private:
    /**
     * Handle all input events (keyboard, mouse, window events)
     * @param event - SFML event to process
     */
    void handleEvents(sf::Event& event);
    
    /**
     * Update all game objects and game state
     * @param deltaTime - Time elapsed since last update (for smooth movement)
     */
    void update(float deltaTime);
    
    /**
     * Render all game objects to the screen
     */
    void render();
    
    /**
     * Spawn a new ore at a random location
     * This keeps the game interesting by continuously adding new ores to mine
     */
    void spawnOre();
    
    /**
     * Check if the player is close enough to mine an ore
     * @param ore - The ore to check collision with
     * @return true if player can mine this ore
     */
    bool canMineOre(const Ore& ore) const;
    
    /**
     * Handle mining an ore (remove it from world, add to inventory)
     * @param oreIndex - Index of the ore in the ores vector
     */
    void mineOre(size_t oreIndex);
    
    /**
     * Update the inventory display text
     */
    void updateInventoryDisplay();
    
    /**
     * Toggle the shop display on/off
     */
    void toggleShop();
};