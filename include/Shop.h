#pragma once

#include <SFML/Graphics.hpp>
#include "Inventory.h"
#include "Player.h"

/**
 * Shop class manages the upgrade system where players can trade ores for improvements
 * The shop offers three types of upgrades:
 * 1. Mining Speed - Mine ores faster
 * 2. Mining Range - Mine ores from further away
 * 3. Ore Multiplier - Get more ores per mine
 */
class Shop {
private:
    // UI elements
    sf::Font font;                      // Font for shop text
    sf::RectangleShape background;      // Background panel for shop
    sf::Text titleText;                 // "PICKAXE UPGRADES" title
    sf::Text instructionsText;          // How to use the shop
    std::vector<sf::Text> upgradeTexts; // Text for each upgrade option
    
    // Upgrade costs (in ore quantities)
    struct UpgradeCost {
        int copper;
        int iron; 
        int gold;
        int diamond;
        
        UpgradeCost(int c = 0, int i = 0, int g = 0, int d = 0) 
            : copper(c), iron(i), gold(g), diamond(d) {}
    };
    
    // Current upgrade levels and costs
    int speedUpgradeLevel;              // Current level of speed upgrade
    int rangeUpgradeLevel;              // Current level of range upgrade  
    int multiplierUpgradeLevel;         // Current level of multiplier upgrade
    
    // Upgrade improvement amounts
    static const float SPEED_IMPROVEMENT;       // How much each speed upgrade helps
    static const float RANGE_IMPROVEMENT;       // How much each range upgrade adds
    static const float MULTIPLIER_IMPROVEMENT;  // How much each multiplier upgrade adds

public:
    /**
     * Constructor initializes the shop UI and upgrade levels
     */
    Shop();
    
    /**
     * Render the shop interface
     * @param window - SFML window to draw to
     */
    void render(sf::RenderWindow& window);
    
    /**
     * Handle keyboard input for purchasing upgrades
     * 1 = Speed Upgrade, 2 = Range Upgrade, 3 = Multiplier Upgrade
     * @param key - Key that was pressed
     * @param inventory - Player's inventory to deduct costs from
     * @param player - Player to apply upgrades to
     * @return true if an upgrade was purchased
     */
    bool handleInput(sf::Keyboard::Key key, Inventory& inventory, Player& player);
    
    /**
     * Update the shop display texts with current costs and levels
     * Called after upgrades to refresh the display
     * @param inventory - Player's inventory to check affordability
     */
    void updateDisplay(const Inventory& inventory);

private:
    /**
     * Get the cost for the next speed upgrade
     * Costs increase with each upgrade level
     * @return UpgradeCost structure with ore requirements
     */
    UpgradeCost getSpeedUpgradeCost() const;
    
    /**
     * Get the cost for the next range upgrade
     * @return UpgradeCost structure with ore requirements
     */
    UpgradeCost getRangeUpgradeCost() const;
    
    /**
     * Get the cost for the next multiplier upgrade  
     * @return UpgradeCost structure with ore requirements
     */
    UpgradeCost getMultiplierUpgradeCost() const;
    
    /**
     * Check if the inventory can afford a specific upgrade
     * @param cost - The upgrade cost to check
     * @param inventory - Player's inventory
     * @return true if affordable
     */
    bool canAfford(const UpgradeCost& cost, const Inventory& inventory) const;
    
    /**
     * Deduct upgrade cost from inventory
     * @param cost - The upgrade cost to deduct
     * @param inventory - Player's inventory to deduct from
     */
    void deductCost(const UpgradeCost& cost, Inventory& inventory);
    
    /**
     * Create a formatted string showing upgrade cost
     * @param cost - The upgrade cost
     * @return String like "Cost: 10 Copper, 5 Iron"
     */
    std::string formatCost(const UpgradeCost& cost) const;
};