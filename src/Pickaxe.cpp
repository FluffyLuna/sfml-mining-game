#include "Pickaxe.h"
#include <algorithm>

/**
 * @brief Constructor initializes pickaxe with specified tier
 */
Pickaxe::Pickaxe(PickaxeTier tier) : m_tier(tier) {
    initializeProperties();
}

/**
 * @brief Initialize pickaxe stats based on tier
 * 
 * This method demonstrates equipment progression scaling.
 * The values create a meaningful upgrade path that feels rewarding
 * while maintaining game balance.
 */
void Pickaxe::initializeProperties() {
    switch (m_tier) {
        case PickaxeTier::Wood:
            m_power = 1.0f;                                 // Base mining power
            m_speed = 1.0f;                                 // Base mining speed
            m_name = "Wooden Pickaxe";
            m_color = sf::Color(139, 69, 19);               // Brown wood color
            break;
            
        case PickaxeTier::Stone:
            m_power = 2.0f;                                 // 2x mining power
            m_speed = 1.2f;                                 // 20% faster mining
            m_name = "Stone Pickaxe";
            m_color = sf::Color(128, 128, 128);             // Gray stone color
            break;
            
        case PickaxeTier::Iron:
            m_power = 4.0f;                                 // 4x mining power
            m_speed = 1.5f;                                 // 50% faster mining
            m_name = "Iron Pickaxe";
            m_color = sf::Color(192, 192, 192);             // Silver iron color
            break;
            
        case PickaxeTier::Gold:
            m_power = 7.0f;                                 // 7x mining power
            m_speed = 2.0f;                                 // 100% faster mining
            m_name = "Golden Pickaxe";
            m_color = sf::Color(255, 215, 0);               // Golden color
            break;
            
        case PickaxeTier::Diamond:
            m_power = 12.0f;                                // 12x mining power
            m_speed = 3.0f;                                 // 200% faster mining
            m_name = "Diamond Pickaxe";
            m_color = sf::Color(185, 242, 255);             // Diamond blue-white
            break;
    }
}

/**
 * @brief Check if pickaxe can be upgraded further
 */
bool Pickaxe::canUpgrade() const {
    return m_tier != PickaxeTier::Diamond;  // Diamond is the highest tier
}

/**
 * @brief Get upgrade recipe for next tier
 * 
 * This method demonstrates how to create meaningful resource costs
 * that encourage players to mine different ore types.
 */
std::vector<UpgradeRecipe> Pickaxe::getUpgradeRecipe() const {
    return getRecipeForUpgrade(m_tier, PickaxeUtils::getNextTier(m_tier));
}

/**
 * @brief Calculate total cost of upgrade in ore values
 */
int Pickaxe::getUpgradeCost() const {
    if (!canUpgrade()) {
        return 0;  // No upgrade available
    }
    
    auto recipe = getUpgradeRecipe();
    int totalCost = 0;
    
    // Calculate total value of all required ores
    for (const auto& ingredient : recipe) {
        Ore sampleOre(ingredient.oreType);
        totalCost += sampleOre.getValue() * ingredient.quantity;
    }
    
    return totalCost;
}

/**
 * @brief Attempt to upgrade using available ores
 * 
 * This method demonstrates transaction processing in games:
 * - Validate prerequisites
 * - Check resource availability
 * - Execute transaction atomically
 * - Provide clear feedback
 */
bool Pickaxe::attemptUpgrade(std::map<OreType, int>& availableOres) {
    if (!canUpgrade()) {
        return false;  // Already at maximum tier
    }
    
    auto recipe = getUpgradeRecipe();
    
    // First, check if we have enough ores for all requirements
    for (const auto& ingredient : recipe) {
        auto it = availableOres.find(ingredient.oreType);
        if (it == availableOres.end() || it->second < ingredient.quantity) {
            return false;  // Insufficient ores
        }
    }
    
    // We have enough ores, so consume them and upgrade
    for (const auto& ingredient : recipe) {
        availableOres[ingredient.oreType] -= ingredient.quantity;
    }
    
    // Upgrade to next tier
    m_tier = PickaxeUtils::getNextTier(m_tier);
    initializeProperties();
    
    return true;  // Upgrade successful
}

