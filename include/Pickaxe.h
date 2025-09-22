#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Ore.h"

/**
 * @brief Enumeration of different pickaxe tiers available in the game
 * 
 * Each tier has improved mining power and efficiency, creating a clear
 * upgrade progression that motivates ore collection and trading.
 */
enum class PickaxeTier {
    Wood,       ///< Starting pickaxe - weak but functional
    Stone,      ///< Basic upgrade - moderate improvement
    Iron,       ///< Good pickaxe - significant improvement
    Gold,       ///< Advanced pickaxe - fast mining
    Diamond     ///< Ultimate pickaxe - mines everything quickly
};

/**
 * @brief Recipe structure defines what ores are needed for upgrades
 * 
 * This demonstrates how to create crafting/upgrade systems in games.
 * Each recipe specifies the exact cost for upgrading equipment.
 */
struct UpgradeRecipe {
    OreType oreType;        ///< Type of ore required
    int quantity;           ///< How many of this ore are needed
    
    UpgradeRecipe(OreType type, int qty) : oreType(type), quantity(qty) {}
};

/**
 * @brief Pickaxe class manages mining tools and their upgrade system
 * 
 * This class demonstrates several important game design concepts:
 * - Equipment progression systems
 * - Resource-based crafting/upgrading
 * - Stat scaling and balance
 * - Visual feedback for equipment quality
 * 
 * The pickaxe is the player's primary tool, so its design affects
 * the pacing and satisfaction of the entire game progression.
 */
class Pickaxe {
public:
    /**
     * @brief Constructor creates a pickaxe of the specified tier
     * 
     * @param tier The initial tier of the pickaxe
     */
    explicit Pickaxe(PickaxeTier tier = PickaxeTier::Wood);
    
    /**
     * @brief Get the current tier of this pickaxe
     * @return The PickaxeTier enum value
     */
    PickaxeTier getTier() const { return m_tier; }
    
    /**
     * @brief Get the mining power of this pickaxe
     * 
     * Mining power determines:
     * - How fast blocks are broken
     * - Which block types can be mined
     * - Mining efficiency multipliers
     * 
     * Higher values mean faster, more effective mining.
     * 
     * @return The mining power value
     */
    float getPower() const { return m_power; }
    
    /**
     * @brief Get the mining speed multiplier
     * 
     * This affects how quickly mining actions complete.
     * Values > 1.0 mean faster mining, < 1.0 mean slower.
     * 
     * @return Speed multiplier for mining actions
     */
    float getSpeed() const { return m_speed; }
    
    /**
     * @brief Get the display name of this pickaxe
     * 
     * @return Human-readable name for UI display
     */
    std::string getName() const { return m_name; }
    
    /**
     * @brief Get the color representing this pickaxe tier
     * 
     * Each tier has a distinct color for easy visual identification:
     * - Wood: Brown
     * - Stone: Gray
     * - Iron: Dark gray
     * - Gold: Yellow
     * - Diamond: Light blue
     * 
     * @return SFML Color for this pickaxe tier
     */
    sf::Color getColor() const { return m_color; }
    
    /**
     * @brief Check if this pickaxe can be upgraded to the next tier
     * 
     * @return True if an upgrade is available, false if already max tier
     */
    bool canUpgrade() const;
    
    /**
     * @brief Get the recipe for upgrading to the next tier
     * 
     * This method demonstrates how to create upgrade requirement systems.
     * Each upgrade requires specific types and quantities of ores.
     * 
     * @return Vector of UpgradeRecipe showing required materials
     */
    std::vector<UpgradeRecipe> getUpgradeRecipe() const;
    
    /**
     * @brief Get the total cost of upgrading to the next tier
     * 
     * This calculates the total value of all required materials,
     * useful for displaying upgrade costs in the shop interface.
     * 
     * @return Total ore value needed for the next upgrade
     */
    int getUpgradeCost() const;
    
    /**
     * @brief Attempt to upgrade this pickaxe using available ores
     * 
     * This method demonstrates transaction-like operations in games:
     * - Check if upgrade is possible
     * - Verify sufficient resources
     * - Consume required materials
     * - Apply the upgrade
     * - Provide feedback on success/failure
     * 
     * @param availableOres Map of ore types to quantities available
     * @return True if upgrade succeeded, false if insufficient resources
     */
    bool attemptUpgrade(std::map<OreType, int>& availableOres);
    
    /**
     * @brief Get all pickaxe tiers in order of power
     * 
     * Useful for displaying upgrade paths and progression information.
     * 
     * @return Vector of all pickaxe tiers from weakest to strongest
     */
    static std::vector<PickaxeTier> getAllTiers();

private:
    PickaxeTier m_tier;         ///< Current tier of this pickaxe
    float m_power;              ///< Mining power value
    float m_speed;              ///< Mining speed multiplier
    std::string m_name;         ///< Display name
    sf::Color m_color;          ///< Visual representation color
    
    /**
     * @brief Initialize pickaxe properties based on tier
     * 
     * This method sets up all the stats that make each tier unique:
     * - Mining power for block breaking capability
     * - Speed multipliers for mining efficiency
     * - Names for UI display
     * - Colors for visual distinction
     * 
     * The progression curve here determines how rewarding upgrades feel
     * and how the game pacing develops over time.
     */
    void initializeProperties();
    
    /**
     * @brief Get the upgrade recipe for a specific tier transition
     * 
     * This method defines the exact cost of each upgrade, creating
     * the resource sink that drives the mining and collection gameplay.
     * 
     * @param fromTier The current tier
     * @param toTier The target tier
     * @return Vector of required materials for this upgrade
     */
    static std::vector<UpgradeRecipe> getRecipeForUpgrade(PickaxeTier fromTier, PickaxeTier toTier);
};

/**
 * @brief Utility functions for pickaxe management
 * 
 * These helper functions provide common operations needed throughout
 * the game for pickaxe handling and display.
 */
namespace PickaxeUtils {
    /**
     * @brief Convert pickaxe tier to string for display
     * 
     * @param tier The tier to convert
     * @return String representation of the pickaxe tier
     */
    std::string tierToString(PickaxeTier tier);
    
    /**
     * @brief Get the next tier in the upgrade sequence
     * 
     * @param currentTier The current tier
     * @return The next tier, or the same tier if already maxed
     */
    PickaxeTier getNextTier(PickaxeTier currentTier);
    
    /**
     * @brief Calculate mining time based on pickaxe power and block hardness
     * 
     * This function demonstrates the combat/interaction formula:
     * Mining Time = Base Time * Block Hardness / Pickaxe Power
     * 
     * @param pickaxePower The power rating of the pickaxe
     * @param blockHardness The hardness rating of the block
     * @param baseTime Base mining time in seconds
     * @return Calculated mining time in seconds
     */
    float calculateMiningTime(float pickaxePower, float blockHardness, float baseTime = 1.0f);
}