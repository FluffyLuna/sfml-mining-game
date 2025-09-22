#include "Shop.h"
#include <sstream>

// Define static constants for upgrade improvements
const float Shop::SPEED_IMPROVEMENT = 0.2f;       // Reduces mining time by 0.2s per upgrade
const float Shop::RANGE_IMPROVEMENT = 15.0f;      // Adds 15 pixels of range per upgrade
const float Shop::MULTIPLIER_IMPROVEMENT = 0.5f;  // Adds 0.5x multiplier per upgrade

Shop::Shop() 
    : speedUpgradeLevel(0)
    , rangeUpgradeLevel(0)
    , multiplierUpgradeLevel(0) {
    
    // Try to load a font - in a real game you'd include font files
    // For now we'll use the default font, but this might not display text
    // In a production game, you would load a font file like:
    // if (!font.loadFromFile("assets/fonts/arial.ttf")) { /* handle error */ }
    
    // Set up the shop background
    background.setSize(sf::Vector2f(600, 500));
    background.setFillColor(sf::Color(0, 0, 0, 200)); // Semi-transparent black
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(2.0f);
    background.setPosition(212, 134); // Center on 1024x768 screen
    
    // Set up title text
    titleText.setFont(font);
    titleText.setString("PICKAXE UPGRADES");
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setPosition(350, 150);
    
    // Set up instructions text
    instructionsText.setFont(font);
    instructionsText.setString("Press 1, 2, or 3 to buy upgrades. Press S to close shop.");
    instructionsText.setCharacterSize(16);
    instructionsText.setFillColor(sf::Color::White);
    instructionsText.setPosition(230, 200);
    
    // Initialize upgrade text objects
    upgradeTexts.resize(3);
    for (size_t i = 0; i < upgradeTexts.size(); ++i) {
        upgradeTexts[i].setFont(font);
        upgradeTexts[i].setCharacterSize(20);
        upgradeTexts[i].setFillColor(sf::Color::White);
        upgradeTexts[i].setPosition(230, 250 + i * 100);
    }
}

void Shop::render(sf::RenderWindow& window) {
    // Draw shop background
    window.draw(background);
    
    // Draw shop title
    window.draw(titleText);
    
    // Draw instructions
    window.draw(instructionsText);
    
    // Draw upgrade options
    for (const auto& text : upgradeTexts) {
        window.draw(text);
    }
}

bool Shop::handleInput(sf::Keyboard::Key key, Inventory& inventory, Player& player) {
    switch (key) {
        case sf::Keyboard::Num1: {
            // Speed upgrade
            UpgradeCost cost = getSpeedUpgradeCost();
            if (canAfford(cost, inventory)) {
                deductCost(cost, inventory);
                player.upgradeMiningSpeed(SPEED_IMPROVEMENT);
                speedUpgradeLevel++;
                return true;
            }
            break;
        }
        
        case sf::Keyboard::Num2: {
            // Range upgrade
            UpgradeCost cost = getRangeUpgradeCost();
            if (canAfford(cost, inventory)) {
                deductCost(cost, inventory);
                player.upgradeMiningRange(RANGE_IMPROVEMENT);
                rangeUpgradeLevel++;
                return true;
            }
            break;
        }
        
        case sf::Keyboard::Num3: {
            // Multiplier upgrade
            UpgradeCost cost = getMultiplierUpgradeCost();
            if (canAfford(cost, inventory)) {
                deductCost(cost, inventory);
                player.upgradeOreMultiplier(MULTIPLIER_IMPROVEMENT);
                multiplierUpgradeLevel++;
                return true;
            }
            break;
        }
        
        default:
            break;
    }
    
    return false; // No upgrade purchased
}

