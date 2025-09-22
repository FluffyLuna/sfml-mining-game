#pragma once

#include <SFML/Graphics.hpp>

/**
 * Player class represents the mining character controlled by the user
 * The player can move around the world and mine ores
 */
class Player {
private:
    sf::CircleShape shape;        // Visual representation of the player (a circle)
    sf::Vector2f position;        // Current position in the world
    sf::Vector2f velocity;        // Current movement velocity
    
    // Player stats that can be upgraded
    float miningSpeed;            // How fast the player mines (lower = faster)
    float miningRange;            // How close to ores the player needs to be
    float oreMultiplier;          // Multiplier for ore collection (upgrades increase this)
    
    // Movement constants
    static const float MOVE_SPEED;           // How fast the player moves
    static const float FRICTION;             // How quickly the player stops moving
    static const float MIN_VELOCITY;         // Minimum velocity before stopping

public:
    /**
     * Constructor creates a player at the specified position
     * @param startX - Starting X coordinate
     * @param startY - Starting Y coordinate
     */
    Player(float startX, float startY);
    
    /**
     * Update player movement and physics
     * @param deltaTime - Time elapsed since last update
     */
    void update(float deltaTime);
    
    /**
     * Handle keyboard input for movement
     * WASD or Arrow keys control movement
     */
    void handleInput();
    
    /**
     * Render the player to the screen
     * @param window - SFML window to draw to
     */
    void render(sf::RenderWindow& window);
    
    /**
     * Get the player's current position
     * @return Vector2f containing X and Y coordinates
     */
    sf::Vector2f getPosition() const;
    
    /**
     * Get the player's mining range (how close they need to be to mine)
     * @return Mining range in pixels
     */
    float getMiningRange() const;
    
    /**
     * Get the player's mining speed (time between mines)
     * @return Mining speed in seconds
     */
    float getMiningSpeed() const;
    
    /**
     * Get the ore collection multiplier
     * @return How many ores are collected per mine
     */
    float getOreMultiplier() const;
    
    /**
     * Upgrade the player's mining speed
     * @param improvement - Amount to improve speed by
     */
    void upgradeMiningSpeed(float improvement);
    
    /**
     * Upgrade the player's mining range
     * @param improvement - Amount to improve range by
     */
    void upgradeMiningRange(float improvement);
    
    /**
     * Upgrade the player's ore multiplier
     * @param improvement - Amount to improve multiplier by
     */
    void upgradeOreMultiplier(float improvement);
    
    /**
     * Keep the player within the window bounds
     * @param windowWidth - Width of the game window
     * @param windowHeight - Height of the game window
     */
    void constrainToWindow(int windowWidth, int windowHeight);
};