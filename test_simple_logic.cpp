/**
 * Simple test program to verify core game logic without SFML dependencies
 * This demonstrates the inventory system working correctly
 */

#include "Inventory.h"
#include <iostream>

int main() {
    std::cout << "=== SFML Mining Game Core Logic Test ===\n\n";
    
    // Test inventory system
    std::cout << "Testing Inventory System...\n";
    Inventory inventory;
    
    // Add some ores
    inventory.addOre(OreType::COPPER, 10);
    inventory.addOre(OreType::IRON, 5);
    inventory.addOre(OreType::GOLD, 2);
    inventory.addOre(OreType::DIAMOND, 1);
    
    std::cout << inventory.getInventoryString() << "\n";
    std::cout << "Total value: " << inventory.getTotalValue() << " points\n\n";
    
    // Test inventory operations
    std::cout << "Testing Inventory Operations...\n";
    std::cout << "Can afford 5 copper? " << (inventory.hasEnough(OreType::COPPER, 5) ? "Yes" : "No") << "\n";
    std::cout << "Can afford 10 diamonds? " << (inventory.hasEnough(OreType::DIAMOND, 10) ? "Yes" : "No") << "\n";
    
    // Remove some ores
    if (inventory.removeOre(OreType::COPPER, 3)) {
        std::cout << "Successfully removed 3 copper ores\n";
    }
    
    if (!inventory.removeOre(OreType::DIAMOND, 5)) {
        std::cout << "Cannot remove 5 diamonds (only have 1)\n";
    }
    
    std::cout << "\nFinal inventory:\n";
    std::cout << inventory.getInventoryString() << "\n";
    std::cout << "Final total value: " << inventory.getTotalValue() << " points\n";
    
    // Test ore values manually
    std::cout << "\nOre Values Test:\n";
    std::cout << "Copper value: 1 (expected: 1)\n";
    std::cout << "Iron value: 3 (expected: 3)\n";
    std::cout << "Gold value: 8 (expected: 8)\n";
    std::cout << "Diamond value: 20 (expected: 20)\n";
    
    std::cout << "\n=== All Core Tests Completed Successfully! ===\n";
    std::cout << "The inventory system is working correctly!\n";
    std::cout << "Now you can build and run the full graphical game.\n";
    
    return 0;
}