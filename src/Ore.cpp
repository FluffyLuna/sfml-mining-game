#include "Ore.h"
#include <random>
#include <cmath>
#include <memory>

Ore::Ore(OreType oreType, float x, float y) 
    : type(oreType), position(x, y) {
    
    // Set up the visual representation of the ore
    // Different ore types have different sizes and colors
    float radius;
    switch (type) {
        case OreType::COPPER:   radius = 8.0f; break;   // Small copper ore
        case OreType::IRON:     radius = 10.0f; break;  // Medium iron ore
        case OreType::GOLD:     radius = 12.0f; break;  // Large gold ore
        case OreType::DIAMOND:  radius = 15.0f; break;  // Largest diamond ore
    }
    
    shape.setRadius(radius);
    shape.setFillColor(getColorForType(type));
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1.0f);
    
    // Center the shape on the ore's position
    shape.setOrigin(radius, radius);
    shape.setPosition(position);
}

sf::Color Ore::getColorForType(OreType type) {
    // Each ore type has a distinctive color for easy identification
    switch (type) {
        case OreType::COPPER:   return sf::Color(184, 115, 51);   // Brown/orange for copper
        case OreType::IRON:     return sf::Color(169, 169, 169);  // Gray for iron
        case OreType::GOLD:     return sf::Color(255, 215, 0);    // Bright yellow for gold
        case OreType::DIAMOND:  return sf::Color(185, 242, 255);  // Light blue for diamond
        default:                return sf::Color::White;
    }
}

float Ore::getRarityWeight(OreType type) {
    // Higher weight = more common
    // These weights determine how often each ore type spawns
    switch (type) {
        case OreType::COPPER:   return 50.0f;  // Very common (50% chance)
        case OreType::IRON:     return 30.0f;  // Common (30% chance)
        case OreType::GOLD:     return 15.0f;  // Uncommon (15% chance)
        case OreType::DIAMOND:  return 5.0f;   // Rare (5% chance)
        default:                return 1.0f;
    }
}

std::unique_ptr<Ore> Ore::createRandomOre(float x, float y) {
    // Use weighted random selection to choose ore type
    // This ensures proper rarity distribution
    
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    // Calculate total weight for all ore types
    float totalWeight = 0.0f;
    for (int i = 0; i < 4; ++i) {
        totalWeight += getRarityWeight(static_cast<OreType>(i));
    }
    
    // Generate random number between 0 and total weight
    std::uniform_real_distribution<float> dis(0.0f, totalWeight);
    float randomValue = dis(gen);
    
    // Find which ore type the random value corresponds to
    float currentWeight = 0.0f;
    for (int i = 0; i < 4; ++i) {
        OreType oreType = static_cast<OreType>(i);
        currentWeight += getRarityWeight(oreType);
        if (randomValue <= currentWeight) {
            return std::make_unique<Ore>(oreType, x, y);
        }
    }
    
    // Fallback to copper if something goes wrong
    return std::make_unique<Ore>(OreType::COPPER, x, y);
}

void Ore::render(sf::RenderWindow& window) {
    // Draw the ore to the screen
    window.draw(shape);
}

sf::Vector2f Ore::getPosition() const {
    return position;
}

OreType Ore::getType() const {
    return type;
}

int Ore::getValue() const {
    // Each ore type has a different trading value
    // Rarer ores are worth more in the shop
    switch (type) {
        case OreType::COPPER:   return 1;   // Basic value
        case OreType::IRON:     return 3;   // 3x copper value
        case OreType::GOLD:     return 8;   // 8x copper value
        case OreType::DIAMOND:  return 20;  // 20x copper value
        default:                return 1;
    }
}

std::string Ore::getName() const {
    // Return human-readable name for UI display
    switch (type) {
        case OreType::COPPER:   return "Copper";
        case OreType::IRON:     return "Iron";
        case OreType::GOLD:     return "Gold";
        case OreType::DIAMOND:  return "Diamond";
        default:                return "Unknown";
    }
}

float Ore::getRadius() const {
    return shape.getRadius();
}

bool Ore::isWithinRange(sf::Vector2f point, float range) const {
    // Calculate distance between the point and ore center
    // Use Pythagorean theorem: distance = sqrt((x2-x1)² + (y2-y1)²)
    float dx = point.x - position.x;
    float dy = point.y - position.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    
    // Check if distance is within mining range
    // We add the ore's radius so you can mine by touching the edge
    return distance <= (range + getRadius());
}