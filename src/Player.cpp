#include "Player.h"
#include "World.h"
#include "Pickaxe.h"
#include "Inventory.h"
#include <iostream>
#include <cmath>

/**
 * @brief Constructor initializes player at starting position
 * 
 * This demonstrates proper initialization of game objects with
 * multiple component systems (graphics, audio, equipment).
 */
Player::Player(float startX, float startY) 
    : m_velocity(0.0f, 0.0f)
    , m_speed(150.0f)  // 150 pixels per second
    , m_animationTime(0.0f)
    , m_currentFrame(0)
    , m_isMoving(false)
{
    // Initialize equipment
    m_pickaxe = std::make_unique<Pickaxe>(PickaxeTier::Wood);
    m_inventory = std::make_unique<Inventory>();
    
    // Set up player sprite
    // For this educational example, we'll create a simple colored rectangle
    // In a real game, you'd load this from an image file
    if (!m_texture.create(32, 32)) {
        std::cerr << "Failed to create player texture!" << std::endl;
    }
    
    // Create a simple player texture programmatically
    sf::Image playerImage;
    playerImage.create(32, 32, sf::Color::Blue); // Blue player character
    m_texture.update(playerImage);
    
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(startX, startY);
    
    // Load audio for mining and walking
    // Note: In a real game, you'd load these from files
    // For this example, we'll create silent buffers that demonstrate the concept
    
    std::cout << "Player created at position (" << startX << ", " << startY << ")" << std::endl;
    std::cout << "Starting equipment: " << m_pickaxe->getName() << std::endl;
}

/**
 * @brief Update player logic including movement and animations
 * 
 * This method demonstrates the typical entity update pattern:
 * - Process input for movement
 * - Apply physics and collision detection
 * - Update animations and visual state
 * - Handle interaction with world systems
 */
void Player::update(float deltaTime, World& world) {
    // Handle continuous movement input
    handleMovement(deltaTime);
    
    // Apply collision detection and movement
    sf::Vector2f newPosition = m_sprite.getPosition() + m_velocity * deltaTime;
    
    if (checkCollision(newPosition, world)) {
        m_sprite.setPosition(newPosition);
    } else {
        // Stop movement if collision detected
        m_velocity = sf::Vector2f(0.0f, 0.0f);
        m_isMoving = false;
    }
    
    // Update animations
    updateAnimation(deltaTime);
    
    // Update audio based on movement
    if (m_isMoving && m_walkingSound.getStatus() != sf::Sound::Playing) {
        // In a real game, this would play footstep sounds
        // m_walkingSound.play();
    } else if (!m_isMoving) {
        m_walkingSound.stop();
    }
}

/**
 * @brief Render player sprite to screen
 * 
 * This demonstrates basic sprite rendering with SFML.
 * The sprite position is automatically set by the update method.
 */
void Player::render(sf::RenderWindow& window) {
    // Draw the player sprite
    window.draw(m_sprite);
    
    // In a more advanced game, you might also draw:
    // - Equipment overlays (pickaxe, armor)
    // - Status effects (glowing, damage indicators)
    // - Player name or health bar
    // - Mining progress indicators
}

/**
 * @brief Handle discrete input events like mining actions
 * 
 * This method demonstrates event-based input handling for actions
 * that should trigger once per key press rather than continuously.
 */
void Player::handleInput(const sf::Event& event, World& world) {
    if (event.type == sf::Event::KeyPressed) {
        // Handle mining input
        if (event.key.code == sf::Keyboard::Space) {
            // Determine mining target based on player position and facing direction
            sf::Vector2f playerPos = m_sprite.getPosition();
            sf::Vector2i playerTile = world.worldToTile(playerPos.x + 16, playerPos.y + 16); // Center of sprite
            
            // Try to mine the tile the player is standing on or adjacent tiles
            // For simplicity, we'll mine the tile directly below the player
            int mineX = playerTile.x;
            int mineY = playerTile.y + 1; // Tile below player
            
            attemptMining(mineX, mineY, world);
        }
        
        // Handle inventory display
        if (event.key.code == sf::Keyboard::I) {
            std::cout << m_inventory->getInventoryDisplay() << std::endl;
        }
        
        // Handle pickaxe info display
        if (event.key.code == sf::Keyboard::P) {
            std::cout << "Current Pickaxe: " << m_pickaxe->getName() 
                      << " (Power: " << m_pickaxe->getPower() 
                      << ", Speed: " << m_pickaxe->getSpeed() << ")" << std::endl;
        }
    }
}

/**
 * @brief Handle continuous keyboard input for smooth movement
 * 
 * This method demonstrates how to create responsive character controls
 * with proper diagonal movement handling and frame-rate independence.
 */
