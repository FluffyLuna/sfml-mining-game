#include "Inventory.h"
#include <sstream>
#include <iomanip>

/**
 * @brief Constructor initializes empty inventory
 * 
 * The map-based approach automatically handles missing entries
 * by returning 0 for ore types not yet collected.
 */
Inventory::Inventory() {
    // Initialize all ore types to 0 count
    // This ensures consistent behavior and prevents map lookup issues
    for (auto oreType : OreUtils::getAllOreTypes()) {
        m_oreCounts[oreType] = 0;
    }
}

/**
 * @brief Add a single ore to inventory
 * 
 * This method demonstrates safe item addition with automatic
 * type detection and quantity tracking.
 */
void Inventory::addOre(const Ore& ore) {
    m_oreCounts[ore.getType()]++;
    updateStatistics();
}

/**
 * @brief Add multiple ores of the same type
 * 
 * Convenience method for bulk operations like mining bonuses
 * or administrative commands.
 */
void Inventory::addOres(OreType oreType, int quantity) {
    if (quantity > 0) {
        m_oreCounts[oreType] += quantity;
        updateStatistics();
    }
}

/**
 * @brief Remove ores from inventory
 * 
 * This method demonstrates safe resource consumption with
 * validation to prevent negative quantities.
 */
bool Inventory::removeOres(OreType oreType, int quantity) {
    if (quantity <= 0) {
        return true;  // Nothing to remove
    }
    
    auto it = m_oreCounts.find(oreType);
    if (it == m_oreCounts.end() || it->second < quantity) {
        return false;  // Not enough ores
    }
    
    it->second -= quantity;
    updateStatistics();
    return true;
}

/**
 * @brief Get count of specific ore type
 */
int Inventory::getOreCount(OreType oreType) const {
    auto it = m_oreCounts.find(oreType);
    return (it != m_oreCounts.end()) ? it->second : 0;
}

/**
 * @brief Get total count of all ores
 * 
 * This method demonstrates aggregation across collections,
 * useful for inventory space calculations and statistics.
 */
int Inventory::getTotalOreCount() const {
    int total = 0;
    for (const auto& pair : m_oreCounts) {
        total += pair.second;
    }
    return total;
}

/**
 * @brief Calculate total value of inventory
 * 
 * This method shows how to calculate derived statistics
 * by combining item quantities with their individual properties.
 */
int Inventory::getTotalValue() const {
    int totalValue = 0;
    
    for (const auto& pair : m_oreCounts) {
        if (pair.second > 0) {  // Only process ores we actually have
            Ore sampleOre(pair.first);
            totalValue += sampleOre.getValue() * pair.second;
        }
    }
    
    return totalValue;
}

/**
 * @brief Check if inventory has enough ores for a recipe
 * 
 * This method demonstrates prerequisite validation common
 * in crafting and upgrade systems.
 */
bool Inventory::hasEnoughOres(const std::map<OreType, int>& requiredOres) const {
    for (const auto& requirement : requiredOres) {
        OreType oreType = requirement.first;
        int requiredQuantity = requirement.second;
        
        if (getOreCount(oreType) < requiredQuantity) {
            return false;  // Missing required ore
        }
    }
    
    return true;  // All requirements met
}

/**
 * @brief Get formatted inventory display string
 * 
 * This method demonstrates data formatting for UI presentation,
 * converting internal game data into human-readable format.
 */
std::string Inventory::getInventoryDisplay() const {
    std::ostringstream oss;
    oss << "=== INVENTORY ===\n";
    
    bool hasAnyOres = false;
    
    // Display each ore type with count and value
    for (auto oreType : OreUtils::getAllOreTypes()) {
        int count = getOreCount(oreType);
        if (count > 0) {
            hasAnyOres = true;
            Ore sampleOre(oreType);
            int individualValue = sampleOre.getValue();
            int totalValue = individualValue * count;
            
            oss << sampleOre.getName() << ": " << count 
                << " (worth " << totalValue << " total)\n";
        }
    }
    
    if (!hasAnyOres) {
        oss << "Empty - go mining to find ores!\n";
    } else {
        oss << "\nTotal Ores: " << getTotalOreCount() << "\n";
        oss << "Total Value: " << getTotalValue() << "\n";
    }
    
    return oss.str();
}

/**
 * @brief Clear all ores from inventory
 */
void Inventory::clear() {
    for (auto& pair : m_oreCounts) {
        pair.second = 0;
    }
    updateStatistics();
}

/**
 * @brief Check if inventory is empty
 */
bool Inventory::isEmpty() const {
    return getTotalOreCount() == 0;
}

/**
 * @brief Update internal statistics
 * 
 * This method would handle complex inventory updates in larger games.
 * Currently simple but shows where such functionality would go.
 */
void Inventory::updateStatistics() {
    // In a more complex game, this might:
    // - Update UI displays
    // - Check for achievement triggers
    // - Log inventory changes
    // - Update save game data
    // - Recalculate encumbrance/weight
    
    // For now, this is a placeholder for future functionality
}

// Utility functions implementation
namespace InventoryUtils {
    
    /**
     * @brief Format ore information for display
     * 
     * This creates consistent formatting across the UI for ore information.
     */
    std::string formatOreDisplay(OreType oreType, int count) {
        if (count <= 0) {
            return "";  // Don't display empty ore types
        }
        
        Ore sampleOre(oreType);
        int totalValue = sampleOre.getValue() * count;
        
        std::ostringstream oss;
        oss << sampleOre.getName() << " x" << count 
            << " (" << totalValue << " value)";
        
        return oss.str();
    }
    
    /**
     * @brief Calculate inventory space efficiency
     * 
     * In games with limited inventory slots, this would measure
     * how well the player is using their available space.
     */
    float calculateSpaceEfficiency(const Inventory& inventory) {
        // This mining game has unlimited inventory space, but this
        // function shows how to calculate efficiency for other games
        
        int totalValue = inventory.getTotalValue();
        int totalCount = inventory.getTotalOreCount();
        
        if (totalCount == 0) {
            return 1.0f;  // Empty inventory is perfectly efficient
        }
        
        // Calculate average value per item
        float averageValue = static_cast<float>(totalValue) / totalCount;
        
        // Diamond ore has value 20, so efficiency is average value / max value
        return averageValue / 20.0f;  // 20 is diamond value
    }
    
    /**
     * @brief Find the most valuable ore type in inventory
     * 
     * This could be used for highlighting achievements or determining
     * what to prioritize in limited-space situations.
     */
    OreType getMostValuableOre(const Inventory& inventory) {
        OreType mostValuable = OreType::Copper;  // Default to cheapest
        int highestTotalValue = 0;
        
        for (auto oreType : OreUtils::getAllOreTypes()) {
            int count = inventory.getOreCount(oreType);
            if (count > 0) {
                Ore sampleOre(oreType);
                int totalValue = sampleOre.getValue() * count;
                
                if (totalValue > highestTotalValue) {
                    highestTotalValue = totalValue;
                    mostValuable = oreType;
                }
            }
        }
        
        return mostValuable;
    }
}