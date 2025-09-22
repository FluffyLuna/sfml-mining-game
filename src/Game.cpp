#include "Game.h"
#include "Player.h"
#include "World.h" 
#include "UI.h"
#include "Pickaxe.h"
#include "Inventory.h"
#include <iostream>

/**
 * @brief Constructor initializes SFML window and game systems
 * 
 * This demonstrates proper SFML initialization and game setup order.
 * The window is created with specific parameters for the mining game.
 */
Game::Game() 
    : m_window(sf::VideoMode(800, 600), "SFML Mining Game - Educational Edition", sf::Style::Titlebar | sf::Style::Close)
    , m_isRunning(true)
    , m_deltaTime(0.0f)
{
    // Set window properties for optimal gameplay
    m_window.setFramerateLimit(60);  // Cap at 60 FPS for consistent gameplay
    m_window.setVerticalSyncEnabled(true);  // Prevent screen tearing
    
    // Initialize game systems
    initialize();
    
    std::cout << "=== SFML Mining Game ===" << std::endl;
    std::cout << "Educational edition with detailed comments" << std::endl;
    std::cout << "Window created: " << m_window.getSize().x << "x" << m_window.getSize().y << std::endl;
}

/**
 * @brief Destructor handles cleanup
 * 
 * SFML handles most cleanup automatically through RAII,
 * but this is where manual cleanup would go if needed.
 */
Game::~Game() {
    std::cout << "Game shutting down..." << std::endl;
}

/**
 * @brief Main game loop - the heart of the game
 * 
 * This method demonstrates the standard game loop pattern used in
 * virtually all real-time games and interactive applications.
 */
void Game::run() {
    std::cout << "Starting main game loop..." << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  WASD or Arrow Keys - Move player" << std::endl;
    std::cout << "  Space - Mine blocks" << std::endl;
    std::cout << "  I - View inventory" << std::endl;
    std::cout << "  B - Open shop" << std::endl;
    std::cout << "  P - View pickaxe info" << std::endl;
    std::cout << "  ESC - Pause game" << std::endl;
    
    // Main game loop continues until window is closed or game exits
    while (m_isRunning && m_window.isOpen()) {
        // 1. Calculate delta time for frame-rate independent movement
        m_deltaTime = m_clock.restart().asSeconds();
        
        // Cap delta time to prevent large jumps (e.g., when debugging)
        if (m_deltaTime > 0.1f) {
            m_deltaTime = 0.1f;
        }
        
        // 2. Process all pending events (input, window events, etc.)
        processEvents(m_deltaTime);
        
        // 3. Update all game logic (physics, AI, game state)
        if (m_isRunning) {  // Only update if not paused
            update(m_deltaTime);
        }
        
        // 4. Render everything to the screen
        render();
    }
}

/**
 * @brief Initialize all game systems and resources
 * 
 * This method sets up all the major game systems in the correct order.
 * Order matters here - some systems depend on others being initialized first.
 */
void Game::initialize() {
    std::cout << "Initializing game systems..." << std::endl;
    
    // Load game assets (textures, sounds, fonts)
    loadAssets();
    
    // Initialize game world (this creates the terrain)
    m_world = std::make_unique<World>();
    std::cout << "World system initialized" << std::endl;
    
    // Initialize player at spawn position
    // Place player at surface level in the middle of the world
    float startX = (World::WORLD_WIDTH / 2) * World::TILE_SIZE;
    float startY = 2 * World::TILE_SIZE;  // Near surface
    m_player = std::make_unique<Player>(startX, startY);
    std::cout << "Player system initialized" << std::endl;
    
    // Initialize UI system
    m_ui = std::make_unique<UI>();
    std::cout << "UI system initialized" << std::endl;
    
    std::cout << "All systems initialized successfully!" << std::endl;
}

/**
 * @brief Load all game assets
 * 
 * This method demonstrates SFML resource loading with error handling.
 * In a real game, you'd load textures, sounds, and fonts from files.
 */