void Shop::updateDisplay(const Inventory& inventory) {
    // Update speed upgrade text
    UpgradeCost speedCost = getSpeedUpgradeCost();
    std::ostringstream speedStream;
    speedStream << "1. Mining Speed (Level " << speedUpgradeLevel << ")\n";
    speedStream << "   " << formatCost(speedCost);
    if (!canAfford(speedCost, inventory)) {
        speedStream << " [CANNOT AFFORD]";
    }
    upgradeTexts[0].setString(speedStream.str());
    upgradeTexts[0].setFillColor(canAfford(speedCost, inventory) ? sf::Color::Green : sf::Color::Red);
    
    // Update range upgrade text
    UpgradeCost rangeCost = getRangeUpgradeCost();
    std::ostringstream rangeStream;
    rangeStream << "2. Mining Range (Level " << rangeUpgradeLevel << ")\n";
    rangeStream << "   " << formatCost(rangeCost);
    if (!canAfford(rangeCost, inventory)) {
        rangeStream << " [CANNOT AFFORD]";
    }
    upgradeTexts[1].setString(rangeStream.str());
    upgradeTexts[1].setFillColor(canAfford(rangeCost, inventory) ? sf::Color::Green : sf::Color::Red);
    
    // Update multiplier upgrade text
    UpgradeCost multiplierCost = getMultiplierUpgradeCost();
    std::ostringstream multiplierStream;
    multiplierStream << "3. Ore Multiplier (Level " << multiplierUpgradeLevel << ")\n";
    multiplierStream << "   " << formatCost(multiplierCost);
    if (!canAfford(multiplierCost, inventory)) {
        multiplierStream << " [CANNOT AFFORD]";
    }
    upgradeTexts[2].setString(multiplierStream.str());
    upgradeTexts[2].setFillColor(canAfford(multiplierCost, inventory) ? sf::Color::Green : sf::Color::Red);
}

Shop::UpgradeCost Shop::getSpeedUpgradeCost() const {
    // Speed upgrade costs increase with level
    // Early upgrades are cheap, later ones require rare ores
    switch (speedUpgradeLevel) {
        case 0: return UpgradeCost(10, 0, 0, 0);  // 10 copper
        case 1: return UpgradeCost(20, 5, 0, 0);  // 20 copper, 5 iron
        case 2: return UpgradeCost(50, 15, 3, 0); // 50 copper, 15 iron, 3 gold
        case 3: return UpgradeCost(100, 30, 10, 1); // 100 copper, 30 iron, 10 gold, 1 diamond
        default: return UpgradeCost(200, 50, 20, 2); // Expensive for high levels
    }
}

Shop::UpgradeCost Shop::getRangeUpgradeCost() const {
    // Range upgrade costs
    switch (rangeUpgradeLevel) {
        case 0: return UpgradeCost(15, 0, 0, 0);  
        case 1: return UpgradeCost(30, 8, 0, 0);  
        case 2: return UpgradeCost(60, 20, 5, 0); 
        case 3: return UpgradeCost(120, 40, 15, 2); 
        default: return UpgradeCost(250, 75, 30, 5); 
    }
}

Shop::UpgradeCost Shop::getMultiplierUpgradeCost() const {
    // Multiplier upgrades are the most expensive since they're very powerful
    switch (multiplierUpgradeLevel) {
        case 0: return UpgradeCost(25, 5, 0, 0);  
        case 1: return UpgradeCost(50, 15, 3, 0);  
        case 2: return UpgradeCost(100, 40, 12, 1); 
        case 3: return UpgradeCost(200, 80, 25, 3); 
        default: return UpgradeCost(400, 150, 50, 10); 
    }
}

bool Shop::canAfford(const UpgradeCost& cost, const Inventory& inventory) const {
    return inventory.hasEnough(OreType::COPPER, cost.copper) &&
           inventory.hasEnough(OreType::IRON, cost.iron) &&
           inventory.hasEnough(OreType::GOLD, cost.gold) &&
           inventory.hasEnough(OreType::DIAMOND, cost.diamond);
}

void Shop::deductCost(const UpgradeCost& cost, Inventory& inventory) {
    inventory.removeOre(OreType::COPPER, cost.copper);
    inventory.removeOre(OreType::IRON, cost.iron);
    inventory.removeOre(OreType::GOLD, cost.gold);
    inventory.removeOre(OreType::DIAMOND, cost.diamond);
}

std::string Shop::formatCost(const UpgradeCost& cost) const {
    std::ostringstream oss;
    oss << "Cost: ";
    
    bool needComma = false;
    if (cost.copper > 0) {
        oss << cost.copper << " Copper";
        needComma = true;
    }
    if (cost.iron > 0) {
        if (needComma) oss << ", ";
        oss << cost.iron << " Iron";
        needComma = true;
    }
    if (cost.gold > 0) {
        if (needComma) oss << ", ";
        oss << cost.gold << " Gold";
        needComma = true;
    }
    if (cost.diamond > 0) {
        if (needComma) oss << ", ";
        oss << cost.diamond << " Diamond";
    }
    
    return oss.str();
}