void Player::handleMovement(float deltaTime) {
    (void)deltaTime; // Suppress unused parameter warning
    sf::Vector2f movement(0.0f, 0.0f);
    bool wasMoving = m_isMoving;
    m_isMoving = false;
    
    // Check for movement input using SFML's real-time input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        movement.y -= 1.0f;
        m_isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += 1.0f;
        m_isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movement.x -= 1.0f;
        m_isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement.x += 1.0f;
        m_isMoving = true;
    }
    
    // Normalize diagonal movement to prevent speed increase
    if (movement.x != 0.0f && movement.y != 0.0f) {
        float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
        movement /= length;
    }
    
    // Apply speed and delta time for frame-rate independent movement
    m_velocity = movement * m_speed;
    
    // Start walking sound if just started moving
    if (m_isMoving && !wasMoving) {
        // In a real game: m_walkingSound.play();
    }
}

/**
 * @brief Attempt to mine a block at world coordinates
 * 
 * This method demonstrates the core mining interaction system,
 * including validation, tool requirements, and resource generation.
 */
void Player::attemptMining(int worldX, int worldY, World& world) {
    // Check if position is valid for mining
    TileType tileType = world.getTileType(worldX, worldY);
    
    if (tileType == TileType::Air) {
        std::cout << "Nothing to mine here!" << std::endl;
        return;
    }
    
    if (tileType == TileType::Bedrock) {
        std::cout << "Bedrock is too hard to mine!" << std::endl;
        return;
    }
    
    // Calculate mining time based on pickaxe power and block hardness
    // This would normally be handled over multiple frames for realistic timing
    std::cout << "Mining..." << std::endl;
    
    // Play mining sound effect
    // In a real game: m_miningSound.play();
    
    // Attempt to mine the tile
    auto minedOre = world.mineTile(worldX, worldY, m_pickaxe->getPower());
    
    if (minedOre) {
        // Successfully mined an ore
        m_inventory->addOre(*minedOre);
        std::cout << "Added " << minedOre->getName() << " to inventory!" << std::endl;
        std::cout << "Total " << minedOre->getName() << ": " 
                  << m_inventory->getOreCount(minedOre->getType()) << std::endl;
    }
}

/**
 * @brief Check collision with world tiles
 * 
 * This method demonstrates basic tile-based collision detection,
 * essential for preventing players from walking through solid blocks.
 */
bool Player::checkCollision(const sf::Vector2f& newPosition, const World& world) const {
    // Get player bounds at new position
    sf::FloatRect playerBounds(newPosition.x, newPosition.y, 32, 32); // 32x32 player size
    
    // Convert bounds to tile coordinates
    int leftTile = static_cast<int>(playerBounds.left / World::TILE_SIZE);
    int rightTile = static_cast<int>((playerBounds.left + playerBounds.width - 1) / World::TILE_SIZE);
    int topTile = static_cast<int>(playerBounds.top / World::TILE_SIZE);
    int bottomTile = static_cast<int>((playerBounds.top + playerBounds.height - 1) / World::TILE_SIZE);
    
    // Check all tiles that the player would overlap
    for (int y = topTile; y <= bottomTile; y++) {
        for (int x = leftTile; x <= rightTile; x++) {
            if (world.isTileSolid(x, y)) {
                return false; // Collision detected
            }
        }
    }
    
    return true; // No collision, movement is allowed
}

/**
 * @brief Update sprite animation based on movement state
 * 
 * This method demonstrates basic sprite animation for character movement.
 * In a real game, this would cycle through different frames of animation.
 */
void Player::updateAnimation(float deltaTime) {
    if (m_isMoving) {
        m_animationTime += deltaTime;
        
        // Change animation frame every 0.2 seconds
        if (m_animationTime >= 0.2f) {
            m_animationTime = 0.0f;
            m_currentFrame = (m_currentFrame + 1) % 4; // 4 animation frames
            
            // In a real game, you would update the sprite's texture rectangle here
            // to show different frames of the walking animation
            // m_sprite.setTextureRect(sf::IntRect(m_currentFrame * 32, 0, 32, 32));
        }
        
        // Add a subtle color change to show movement
        // sf::Color animColor = sf::Color::Blue;
        // animColor.r = 100 + static_cast<sf::Uint8>(m_currentFrame * 30);
        // m_sprite.setColor(animColor); // Uncomment for color animation
    } else {
        // Reset to idle state
        m_animationTime = 0.0f;
        m_currentFrame = 0;
        // m_sprite.setColor(sf::Color::Blue); // Reset to base color
    }
}