void Game::loadAssets() {
    std::cout << "Loading game assets..." << std::endl;
    
    // Load background music
    // In a real game: m_backgroundMusic.openFromFile("assets/music/background.ogg");
    // m_backgroundMusic.setLoop(true);
    // m_backgroundMusic.setVolume(50);
    // m_backgroundMusic.play();
    
    std::cout << "Assets loaded successfully!" << std::endl;
}

/**
 * @brief Process all SFML events
 * 
 * This method demonstrates proper SFML event handling with delegation
 * to appropriate systems. Events are processed in order of priority.
 */
void Game::processEvents(float deltaTime) {
    (void)deltaTime; // Suppress unused parameter warning
    // Poll all pending events in a loop to ensure none are missed
    while (m_window.pollEvent(m_event)) {
        // Handle window close event
        if (m_event.type == sf::Event::Closed) {
            m_isRunning = false;
            m_window.close();
        }
        
        // Handle window resize event
        if (m_event.type == sf::Event::Resized) {
            // Update the view to match new window size
            sf::FloatRect visibleArea(0, 0, m_event.size.width, m_event.size.height);
            m_window.setView(sf::View(visibleArea));
        }
        
        // Let UI handle its events first (menus have priority)
        if (m_ui) {
            m_ui->handleEvent(m_event, *m_player);
        }
        
        // Let player handle input events (if UI didn't consume them)
        if (m_player && m_ui->getCurrentState() == UIState::Game) {
            m_player->handleInput(m_event, *m_world);
        }
        
        // Handle global game events
        if (m_event.type == sf::Event::KeyPressed) {
            if (m_event.key.code == sf::Keyboard::F1) {
                // F1 for help/debug info
                std::cout << "\n=== Game Status ===" << std::endl;
                std::cout << "Player Position: " << m_player->getPosition().x << ", " << m_player->getPosition().y << std::endl;
                std::cout << "Current Pickaxe: " << m_player->getPickaxe().getName() << std::endl;
                std::cout << "Inventory Value: " << m_player->getInventory().getTotalValue() << std::endl;
                std::cout << "==================\n" << std::endl;
            }
        }
    }
}

/**
 * @brief Update all game logic and systems
 * 
 * This method demonstrates the typical game update cycle where
 * all systems are updated in the correct order with frame timing.
 */
void Game::update(float deltaTime) {
    // Update world systems (physics, environment changes)
    if (m_world) {
        m_world->update(deltaTime);
    }
    
    // Update player (movement, actions, animations)
    if (m_player && m_world) {
        m_player->update(deltaTime, *m_world);
    }
    
    // Update UI (animations, data refresh)
    if (m_ui && m_player) {
        m_ui->update(deltaTime, *m_player);
    }
    
    // Update camera to follow player
    if (m_player) {
        sf::Vector2f playerPos = m_player->getPosition();
        sf::View gameView = m_window.getView();
        
        // Smooth camera following
        sf::Vector2f currentCenter = gameView.getCenter();
        sf::Vector2f targetCenter = playerPos + sf::Vector2f(16, 16); // Center on player sprite
        
        // Lerp towards target position for smooth camera movement
        float cameraSpeed = 3.0f;
        sf::Vector2f newCenter = currentCenter + (targetCenter - currentCenter) * cameraSpeed * deltaTime;
        
        gameView.setCenter(newCenter);
        m_window.setView(gameView);
    }
}

/**
 * @brief Render all visual elements to the screen
 * 
 * This method demonstrates the SFML rendering pipeline with proper
 * draw order (background to foreground) and state management.
 */
void Game::render() {
    // Clear the screen with a background color
    m_window.clear(sf::Color(50, 50, 100));  // Dark blue background
    
    // Draw game world (background layer)
    if (m_world && m_player) {
        m_world->render(m_window, m_player->getPosition());
    }
    
    // Draw player (middle layer)
    if (m_player) {
        m_player->render(m_window);
    }
    
    // Draw UI (foreground layer - always on top)
    if (m_ui) {
        m_ui->render(m_window);
    }
    
    // Display the rendered frame
    m_window.display();
}