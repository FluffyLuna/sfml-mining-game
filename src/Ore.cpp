#include "Ore.h"
#include <algorithm>

/**
 * @brief Constructor initializes ore with specified type
 * 
 * This demonstrates the initialization pattern where the constructor
 * delegates complex setup to a separate method for clarity.
 */
Ore::Ore(OreType type) : m_type(type) {
    initializeProperties();
}

/**
 * @brief Initialize ore properties based on type
 * 
 * This method centralizes all ore balance values, making it easy to
 * adjust game economy without hunting through multiple files.
 * The values here directly affect game progression and player motivation.
 */
void Ore::initializeProperties() {
    switch (m_type) {
        case OreType::Copper:
            m_value = 1;                                    // Least valuable - starter resource
            m_name = "Copper";
            m_color = sf::Color(184, 115, 51);              // Orange-brown color
            m_rarity = 0.15f;                               // 15% chance - fairly common
            break;
            
        case OreType::Iron:
            m_value = 3;                                    // 3x more valuable than copper
            m_name = "Iron";
            m_color = sf::Color(169, 169, 169);             // Gray color
            m_rarity = 0.08f;                               // 8% chance - less common
            break;
            
        case OreType::Gold:
            m_value = 8;                                    // 8x more valuable than copper
            m_name = "Gold";
            m_color = sf::Color(255, 215, 0);               // Golden yellow
            m_rarity = 0.03f;                               // 3% chance - rare
            break;
            
        case OreType::Diamond:
            m_value = 20;                                   // 20x more valuable than copper
            m_name = "Diamond";
            m_color = sf::Color(185, 242, 255);             // Light blue-white
            m_rarity = 0.008f;                              // 0.8% chance - very rare
            break;
    }
}

/**
 * @brief Factory method to create ore with proper initialization
 * 
 * This static method provides a clean way to create ores from external code
 * while ensuring all properties are properly initialized.
 */
Ore Ore::createOre(OreType type) {
    return Ore(type);
}

// Utility functions implementation
namespace OreUtils {
    
    /**
     * @brief Convert ore type enum to display string
     * 
     * This function demonstrates enum-to-string conversion, essential
     * for UI display and debugging output.
     */
    std::string oreTypeToString(OreType type) {
        switch (type) {
            case OreType::Copper:   return "Copper";
            case OreType::Iron:     return "Iron";
            case OreType::Gold:     return "Gold";
            case OreType::Diamond:  return "Diamond";
            default:                return "Unknown";
        }
    }
    
    /**
     * @brief Get all ore types sorted by value (cheapest to most expensive)
     * 
     * This is useful for shop displays and progression visualization.
     * The order reflects the intended progression path for players.
     */
    std::vector<OreType> getAllOreTypes() {
        return {
            OreType::Copper,    // Value: 1  - Starting resource
            OreType::Iron,      // Value: 3  - Early upgrade material
            OreType::Gold,      // Value: 8  - Mid-game resource
            OreType::Diamond    // Value: 20 - End-game resource
        };
    }
    
    /**
     * @brief Calculate total value of a collection of ores
     * 
     * This function demonstrates aggregation operations common in games:
     * - Iterating over collections
     * - Accumulating values based on item properties
     * - Providing summary statistics for player feedback
     */
    int calculateTotalValue(const std::vector<Ore>& ores) {
        int totalValue = 0;
        
        // Sum up the value of each individual ore
        for (const auto& ore : ores) {
            totalValue += ore.getValue();
        }
        
        return totalValue;
    }
}