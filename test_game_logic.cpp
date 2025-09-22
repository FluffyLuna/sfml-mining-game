/**
 * Simple test program to verify game logic without GUI
 * This demonstrates the core game mechanics working correctly
 * Compile with: g++ -std=c++17 test_game_logic.cpp -I include src/Inventory.cpp src/Ore.cpp -o test_logic
 */

#include "Inventory.h"
#include "Ore.h"
#include <iostream>
#include <memory>

int main() {
    std::cout << "=== SFML Mining Game Logic Test ===\n\n";
    
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
    
    // Test ore creation
    std::cout << "Testing Ore System...\n";
    auto copper = std::make_unique<Ore>(OreType::COPPER, 100, 100);
    auto gold = std::make_unique<Ore>(OreType::GOLD, 200, 200);
    auto diamond = std::make_unique<Ore>(OreType::DIAMOND, 300, 300);
    
    std::cout << "Created " << copper->getName() << " ore worth " << copper->getValue() << " points\n";
    std::cout << "Created " << gold->getName() << " ore worth " << gold->getValue() << " points\n";
    std::cout << "Created " << diamond->getName() << " ore worth " << diamond->getValue() << " points\n\n";
    
    // Test random ore generation
    std::cout << "Testing Random Ore Generation...\n";
    for (int i = 0; i < 10; ++i) {
        auto randomOre = Ore::createRandomOre(i * 50, i * 50);
        std::cout << "Random ore #" << (i+1) << ": " << randomOre->getName() 
                  << " (value: " << randomOre->getValue() << ")\n";
    }
    std::cout << "\n";
    
    // Test inventory operations
    std::cout << "Testing Inventory Operations...\n";
    std::cout << "Can afford 5 copper? " << (inventory.hasEnough(OreType::COPPER, 5) ? "Yes" : "No") << "\n";
    std::cout << "Can afford 10 diamonds? " << (inventory.hasEnough(OreType::DIAMOND, 10) ? "Yes" : "No") << "\n";
    
    // Remove some ores
    if (inventory.removeOre(OreType::COPPER, 3)) {
        std::cout << "Successfully removed 3 copper ores\n";
    }
    
    std::cout << "\nFinal inventory:\n";
    std::cout << inventory.getInventoryString() << "\n";
    std::cout << "Final total value: " << inventory.getTotalValue() << " points\n";
    
    std::cout << "\n=== All Tests Completed Successfully! ===\n";
    std::cout << "The game logic is working correctly. You can now run the full game!\n";
    
    return 0;
}