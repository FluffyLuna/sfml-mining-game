#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "Ore.h"

/**
 * @brief Inventory class manages the player's collected ores and resources
 * 
 * This class demonstrates several important game programming concepts:
 * - Container management for game items
 * - Resource tracking and counting
 * - UI data preparation and formatting
 * - Transaction handling for trading systems
 * 
 * The inventory is crucial for progression as it holds the resources
 * needed for pickaxe upgrades and tracks player wealth/progress.
 */
class Inventory {
public:
    /**
     * @brief Constructor initializes empty inventory
     * 
     * Sets up the ore counting system and prepares for item management.
     */
    Inventory();
    
    /**
     * @brief Add an ore to the inventory
     * 
     * This method demonstrates item addition with automatic stacking:
     * - Identifies ore type
     * - Increments count for that type
     * - Updates total inventory value
     * - Triggers any relevant UI updates
     * 
     * @param ore The ore to add to inventory
     */
    void addOre(const Ore& ore);
    
    /**
     * @brief Add multiple ores of the same type
     * 
     * Convenience method for bulk additions (useful for mining bonuses
     * or administrative functions).
     * 
     * @param oreType The type of ore to add
     * @param quantity How many to add
     */
    void addOres(OreType oreType, int quantity);
    
    /**
     * @brief Remove ores from inventory (for trading/spending)
     * 
     * This method demonstrates safe item removal:
     * - Check if sufficient quantity exists
     * - Remove only the requested amount
     * - Prevent negative quantities
     * - Return success/failure status
     * 
     * @param oreType The type of ore to remove
     * @param quantity How many to remove
     * @return True if removal succeeded, false if insufficient quantity
     */
    bool removeOres(OreType oreType, int quantity);
    
    /**
     * @brief Get the count of a specific ore type
     * 
     * @param oreType The ore type to check
     * @return Number of this ore type in inventory
     */
    int getOreCount(OreType oreType) const;
    
    /**
     * @brief Get total count of all ores in inventory
     * 
     * Useful for inventory space calculations and general statistics.
     * 
     * @return Total number of individual ores
     */
    int getTotalOreCount() const;
    
    /**
     * @brief Calculate total value of all ores in inventory
     * 
     * This method demonstrates wealth calculation:
     * - Multiply each ore count by its individual value
     * - Sum all ore types for total wealth
     * - Useful for shop interfaces and progress tracking
     * 
     * @return Total value of all ores combined
     */
    int getTotalValue() const;
    
    /**
     * @brief Get all ore counts as a map
     * 
     * Returns the internal ore storage for advanced operations like
     * upgrade checking and batch processing.
     * 
     * @return Map of ore types to their quantities
     */
    const std::map<OreType, int>& getAllOreCounts() const { return m_oreCounts; }
    
    /**
     * @brief Get a reference to ore counts for modification
     * 
     * Allows external systems (like shops) to modify inventory directly
     * for complex transactions. Use with caution!
     * 
     * @return Mutable reference to ore count map
     */
    std::map<OreType, int>& getOreCountsRef() { return m_oreCounts; }
    
    /**
     * @brief Check if inventory contains enough ores for a specific recipe
     * 
     * This method demonstrates recipe validation:
     * - Check each required ore type
     * - Verify sufficient quantities exist
     * - Return overall feasibility
     * 
     * Used by upgrade systems to validate transactions before executing.
     * 
     * @param requiredOres Map of ore types to required quantities
     * @return True if inventory contains sufficient ores
     */
    bool hasEnoughOres(const std::map<OreType, int>& requiredOres) const;
    
    /**
     * @brief Get formatted string representation of inventory contents
     * 
     * This method demonstrates data formatting for UI display:
     * - Convert internal data to human-readable format
     * - Include ore names, counts, and values
     * - Format for consistent display
     * 
     * @return Formatted string showing all inventory contents
     */
    std::string getInventoryDisplay() const;
    
    /**
     * @brief Clear all ores from inventory
     * 
     * Useful for debugging, testing, or special game events.
     */
    void clear();
    
    /**
     * @brief Check if inventory is empty
     * 
     * @return True if no ores are stored
     */
    bool isEmpty() const;

private:
    /**
     * @brief Map storing count of each ore type
     * 
     * Using std::map provides:
     * - Automatic sorting by ore type
     * - Efficient lookups by ore type
     * - Easy iteration over all ore types
     * - Automatic handling of new ore types
     */
    std::map<OreType, int> m_oreCounts;
    
    /**
     * @brief Update internal statistics after inventory changes
     * 
     * This method would be called after additions/removals to:
     * - Recalculate total values
     * - Update UI displays
     * - Trigger achievement checks
     * - Log inventory changes
     * 
     * Currently not needed for this simple system, but shows where
     * such functionality would go in a more complex game.
     */
    void updateStatistics();
};

/**
 * @brief Utility functions for inventory management
 * 
 * These helper functions provide common operations and formatting
 * used throughout the game for inventory display and manipulation.
 */
namespace InventoryUtils {
    /**
     * @brief Format ore count and value for display
     * 
     * Creates consistent formatting for UI elements showing ore information.
     * 
     * @param oreType The type of ore
     * @param count How many of this ore
     * @return Formatted string like "Iron x5 (50 value)"
     */
    std::string formatOreDisplay(OreType oreType, int count);
    
    /**
     * @brief Calculate space efficiency of inventory
     * 
     * In games with limited inventory space, this would calculate
     * how efficiently the space is being used.
     * 
     * @param inventory The inventory to analyze
     * @return Efficiency ratio (0.0 to 1.0)
     */
    float calculateSpaceEfficiency(const Inventory& inventory);
    
    /**
     * @brief Get the most valuable ore type in inventory
     * 
     * Useful for highlighting the player's best finds or determining
     * what to prioritize in limited-space situations.
     * 
     * @param inventory The inventory to analyze
     * @return The most valuable ore type found
     */
    OreType getMostValuableOre(const Inventory& inventory);
}