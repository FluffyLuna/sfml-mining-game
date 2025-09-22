#include "World.h"
#include <iostream>
#include <cmath>
#include <memory>

/**
 * @brief Constructor initializes world and generates terrain
 * 
 * This demonstrates proper initialization order and resource setup.
 */
World::World() : m_rng(std::random_device{}()), m_dist(0.0f, 1.0f) {
    // Initialize the tile grid
    m_tiles.resize(WORLD_HEIGHT);
    for (auto& row : m_tiles) {
        row.resize(WORLD_WIDTH);
    }
    
    // Set up the reusable tile sprite for efficient rendering
    m_tileSprite.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    
    // Generate the world terrain
    generateTerrain();
    
    std::cout << "World generated with " << WORLD_WIDTH << "x" << WORLD_HEIGHT << " tiles" << std::endl;
}

/**
 * @brief Update world logic
 * 
 * This method would handle dynamic world changes in more complex games.
 * For now, the mining world is mostly static after generation.
 */
void World::update(float deltaTime) {
    (void)deltaTime; // Suppress unused parameter warning
    // In a more complex game, this might handle:
    // - Falling sand/gravel physics
    // - Plant growth and decay
    // - Liquid flow (water, lava)
    // - Random ore regeneration
    // - Day/night cycles affecting visibility
    
    // For this educational example, we keep it simple
    // but show where such systems would be implemented
}

/**
 * @brief Render the visible portion of the world
 * 
 * This method demonstrates efficient tile-based rendering with view culling.
 * Only tiles visible on screen are drawn to maintain good performance.
 */
void World::render(sf::RenderWindow& window, const sf::Vector2f& playerPos) {
    (void)playerPos; // Suppress unused parameter warning
    // Get the current view to determine what's visible
    sf::View currentView = window.getView();
    sf::Vector2f viewCenter = currentView.getCenter();
    sf::Vector2f viewSize = currentView.getSize();
    
    // Calculate visible tile range with some padding for smooth scrolling
    int minTileX = std::max(0, static_cast<int>((viewCenter.x - viewSize.x / 2) / TILE_SIZE) - 1);
    int maxTileX = std::min(WORLD_WIDTH - 1, static_cast<int>((viewCenter.x + viewSize.x / 2) / TILE_SIZE) + 1);
    int minTileY = std::max(0, static_cast<int>((viewCenter.y - viewSize.y / 2) / TILE_SIZE) - 1);
    int maxTileY = std::min(WORLD_HEIGHT - 1, static_cast<int>((viewCenter.y + viewSize.y / 2) / TILE_SIZE) + 1);
    
    // Render only the visible tiles
    for (int y = minTileY; y <= maxTileY; y++) {
        for (int x = minTileX; x <= maxTileX; x++) {
            const Tile& tile = m_tiles[y][x];
            
            // Skip rendering air tiles (optimization)
            if (tile.type == TileType::Air) {
                continue;
            }
            
            // Set tile position and color
            m_tileSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            m_tileSprite.setFillColor(tile.color);
            
            // Add visual depth effect for different tile types
            sf::Color renderColor = tile.color;
            if (tile.type == TileType::Stone || tile.type == TileType::Dirt) {
                // Add subtle shading based on depth
                float depthFactor = std::min(1.0f, y / 20.0f);
                renderColor.r = static_cast<sf::Uint8>(renderColor.r * (1.0f - depthFactor * 0.3f));
                renderColor.g = static_cast<sf::Uint8>(renderColor.g * (1.0f - depthFactor * 0.3f));
                renderColor.b = static_cast<sf::Uint8>(renderColor.b * (1.0f - depthFactor * 0.3f));
            }
            
            m_tileSprite.setFillColor(renderColor);
            
            // Draw the tile
            window.draw(m_tileSprite);
            
            // Add outline for ore tiles to make them more visible
            if (tile.type >= TileType::OreCopper && tile.type <= TileType::OreDiamond) {
                m_tileSprite.setFillColor(sf::Color::Transparent);
                m_tileSprite.setOutlineThickness(2.0f);
                m_tileSprite.setOutlineColor(sf::Color::White);
                window.draw(m_tileSprite);
                m_tileSprite.setOutlineThickness(0.0f);
            }
        }
    }
}

/**
 * @brief Attempt to mine a tile at given coordinates
 * 
 * This method implements the core mining mechanic with proper validation,
 * difficulty scaling, and resource generation.
 */
