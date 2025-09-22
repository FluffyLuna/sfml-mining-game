#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

/**
 * Enumeration for the different types of ores in the game
 * Each ore has different rarity and value for trading
 */
enum class OreType {
    COPPER,     // Most common, lowest value
    IRON,       // Common, moderate value  
    GOLD,       // Uncommon, high value
    DIAMOND     // Rare, highest value
};

/**
 * Ore class represents a minable resource in the game world
 * Each ore has a type, position, and visual representation
 */
class Ore {
private:
    OreType type;                    // What type of ore this is
    sf::CircleShape shape;           // Visual representation (colored circle)
    sf::Vector2f position;           // Position in the world
    
    // Static color mapping for different ore types
    static sf::Color getColorForType(OreType type);
    
    // Static rarity weights for ore spawning
    static float getRarityWeight(OreType type);

public:
    /**
     * Constructor creates an ore of specified type at given position
     * @param oreType - Type of ore to create
     * @param x - X coordinate position
     * @param y - Y coordinate position
     */
    Ore(OreType oreType, float x, float y);
    
    /**
     * Static method to create a random ore at specified position
     * Uses weighted random selection based on ore rarity
     * @param x - X coordinate position
     * @param y - Y coordinate position
     * @return Unique pointer to the created ore
     */
    static std::unique_ptr<Ore> createRandomOre(float x, float y);
    
    /**
     * Render the ore to the screen
     * @param window - SFML window to draw to
     */
    void render(sf::RenderWindow& window);
    
    /**
     * Get the ore's current position
     * @return Vector2f containing X and Y coordinates
     */
    sf::Vector2f getPosition() const;
    
    /**
     * Get the ore's type
     * @return OreType enumeration value
     */
    OreType getType() const;
    
    /**
     * Get the trading value of this ore type
     * Used by the shop system to determine upgrade costs
     * @return Integer value of the ore
     */
    int getValue() const;
    
    /**
     * Get the name of this ore type as a string
     * Useful for UI display
     * @return String name of the ore
     */
    std::string getName() const;
    
    /**
     * Get the radius of the ore's collision circle
     * Used for mining collision detection
     * @return Radius in pixels
     */
    float getRadius() const;
    
    /**
     * Check if a point is within mining range of this ore
     * @param point - Position to check
     * @param range - Mining range distance
     * @return true if within range, false otherwise
     */
    bool isWithinRange(sf::Vector2f point, float range) const;
};