/**
 * @brief Get all pickaxe tiers in order
 */
std::vector<PickaxeTier> Pickaxe::getAllTiers() {
    return {
        PickaxeTier::Wood,
        PickaxeTier::Stone,
        PickaxeTier::Iron,
        PickaxeTier::Gold,
        PickaxeTier::Diamond
    };
}

/**
 * @brief Get upgrade recipe for specific tier transition
 * 
 * This method defines the progression costs, creating the resource
 * sink that drives the mining gameplay loop.
 */
std::vector<UpgradeRecipe> Pickaxe::getRecipeForUpgrade(PickaxeTier fromTier, PickaxeTier toTier) {
    (void)fromTier; // Suppress unused parameter warning
    std::vector<UpgradeRecipe> recipe;
    
    switch (toTier) {
        case PickaxeTier::Stone:
            // Wood -> Stone: Requires some copper
            recipe.emplace_back(OreType::Copper, 5);
            break;
            
        case PickaxeTier::Iron:
            // Stone -> Iron: Requires copper and iron
            recipe.emplace_back(OreType::Copper, 8);
            recipe.emplace_back(OreType::Iron, 3);
            break;
            
        case PickaxeTier::Gold:
            // Iron -> Gold: Requires iron and some gold
            recipe.emplace_back(OreType::Iron, 5);
            recipe.emplace_back(OreType::Gold, 2);
            break;
            
        case PickaxeTier::Diamond:
            // Gold -> Diamond: Requires gold and diamonds
            recipe.emplace_back(OreType::Gold, 3);
            recipe.emplace_back(OreType::Diamond, 1);
            break;
            
        case PickaxeTier::Wood:
        default:
            // No recipe needed for wood tier or invalid upgrades
            break;
    }
    
    return recipe;
}

// Utility functions implementation
namespace PickaxeUtils {
    
    /**
     * @brief Convert pickaxe tier to display string
     */
    std::string tierToString(PickaxeTier tier) {
        switch (tier) {
            case PickaxeTier::Wood:     return "Wood";
            case PickaxeTier::Stone:    return "Stone";
            case PickaxeTier::Iron:     return "Iron";
            case PickaxeTier::Gold:     return "Gold";
            case PickaxeTier::Diamond:  return "Diamond";
            default:                    return "Unknown";
        }
    }
    
    /**
     * @brief Get the next tier in progression
     */
    PickaxeTier getNextTier(PickaxeTier currentTier) {
        switch (currentTier) {
            case PickaxeTier::Wood:     return PickaxeTier::Stone;
            case PickaxeTier::Stone:    return PickaxeTier::Iron;
            case PickaxeTier::Iron:     return PickaxeTier::Gold;
            case PickaxeTier::Gold:     return PickaxeTier::Diamond;
            case PickaxeTier::Diamond:  return PickaxeTier::Diamond; // Already maxed
            default:                    return currentTier;
        }
    }
    
    /**
     * @brief Calculate mining time based on tool power and block hardness
     * 
     * This formula creates the core mining mechanic:
     * - Harder blocks take longer to mine
     * - Better pickaxes reduce mining time
     * - The relationship is inverse to feel intuitive
     */
    float calculateMiningTime(float pickaxePower, float blockHardness, float baseTime) {
        // Prevent division by zero
        if (pickaxePower <= 0.0f) {
            return baseTime * 10.0f;  // Very slow if no power
        }
        
        // Mining time = base time * block hardness / pickaxe power
        // This creates intuitive scaling where better tools mine faster
        float miningTime = baseTime * blockHardness / pickaxePower;
        
        // Ensure minimum mining time for game feel
        return std::max(miningTime, 0.1f);
    }
}