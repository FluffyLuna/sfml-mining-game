#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

// Forward declarations to avoid circular dependencies
class Player;
class World;
class UI;

/**
 * @brief Main Game class that manages the entire game state and logic
 * 
 * This class demonstrates SFML's window management, event handling, and the 
 * typical game loop structure used in most games. It serves as the central
 * hub that coordinates all game systems.
 * 
 * Key SFML concepts demonstrated:
 * - sf::RenderWindow for window creation and management
 * - Event polling and handling
 * - Delta time for frame-rate independent movement
 * - Render states and drawing order
 */
class Game {
public:
    /**
     * @brief Constructor initializes SFML window and game resources
     * 
     * This demonstrates proper SFML initialization including:
     * - Window creation with specific dimensions and title
     * - Setting frame rate limits for consistent gameplay
     * - Loading game resources (textures, sounds, fonts)
     */
    Game();
    
    /**
     * @brief Destructor handles cleanup of resources
     * 
     * SFML handles most cleanup automatically through RAII,
     * but this is where you'd handle any manual cleanup if needed
     */
    ~Game();
    
    /**
     * @brief Main game loop - the heart of any game
     * 
     * This method demonstrates the standard game loop pattern:
     * 1. Process events (input handling)
     * 2. Update game logic (physics, AI, game state)
     * 3. Render graphics (draw everything to screen)
     * 
     * The loop continues until the window is closed or game exits
     */
    void run();

private:
    // Core SFML components
    sf::RenderWindow m_window;              ///< Main game window for rendering
    sf::Clock m_clock;                      ///< Clock for measuring delta time
    sf::Event m_event;                      ///< Event object for input handling
    
    // Game state management
    bool m_isRunning;                       ///< Flag to control main game loop
    float m_deltaTime;                      ///< Time between frames for smooth animation
    
    // Game systems - using smart pointers for automatic memory management
    std::unique_ptr<Player> m_player;       ///< Player character and controls
    std::unique_ptr<World> m_world;         ///< Mining world with terrain and ores
    std::unique_ptr<UI> m_ui;               ///< User interface for stats and inventory
    
    // Audio system
    sf::Music m_backgroundMusic;            ///< Background music for atmosphere
    
    /**
     * @brief Process all SFML events like keyboard input, window events, etc.
     * 
     * This method demonstrates proper SFML event handling:
     * - Polling events in a loop to ensure none are missed
     * - Handling different event types (KeyPressed, MouseClicked, etc.)
     * - Proper window close handling
     * 
     * @param deltaTime Time elapsed since last frame
     */
    void processEvents(float deltaTime);
    
    /**
     * @brief Update all game logic and systems
     * 
     * This is where the game "thinks" - all non-rendering logic happens here:
     * - Player movement and collision detection
     * - Mining mechanics and ore collection
     * - World updates and physics
     * - UI state updates
     * 
     * @param deltaTime Time elapsed since last frame for smooth movement
     */
    void update(float deltaTime);
    
    /**
     * @brief Render all visual elements to the screen
     * 
     * This method demonstrates SFML's rendering pipeline:
     * - Clear the screen with a background color
     * - Draw all game objects in the correct order (background to foreground)
     * - Display the final rendered frame
     * 
     * Drawing order is crucial - objects drawn later appear on top!
     */
    void render();
    
    /**
     * @brief Initialize all game resources and systems
     * 
     * Separating initialization from the constructor makes error handling easier
     * and allows for more complex setup procedures
     */
    void initialize();
    
    /**
     * @brief Load all game assets (textures, sounds, fonts)
     * 
     * This method demonstrates SFML resource loading:
     * - Loading textures from files
     * - Setting up sound buffers and music
     * - Loading fonts for text rendering
     * - Error handling for missing files
     */
    void loadAssets();
};