#pragma once

#include <SFML/Graphics.hpp>
#include <string>

/**
 * @brief Enumeration of the four different ore types in the game
 * 
 * Each ore type has different rarity and value, creating a natural
 * progression system where players work toward rarer materials.
 */
enum class OreType {
    Copper,     ///< Most common ore - used for basic upgrades
    Iron,       ///< Common ore - intermediate upgrades  
    Gold,       ///< Rare ore - advanced upgrades
    Diamond     ///< Very rare ore - best upgrades
};

/**
 * @brief Ore class represents collectible materials from mining
 * 
 * This class demonstrates:
 * - Enum-based type systems for game items
 * - Value/rarity balance in game economics
 * - String conversion for UI display
 * - Color coding for visual feedback
 * 
 * Ores are the primary resource in the mining game, so their design
 * affects the entire game economy and progression system.
 */
class Ore {
public:
    /**
     * @brief Constructor creates an ore of the specified type
     * 
     * @param type The type of ore to create
     */
    explicit Ore(OreType type);
    
    /**
     * @brief Get the ore type
     * @return The OreType enum value
     */
    OreType getType() const { return m_type; }
    
    /**
     * @brief Get the trade value of this ore
     * 
     * This value is used in the shop system for purchasing upgrades.
     * The values are balanced to create meaningful choices and progression.
     * 
     * @return The trade value of this ore
     */
    int getValue() const { return m_value; }
    
    /**
     * @brief Get the display name of this ore type
     * 
     * This demonstrates string conversion from enums for UI display.
     * Useful for inventory screens, tooltips, and trading interfaces.
     * 
     * @return Human-readable name of the ore
     */
    std::string getName() const { return m_name; }
    
    /**
     * @brief Get the color associated with this ore type
     * 
     * Each ore has a distinct color for easy visual identification:
     * - Copper: Orange/brown
     * - Iron: Gray
     * - Gold: Yellow
     * - Diamond: Light blue/white
     * 
     * @return SFML Color for this ore type
     */
    sf::Color getColor() const { return m_color; }
    
    /**
     * @brief Get the rarity factor of this ore (0.0 to 1.0)
     * 
     * Lower values mean rarer ores. This is used by the world generator
     * to determine how often this ore appears in the terrain.
     * 
     * @return Rarity value where 0.0 = never appears, 1.0 = always appears
     */
    float getRarity() const { return m_rarity; }
    
    /**
     * @brief Static method to get ore properties by type
     * 
     * This factory-like method centralizes ore property definition,
     * making it easy to balance the game economy and add new ore types.
     * 
     * @param type The ore type to get properties for
     * @return Ore object with appropriate properties
     */
    static Ore createOre(OreType type);

private:
    OreType m_type;         ///< The type of this ore
    int m_value;            ///< Trade value for shop purchases
    std::string m_name;     ///< Display name for UI
    sf::Color m_color;      ///< Visual color for rendering
    float m_rarity;         ///< How rare this ore is (affects world generation)
    
    /**
     * @brief Initialize ore properties based on type
     * 
     * This method sets up all the properties that make each ore type unique:
     * - Trade values for economic balance
     * - Names for UI display
     * - Colors for visual distinction
     * - Rarity for world generation
     * 
     * The values here directly affect game balance and player progression.
     */
    void initializeProperties();
};

/**
 * @brief Utility functions for ore management
 * 
 * These functions provide common operations needed throughout the game
 * for ore handling and display.
 */
namespace OreUtils {
    /**
     * @brief Convert ore type to string for display
     * 
     * @param type The ore type to convert
     * @return String representation of the ore type
     */
    std::string oreTypeToString(OreType type);
    
    /**
     * @brief Get all ore types in order of value (cheapest to most expensive)
     * 
     * This is useful for shop displays and progression systems.
     * 
     * @return Vector of ore types sorted by value
     */
    std::vector<OreType> getAllOreTypes();
    
    /**
     * @brief Calculate total value of a collection of ores
     * 
     * Used for inventory value calculation and trade validation.
     * 
     * @param ores Vector of ores to calculate total value for
     * @return Total combined value of all ores
     */
    int calculateTotalValue(const std::vector<Ore>& ores);
}