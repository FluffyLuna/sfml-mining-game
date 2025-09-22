#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "Ore.h"

/**
 * @brief Enumeration of different tile types in the mining world
 * 
 * This demonstrates how to organize different game elements and their properties.
 * Each tile type has different characteristics affecting gameplay.
 */
enum class TileType {
    Air,        ///< Empty space - can be moved through
    Stone,      ///< Basic mineable rock
    Dirt,       ///< Soft earth - easy to mine
    Bedrock,    ///< Unbreakable bottom layer
    OreCopper,  ///< Copper ore deposits
    OreIron,    ///< Iron ore deposits  
    OreGold,    ///< Gold ore deposits
    OreDiamond  ///< Diamond ore deposits (rarest)
};

/**
 * @brief Structure representing a single tile in the world
 * 
 * This shows how to organize tile data efficiently while keeping
 * memory usage reasonable for large worlds.
 */
struct Tile {
    TileType type;              ///< What kind of tile this is
    float hardness;             ///< How difficult it is to mine (mining time multiplier)
    bool isSolid;               ///< Whether the player can pass through
    sf::Color color;            ///< Visual color for rendering
    
    /**
     * @brief Constructor with default values for easy tile creation
     */
    Tile(TileType t = TileType::Air, float h = 1.0f, bool solid = false, sf::Color c = sf::Color::Black)
        : type(t), hardness(h), isSolid(solid), color(c) {}
};

/**
 * @brief World class manages the mining environment and terrain generation
 * 
 * This class demonstrates several important game programming concepts:
 * - 2D tile-based world representation
 * - Procedural world generation using random numbers
 * - Efficient rendering of large tile grids
 * - Spatial data structures for fast lookups
 * - Resource management for ore placement
 * 
 * The world is the stage where all mining action takes place, so it needs
 * to be both visually appealing and functionally robust.
 */
class World {
public:
    // World dimensions
    static const int WORLD_WIDTH = 100;     ///< Width in tiles
    static const int WORLD_HEIGHT = 50;     ///< Height in tiles  
    static const int TILE_SIZE = 32;        ///< Size of each tile in pixels
    
    /**
     * @brief Constructor initializes world and generates terrain
     * 
     * This demonstrates:
     * - Setting up 2D tile arrays
     * - Initializing random number generators
     * - Calling terrain generation methods
     */
    World();
    
    /**
     * @brief Update world logic (growing plants, falling sand, etc.)
     * 
     * While this mining game focuses on static terrain, this method
     * shows where dynamic world updates would go in more complex games.
     * 
     * @param deltaTime Time elapsed since last frame
     */
    void update(float deltaTime);
    
    /**
     * @brief Render the visible portion of the world
     * 
     * This method demonstrates efficient tile rendering:
     * - Only drawing tiles visible on screen (view culling)
     * - Using sf::RectangleShape for simple tile graphics
     * - Batch rendering for performance
     * - Camera/view transformation handling
     * 
     * @param window The SFML window to draw to
     * @param playerPos Player position for camera centering
     */
    void render(sf::RenderWindow& window, const sf::Vector2f& playerPos);
    
    /**
     * @brief Attempt to mine a tile at the given coordinates
     * 
     * This method shows the core mining mechanic:
     * - Checking if a tile can be mined
     * - Determining mining time based on tile hardness and pickaxe power
     * - Dropping appropriate ores when mining succeeds
     * - Playing visual and audio feedback
     * 
     * @param x X coordinate in tile space
     * @param y Y coordinate in tile space
     * @param pickaxePower How powerful the mining tool is
     * @return Pointer to ore obtained from mining (nullptr if none)
     */
    std::unique_ptr<Ore> mineTile(int x, int y, float pickaxePower);
    
    /**
     * @brief Get the tile type at specific coordinates
     * 
     * This is essential for collision detection and mining logic.
     * Includes bounds checking to prevent array access errors.
     * 
     * @param x X coordinate in tile space
     * @param y Y coordinate in tile space
     * @return The tile type at the given position
     */
    TileType getTileType(int x, int y) const;
    
    /**
     * @brief Check if a tile is solid (blocks player movement)
     * 
     * @param x X coordinate in tile space
     * @param y Y coordinate in tile space
     * @return True if the tile blocks movement
     */
    bool isTileSolid(int x, int y) const;
    
    /**
     * @brief Convert world pixel coordinates to tile coordinates
     * 
     * This utility function is crucial for bridging the gap between
     * pixel-based positions (player, mouse) and tile-based world logic.
     * 
     * @param worldX X position in pixel coordinates
     * @param worldY Y position in pixel coordinates
     * @return Tile coordinates as sf::Vector2i
     */
    sf::Vector2i worldToTile(float worldX, float worldY) const;
    
    /**
     * @brief Convert tile coordinates to world pixel coordinates
     * 
     * @param tileX X coordinate in tile space
     * @param tileY Y coordinate in tile space
     * @return World position as sf::Vector2f
     */
    sf::Vector2f tileToWorld(int tileX, int tileY) const;

private:
    // World data
    std::vector<std::vector<Tile>> m_tiles;     ///< 2D array of world tiles
    
    // Terrain generation
    std::mt19937 m_rng;                         ///< Random number generator for procedural generation
    std::uniform_real_distribution<float> m_dist; ///< Distribution for random values
    
    // Rendering optimization
    sf::RectangleShape m_tileSprite;            ///< Reusable rectangle for tile rendering
    
    /**
     * @brief Generate the initial world terrain
     * 
     * This method demonstrates procedural generation techniques:
     * - Creating realistic cave-like structures
     * - Placing ores with appropriate rarity
     * - Ensuring the world is interesting to explore
     * - Balancing resource availability
     * 
     * The generation creates a layered world with:
     * - Surface layer of dirt
     * - Stone underground with cave systems
     * - Ores distributed by depth and rarity
     * - Unbreakable bedrock at the bottom
     */
    void generateTerrain();
    
    /**
     * @brief Place ore deposits throughout the world
     * 
     * This shows resource distribution logic:
     * - Different ores appear at different depths
     * - Rarer ores are less common
     * - Clustering ores in veins for realistic distribution
     * 
     * @param oreType The type of ore to place
     * @param rarity How rare this ore should be (0.0 = never, 1.0 = always)
     * @param minDepth Minimum depth for this ore type
     * @param maxDepth Maximum depth for this ore type
     */
    void placeOres(TileType oreType, float rarity, int minDepth, int maxDepth);
    
    /**
     * @brief Create cave systems for interesting terrain
     * 
     * This demonstrates advanced procedural generation:
     * - Using cellular automata or random walks
     * - Creating connected cave networks
     * - Balancing accessibility with challenge
     */
    void generateCaves();
    
    /**
     * @brief Get tile properties for a given tile type
     * 
     * This method centralizes tile behavior, making it easy to:
     * - Modify tile properties in one place
     * - Add new tile types consistently
     * - Balance mining difficulty and rewards
     * 
     * @param type The tile type to get properties for
     * @return Tile structure with appropriate properties
     */
    Tile getTileProperties(TileType type) const;
    
    /**
     * @brief Check if coordinates are within world bounds
     * 
     * @param x X coordinate to check
     * @param y Y coordinate to check
     * @return True if coordinates are valid
     */
    bool isValidCoordinate(int x, int y) const;
};