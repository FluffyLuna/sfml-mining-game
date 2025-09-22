#include "Inventory.h"
#include <sstream>

Inventory::Inventory() {
    // Initialize all ore counts to zero
    // We explicitly set each type to make sure they exist in the map
    oreCount[OreType::COPPER] = 0;
    oreCount[OreType::IRON] = 0;
    oreCount[OreType::GOLD] = 0;
    oreCount[OreType::DIAMOND] = 0;
}

void Inventory::addOre(OreType type, int quantity) {
    // Add the specified quantity to the ore count
    // If the ore type doesn't exist in the map, it will be created with value 0
    oreCount[type] += quantity;
}

bool Inventory::removeOre(OreType type, int quantity) {
    // Check if we have enough ore to remove
    if (getOreCount(type) < quantity) {
        return false; // Not enough ore
    }
    
    // Remove the ore
    oreCount[type] -= quantity;
    return true; // Success
}

int Inventory::getOreCount(OreType type) const {
    // Find the ore type in the map
    auto it = oreCount.find(type);
    if (it != oreCount.end()) {
        return it->second; // Return the count
    }
    return 0; // Ore type not found, return 0
}

bool Inventory::hasEnough(OreType type, int quantity) const {
    return getOreCount(type) >= quantity;
}

std::string Inventory::getInventoryString() const {
    // Create a formatted string showing all ore counts
    // This is used for the inventory display in the game UI
    
    std::ostringstream oss;
    oss << "Inventory:\n";
    
    // Show each ore type with its count and name
    oss << "Copper: " << getOreCount(OreType::COPPER) << "\n";
    oss << "Iron: " << getOreCount(OreType::IRON) << "\n"; 
    oss << "Gold: " << getOreCount(OreType::GOLD) << "\n";
    oss << "Diamond: " << getOreCount(OreType::DIAMOND);
    
    return oss.str();
}

int Inventory::getTotalValue() const {
    // Calculate total value of all ores using their individual values
    int totalValue = 0;
    
    // For each ore type, multiply count by value per ore
    totalValue += getOreCount(OreType::COPPER) * 1;   // Copper worth 1 each
    totalValue += getOreCount(OreType::IRON) * 3;     // Iron worth 3 each
    totalValue += getOreCount(OreType::GOLD) * 8;     // Gold worth 8 each
    totalValue += getOreCount(OreType::DIAMOND) * 20; // Diamond worth 20 each
    
    return totalValue;
}

bool Inventory::isEmpty() const {
    // Check if all ore counts are zero
    for (const auto& pair : oreCount) {
        if (pair.second > 0) {
            return false; // Found at least one ore
        }
    }
    return true; // No ores found
}

void Inventory::clear() {
    // Reset all ore counts to zero
    // This is useful for testing or if we ever want a "reset inventory" feature
    for (auto& pair : oreCount) {
        pair.second = 0;
    }
}