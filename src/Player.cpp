#include "Player.h"
#include <cmath>

// Define static constants
// These control how the player moves and behaves
const float Player::MOVE_SPEED = 300.0f;      // Pixels per second
const float Player::FRICTION = 0.85f;         // How quickly player stops (0-1)
const float Player::MIN_VELOCITY = 10.0f;     // Minimum speed before stopping

Player::Player(float startX, float startY) 
    : position(startX, startY)
    , velocity(0.0f, 0.0f)
    , miningSpeed(1.0f)        // 1 second between mines initially
    , miningRange(50.0f)       // Can mine ores within 50 pixels
    , oreMultiplier(1.0f)      // Get 1 ore per mine initially
{
    // Set up the visual representation of the player
    // We use a blue circle to represent the player character
    shape.setRadius(15.0f);
    shape.setFillColor(sf::Color::Blue);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2.0f);
    
    // Center the shape on the player's position
    // By default, SFML draws shapes from their top-left corner
    // We want the center of the circle to be at the player's position
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(position);
}

void Player::update(float deltaTime) {
    // Apply movement based on current velocity
    // deltaTime ensures smooth movement regardless of framerate
    position += velocity * deltaTime;
    
    // Apply friction to gradually slow down the player
    // This makes movement feel more natural and controllable
    velocity *= FRICTION;
    
    // Stop very small movements to prevent jittering
    // When velocity gets very small, just set it to zero
    if (std::abs(velocity.x) < MIN_VELOCITY) velocity.x = 0.0f;
    if (std::abs(velocity.y) < MIN_VELOCITY) velocity.y = 0.0f;
    
    // Update the visual position to match the logical position
    shape.setPosition(position);
}

void Player::handleInput() {
    // Reset acceleration for this frame
    sf::Vector2f acceleration(0.0f, 0.0f);
    
    // Check for movement input
    // We support both WASD and arrow keys for accessibility
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        acceleration.y -= MOVE_SPEED;  // Move up (negative Y)
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        acceleration.y += MOVE_SPEED;  // Move down (positive Y)
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        acceleration.x -= MOVE_SPEED;  // Move left (negative X)
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        acceleration.x += MOVE_SPEED;  // Move right (positive X)
    }
    
    // Apply acceleration to velocity
    // This creates responsive but smooth movement
    velocity += acceleration * 0.016f; // Assuming ~60 FPS for smooth acceleration
    
    // Limit maximum velocity to prevent player from moving too fast
    const float MAX_VELOCITY = MOVE_SPEED;
    float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (speed > MAX_VELOCITY) {
        velocity = (velocity / speed) * MAX_VELOCITY;
    }
}

void Player::render(sf::RenderWindow& window) {
    // Draw the player to the screen
    window.draw(shape);
}

sf::Vector2f Player::getPosition() const {
    return position;
}

float Player::getMiningRange() const {
    return miningRange;
}

float Player::getMiningSpeed() const {
    return miningSpeed;
}

float Player::getOreMultiplier() const {
    return oreMultiplier;
}

void Player::upgradeMiningSpeed(float improvement) {
    // Reduce mining time (faster mining)
    // We subtract the improvement because lower time = faster mining
    miningSpeed = std::max(0.1f, miningSpeed - improvement);
}

void Player::upgradeMiningRange(float improvement) {
    // Increase mining range
    miningRange += improvement;
}

void Player::upgradeOreMultiplier(float improvement) {
    // Increase ore collection multiplier
    oreMultiplier += improvement;
}

void Player::constrainToWindow(int windowWidth, int windowHeight) {
    // Keep player within window bounds
    // This prevents the player from disappearing off the edge of the screen
    
    float radius = shape.getRadius();
    
    // Check left and right bounds
    if (position.x - radius < 0) {
        position.x = radius;
        velocity.x = 0; // Stop horizontal movement when hitting wall
    }
    if (position.x + radius > windowWidth) {
        position.x = windowWidth - radius;
        velocity.x = 0;
    }
    
    // Check top and bottom bounds  
    if (position.y - radius < 0) {
        position.y = radius;
        velocity.y = 0; // Stop vertical movement when hitting wall
    }
    if (position.y + radius > windowHeight) {
        position.y = windowHeight - radius;
        velocity.y = 0;
    }
    
    // Update visual position
    shape.setPosition(position);
}