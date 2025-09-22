#pragma once

#include "Ore.h"
#include <unordered_map>
#include <string>

/**
 * Inventory class manages the player's collected ores
 * Keeps track of quantities of each ore type and provides
 * methods for adding, removing, and querying ore counts
 */
class Inventory {
private:
    // Map storing count of each ore type
    // Key: OreType, Value: quantity owned
    std::unordered_map<OreType, int> oreCount;

public:
    /**
     * Constructor initializes empty inventory
     * All ore counts start at zero
     */
    Inventory();
    
    /**
     * Add ores to the inventory
     * @param type - Type of ore to add
     * @param quantity - How many to add (default 1)
     */
    void addOre(OreType type, int quantity = 1);
    
    /**
     * Remove ores from the inventory (used when buying upgrades)
     * @param type - Type of ore to remove
     * @param quantity - How many to remove
     * @return true if successful, false if not enough ores
     */
    bool removeOre(OreType type, int quantity);
    
    /**
     * Get the count of a specific ore type
     * @param type - Ore type to check
     * @return Number of that ore type owned
     */
    int getOreCount(OreType type) const;
    
    /**
     * Check if the inventory has enough of a specific ore
     * @param type - Ore type to check
     * @param quantity - Required quantity
     * @return true if player has enough, false otherwise
     */
    bool hasEnough(OreType type, int quantity) const;
    
    /**
     * Get a formatted string showing all ore counts
     * Used for displaying inventory in the UI
     * @return String with ore counts (e.g., "Copper: 5, Iron: 3, Gold: 1")
     */
    std::string getInventoryString() const;
    
    /**
     * Get the total value of all ores in the inventory
     * Useful for showing player's total wealth
     * @return Total value in points
     */
    int getTotalValue() const;
    
    /**
     * Check if the inventory is completely empty
     * @return true if no ores are owned
     */
    bool isEmpty() const;
    
    /**
     * Clear all ores from the inventory
     * Rarely used, but useful for testing or reset functionality
     */
    void clear();
};