std::unique_ptr<Ore> World::mineTile(int x, int y, float pickaxePower) {
    if (!isValidCoordinate(x, y)) {
        return nullptr;  // Invalid coordinates
    }
    
    Tile& tile = m_tiles[y][x];
    
    // Check if tile can be mined
    if (tile.type == TileType::Air || tile.type == TileType::Bedrock) {
        return nullptr;  // Can't mine air or bedrock
    }
    
    // Check if pickaxe is powerful enough
    if (pickaxePower < tile.hardness * 0.5f) {
        std::cout << "Pickaxe too weak to mine this block!" << std::endl;
        return nullptr;
    }
    
    // Determine what ore to drop based on tile type
    std::unique_ptr<Ore> droppedOre = nullptr;
    
    switch (tile.type) {
        case TileType::OreCopper:
            droppedOre = std::make_unique<Ore>(OreType::Copper);
            break;
        case TileType::OreIron:
            droppedOre = std::make_unique<Ore>(OreType::Iron);
            break;
        case TileType::OreGold:
            droppedOre = std::make_unique<Ore>(OreType::Gold);
            break;
        case TileType::OreDiamond:
            droppedOre = std::make_unique<Ore>(OreType::Diamond);
            break;
        case TileType::Stone:
        case TileType::Dirt:
            // Stone and dirt don't drop ores, but can still be mined
            break;
        default:
            break;
    }
    
    // Replace the mined tile with air
    tile = getTileProperties(TileType::Air);
    
    // Print mining feedback
    if (droppedOre) {
        std::cout << "Mined " << droppedOre->getName() << " ore!" << std::endl;
    } else {
        std::cout << "Block mined successfully!" << std::endl;
    }
    
    return droppedOre;
}

/**
 * @brief Get tile type at coordinates with bounds checking
 */
TileType World::getTileType(int x, int y) const {
    if (!isValidCoordinate(x, y)) {
        return TileType::Bedrock;  // Treat out-of-bounds as solid
    }
    return m_tiles[y][x].type;
}

/**
 * @brief Check if tile blocks movement
 */
bool World::isTileSolid(int x, int y) const {
    if (!isValidCoordinate(x, y)) {
        return true;  // Out-of-bounds is solid
    }
    return m_tiles[y][x].isSolid;
}

/**
 * @brief Convert world coordinates to tile coordinates
 */
sf::Vector2i World::worldToTile(float worldX, float worldY) const {
    return sf::Vector2i(
        static_cast<int>(worldX / TILE_SIZE),
        static_cast<int>(worldY / TILE_SIZE)
    );
}

/**
 * @brief Convert tile coordinates to world position
 */
sf::Vector2f World::tileToWorld(int tileX, int tileY) const {
    return sf::Vector2f(
        tileX * TILE_SIZE,
        tileY * TILE_SIZE
    );
}

/**
 * @brief Generate the initial world terrain
 * 
 * This method demonstrates procedural generation techniques for creating
 * an interesting and balanced mining world.
 */
void World::generateTerrain() {
    std::cout << "Generating terrain..." << std::endl;
    
    // First pass: Create basic layers
    for (int y = 0; y < WORLD_HEIGHT; y++) {
        for (int x = 0; x < WORLD_WIDTH; x++) {
            if (y < 3) {
                // Surface area - mostly air with some dirt
                if (y == 2 && m_dist(m_rng) < 0.7f) {
                    m_tiles[y][x] = getTileProperties(TileType::Dirt);
                } else {
                    m_tiles[y][x] = getTileProperties(TileType::Air);
                }
            } else if (y < 8) {
                // Shallow underground - dirt and some stone
                if (m_dist(m_rng) < 0.8f) {
                    m_tiles[y][x] = getTileProperties(TileType::Dirt);
                } else {
                    m_tiles[y][x] = getTileProperties(TileType::Stone);
                }
            } else if (y < WORLD_HEIGHT - 2) {
                // Deep underground - mostly stone
                m_tiles[y][x] = getTileProperties(TileType::Stone);
            } else {
                // Bottom layer - unbreakable bedrock
                m_tiles[y][x] = getTileProperties(TileType::Bedrock);
            }
        }
    }
    
    // Second pass: Create cave systems
    generateCaves();
    
    // Third pass: Place ore deposits
    placeOres(TileType::OreCopper, 0.15f, 5, WORLD_HEIGHT - 5);    // Copper: common, shallow to deep
    placeOres(TileType::OreIron, 0.08f, 10, WORLD_HEIGHT - 5);    // Iron: less common, deeper
    placeOres(TileType::OreGold, 0.03f, 15, WORLD_HEIGHT - 5);    // Gold: rare, deep only
    placeOres(TileType::OreDiamond, 0.008f, 25, WORLD_HEIGHT - 5); // Diamond: very rare, very deep
    
    std::cout << "Terrain generation complete!" << std::endl;
}

/**
 * @brief Place ore deposits with realistic distribution
 * 
 * This method demonstrates resource placement algorithms that create
 * balanced and interesting exploration opportunities.
 */
