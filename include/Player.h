#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

// Forward declarations
class World;
class Pickaxe;
class Inventory;

/**
 * @brief Player class handles character movement, mining, and interactions
 * 
 * This class demonstrates several key SFML and game programming concepts:
 * - Sprite handling and animation
 * - Collision detection with tile-based worlds
 * - Input handling for smooth character movement
 * - Sound effect triggering based on actions
 * 
 * The player is the main interface between the user and the game world,
 * so this class shows how to create responsive, smooth character controls.
 */
class Player {
public:
    /**
     * @brief Constructor initializes player sprite and starting equipment
     * 
     * @param startX Starting X position in the world
     * @param startY Starting Y position in the world
     */
    Player(float startX, float startY);
    
    /**
     * @brief Update player logic including movement and mining
     * 
     * This method demonstrates frame-rate independent movement using deltaTime:
     * - Process keyboard input for movement
     * - Apply movement with collision detection
     * - Handle mining input and actions
     * - Update sprite animations
     * 
     * @param deltaTime Time elapsed since last frame
     * @param world Reference to the world for collision detection and mining
     */
    void update(float deltaTime, World& world);
    
    /**
     * @brief Render the player sprite to the screen
     * 
     * This shows basic sprite rendering with SFML:
     * - Setting sprite position based on world coordinates
     * - Drawing the sprite with proper transformations
     * 
     * @param window The SFML window to draw to
     */
    void render(sf::RenderWindow& window);
    
    /**
     * @brief Handle input events like key presses for mining
     * 
     * Some actions (like mining) work better with event-based input rather
     * than continuous input checking. This method handles those discrete actions.
     * 
     * @param event The SFML event to process
     * @param world Reference to the world for mining interactions
     */
    void handleInput(const sf::Event& event, World& world);
    
    // Getters for player state
    sf::Vector2f getPosition() const { return m_sprite.getPosition(); }
    sf::FloatRect getBounds() const { return m_sprite.getGlobalBounds(); }
    
    /**
     * @brief Get player's current pickaxe for mining calculations
     * @return Reference to the current pickaxe
     */
    Pickaxe& getPickaxe() { return *m_pickaxe; }
    const Pickaxe& getPickaxe() const { return *m_pickaxe; }
    
    /**
     * @brief Get player's inventory for ore management
     * @return Reference to the player's inventory
     */
    Inventory& getInventory() { return *m_inventory; }
    const Inventory& getInventory() const { return *m_inventory; }

private:
    // Visual representation
    sf::Sprite m_sprite;                    ///< Player sprite for rendering
    sf::Texture m_texture;                  ///< Texture containing player graphics
    
    // Movement and physics
    sf::Vector2f m_velocity;                ///< Current movement velocity
    float m_speed;                          ///< Movement speed in pixels per second
    
    // Equipment and inventory
    std::unique_ptr<Pickaxe> m_pickaxe;     ///< Current pickaxe for mining
    std::unique_ptr<Inventory> m_inventory; ///< Inventory for collected ores
    
    // Audio
    sf::SoundBuffer m_miningBuffer;         ///< Sound buffer for mining effects
    sf::Sound m_miningSound;                ///< Sound player for mining
    sf::SoundBuffer m_walkingBuffer;        ///< Sound buffer for footsteps
    sf::Sound m_walkingSound;               ///< Sound player for walking
    
    // Animation state
    float m_animationTime;                  ///< Timer for sprite animation
    int m_currentFrame;                     ///< Current animation frame
    bool m_isMoving;                        ///< Whether player is currently moving
    
    /**
     * @brief Handle continuous keyboard input for movement
     * 
     * This method demonstrates how to handle smooth, continuous movement:
     * - Check multiple keys simultaneously (WASD or arrow keys)
     * - Apply velocity based on input and delta time
     * - Normalize diagonal movement to prevent speed increase
     * 
     * @param deltaTime Time elapsed since last frame
     */
    void handleMovement(float deltaTime);
    
    /**
     * @brief Attempt to mine a block at the specified world position
     * 
     * This method shows how to:
     * - Convert screen/player coordinates to world tile coordinates
     * - Check if a tile can be mined based on pickaxe power
     * - Play appropriate sound effects
     * - Add mined ores to inventory
     * 
     * @param worldX X coordinate in the world to mine
     * @param worldY Y coordinate in the world to mine
     * @param world Reference to the world for mining operations
     */
    void attemptMining(int worldX, int worldY, World& world);
    
    /**
     * @brief Check collision with world tiles
     * 
     * This demonstrates basic collision detection:
     * - Converting player bounds to tile coordinates
     * - Checking solid tiles in the movement path
     * - Preventing movement into solid blocks
     * 
     * @param newPosition The position to check for collisions
     * @param world Reference to the world for tile checking
     * @return True if the position is free to move to
     */
    bool checkCollision(const sf::Vector2f& newPosition, const World& world) const;
    
    /**
     * @brief Update sprite animation based on movement state
     * 
     * This shows basic sprite animation:
     * - Cycling through animation frames over time
     * - Different animations for different states (idle, walking)
     * - Smooth frame transitions
     * 
     * @param deltaTime Time elapsed since last frame
     */
    void updateAnimation(float deltaTime);
};