void World::placeOres(TileType oreType, float rarity, int minDepth, int maxDepth) {
    for (int y = minDepth; y <= maxDepth; y++) {
        for (int x = 0; x < WORLD_WIDTH; x++) {
            // Only place ores in stone blocks
            if (m_tiles[y][x].type == TileType::Stone) {
                // Use depth-based rarity scaling
                float depthFactor = 1.0f + (y - minDepth) * 0.05f; // Slightly more common deeper
                float adjustedRarity = rarity * depthFactor;
                
                if (m_dist(m_rng) < adjustedRarity) {
                    m_tiles[y][x] = getTileProperties(oreType);
                    
                    // Create small ore veins by placing additional ores nearby
                    if (m_dist(m_rng) < 0.3f) { // 30% chance for vein formation
                        for (int dy = -1; dy <= 1; dy++) {
                            for (int dx = -1; dx <= 1; dx++) {
                                int nx = x + dx;
                                int ny = y + dy;
                                if (isValidCoordinate(nx, ny) && 
                                    m_tiles[ny][nx].type == TileType::Stone &&
                                    m_dist(m_rng) < 0.4f) {
                                    m_tiles[ny][nx] = getTileProperties(oreType);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/**
 * @brief Generate interesting cave systems
 * 
 * This method creates cave networks that make exploration more engaging
 * and provide natural mining opportunities.
 */
void World::generateCaves() {
    // Create several cave systems using random walks
    int numCaves = 8 + m_rng() % 5; // 8-12 cave systems
    
    for (int cave = 0; cave < numCaves; cave++) {
        // Pick random starting point in underground area
        int startX = m_rng() % WORLD_WIDTH;
        int startY = 8 + m_rng() % (WORLD_HEIGHT - 15); // Start in stone layer
        
        int currentX = startX;
        int currentY = startY;
        
        // Random walk to create cave tunnel
        int caveLength = 20 + m_rng() % 30; // 20-50 tiles long
        
        for (int step = 0; step < caveLength; step++) {
            // Create a small room around current position
            int roomSize = 1 + m_rng() % 3; // 1-3 tiles radius
            
            for (int dy = -roomSize; dy <= roomSize; dy++) {
                for (int dx = -roomSize; dx <= roomSize; dx++) {
                    int nx = currentX + dx;
                    int ny = currentY + dy;
                    
                    if (isValidCoordinate(nx, ny) && 
                        m_tiles[ny][nx].type != TileType::Bedrock) {
                        // Create air pockets, but leave some support pillars
                        if (m_dist(m_rng) < 0.8f) {
                            m_tiles[ny][nx] = getTileProperties(TileType::Air);
                        }
                    }
                }
            }
            
            // Move in random direction for next step
            int direction = m_rng() % 4;
            switch (direction) {
                case 0: currentX++; break; // Right
                case 1: currentX--; break; // Left  
                case 2: currentY++; break; // Down
                case 3: currentY--; break; // Up
            }
            
            // Keep within bounds
            currentX = std::max(1, std::min(WORLD_WIDTH - 2, currentX));
            currentY = std::max(8, std::min(WORLD_HEIGHT - 3, currentY));
        }
    }
}

/**
 * @brief Get tile properties for a given tile type
 * 
 * This method centralizes tile behavior definition, making it easy
 * to balance and modify tile characteristics.
 */
Tile World::getTileProperties(TileType type) const {
    switch (type) {
        case TileType::Air:
            return Tile(type, 0.0f, false, sf::Color::Black);
            
        case TileType::Dirt:
            return Tile(type, 0.5f, true, sf::Color(139, 69, 19)); // Brown
            
        case TileType::Stone:
            return Tile(type, 1.0f, true, sf::Color(128, 128, 128)); // Gray
            
        case TileType::Bedrock:
            return Tile(type, 1000.0f, true, sf::Color(64, 64, 64)); // Dark gray
            
        case TileType::OreCopper:
            return Tile(type, 1.2f, true, sf::Color(184, 115, 51)); // Orange-brown
            
        case TileType::OreIron:
            return Tile(type, 1.5f, true, sf::Color(169, 169, 169)); // Light gray
            
        case TileType::OreGold:
            return Tile(type, 2.0f, true, sf::Color(255, 215, 0)); // Gold
            
        case TileType::OreDiamond:
            return Tile(type, 3.0f, true, sf::Color(185, 242, 255)); // Light blue
            
        default:
            return Tile();
    }
}

/**
 * @brief Validate tile coordinates
 */
bool World::isValidCoordinate(int x, int y) const {
    return x >= 0 && x < WORLD_WIDTH && y >= 0 && y < WORLD_HEIGHT;
}