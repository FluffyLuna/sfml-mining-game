#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

// Forward declarations
class Player;
class Inventory;
class Pickaxe;

/**
 * @brief Enumeration of different UI screen states
 * 
 * This demonstrates how to manage different game screens and interfaces
 * in a clean, organized way.
 */
enum class UIState {
    Game,           ///< Main game HUD and playing interface
    Inventory,      ///< Detailed inventory view
    Shop,           ///< Pickaxe upgrade shop
    Paused          ///< Pause menu
};

/**
 * @brief Structure representing a clickable UI button
 * 
 * This shows how to create interactive UI elements with proper
 * encapsulation and event handling.
 */
struct UIButton {
    sf::RectangleShape shape;           ///< Visual representation
    sf::Text label;                     ///< Button text
    std::function<void()> onClick;      ///< Callback function for clicks
    bool isHovered;                     ///< Whether mouse is over button
    bool isEnabled;                     ///< Whether button can be clicked
    
    UIButton() : isHovered(false), isEnabled(true) {}
};

/**
 * @brief UI class manages all user interface elements and interactions
 * 
 * This class demonstrates several important UI programming concepts:
 * - State-based UI management
 * - Event-driven button interactions
 * - Text rendering and formatting
 * - Layout management and positioning
 * - Visual feedback for user actions
 * 
 * The UI is crucial for player feedback and game accessibility,
 * making complex systems understandable and interactive.
 */
class UI {
public:
    /**
     * @brief Constructor initializes UI fonts and layout
     * 
     * This demonstrates SFML font loading and UI setup:
     * - Loading TTF fonts from files
     * - Creating reusable text objects
     * - Setting up button templates
     * - Initializing layout constants
     */
    UI();
    
    /**
     * @brief Update UI logic and animations
     * 
     * This method handles:
     * - Button hover state updates
     * - Animation timers for UI effects
     * - Data refresh from game systems
     * - Input state management
     * 
     * @param deltaTime Time elapsed since last frame
     * @param player Reference to player for data access
     */
    void update(float deltaTime, const Player& player);
    
    /**
     * @brief Render all UI elements for the current state
     * 
     * This method demonstrates layered UI rendering:
     * - Background elements first
     * - Main content elements
     * - Overlay elements (tooltips, popups)
     * - Debug information (if enabled)
     * 
     * @param window The SFML window to draw to
     */
    void render(sf::RenderWindow& window);
    
    /**
     * @brief Handle UI-specific events like button clicks
     * 
     * This method shows event-driven UI interaction:
     * - Mouse click detection on buttons
     * - Keyboard shortcuts for UI actions
     * - State transitions based on input
     * 
     * @param event The SFML event to process
     * @param player Reference to player for shop transactions
     */
    void handleEvent(const sf::Event& event, Player& player);
    
    /**
     * @brief Get the current UI state
     * @return Current UIState enum value
     */
    UIState getCurrentState() const { return m_currentState; }
    
    /**
     * @brief Change to a different UI state
     * 
     * This method demonstrates state transition management:
     * - Validation of state changes
     * - Cleanup of previous state
     * - Initialization of new state
     * - Visual transition effects
     * 
     * @param newState The UI state to transition to
     */
    void setState(UIState newState);
    
    /**
     * @brief Toggle inventory display on/off
     * 
     * Convenience method for common UI action.
     */
    void toggleInventory();
    
    /**
     * @brief Toggle shop display on/off
     * 
     * Convenience method for common UI action.
     */
    void toggleShop();

private:
    // Game state management
    UIState m_currentState;                 ///< Current active UI screen
    UIState m_previousState;                ///< Previous state for back navigation
    const Player* m_currentPlayer;          ///< Reference to current player for data access
    
    // Font and text rendering
    sf::Font m_font;                        ///< Main UI font
    sf::Text m_titleText;                   ///< Large text for titles
    sf::Text m_bodyText;                    ///< Regular text for content
    sf::Text m_smallText;                   ///< Small text for details
    
    // UI Elements
    std::vector<UIButton> m_buttons;        ///< Collection of interactive buttons
    sf::RectangleShape m_background;        ///< Background for UI panels
    sf::RectangleShape m_panel;             ///< Main content panel
    
    // Game HUD elements
    sf::RectangleShape m_hudBackground;     ///< HUD background bar
    sf::Text m_statsText;                   ///< Player statistics display
    sf::Text m_inventoryText;               ///< Quick inventory summary
    sf::Text m_pickaxeText;                 ///< Current pickaxe info
    
    // Animation and effects
    float m_animationTimer;                 ///< Timer for UI animations
    sf::Color m_highlightColor;             ///< Color for highlighting elements
    
    /**
     * @brief Render the main game HUD
     * 
     * This method shows persistent UI elements:
     * - Player statistics (ore counts, pickaxe info)
     * - Mini-map or world information
     * - Health/status indicators
     * - Quick action buttons
     * 
     * @param window The window to render to
     */
    void renderGameHUD(sf::RenderWindow& window);
    
    /**
     * @brief Render the detailed inventory screen
     * 
     * This method demonstrates complex data display:
     * - Tabular ore information
     * - Total value calculations
     * - Sorting and filtering options
     * - Visual ore representations
     * 
     * @param window The window to render to
     */
    void renderInventoryScreen(sf::RenderWindow& window);
    
    /**
     * @brief Render the pickaxe upgrade shop
     * 
     * This method shows transaction UI design:
     * - Available upgrades with costs
     * - Current vs. upgraded stats comparison
     * - Transaction confirmation
     * - Insufficient funds feedback
     * 
     * @param window The window to render to
     */
    void renderShopScreen(sf::RenderWindow& window);
    
    /**
     * @brief Render pause menu overlay
     * 
     * @param window The window to render to
     */
    void renderPauseScreen(sf::RenderWindow& window);
    
    /**
     * @brief Create a button with specified properties
     * 
     * This factory method demonstrates consistent button creation:
     * - Standard sizing and positioning
     * - Consistent visual styling
     * - Proper callback assignment
     * - Accessibility considerations
     * 
     * @param text Button label text
     * @param x X position on screen
     * @param y Y position on screen
     * @param callback Function to call when clicked
     * @return Created UIButton object
     */
    UIButton createButton(const std::string& text, float x, float y, std::function<void()> callback);
    
    /**
     * @brief Update button visual states based on mouse position
     * 
     * This method handles button interaction feedback:
     * - Hover state changes (color, size)
     * - Click state visualization
     * - Disabled state rendering
     * - Smooth transitions between states
     * 
     * @param mousePos Current mouse position
     */
    void updateButtonStates(const sf::Vector2f& mousePos);
    
    /**
     * @brief Format text for consistent UI display
     * 
     * This utility method handles:
     * - Font size and color setting
     * - Text alignment and positioning
     * - Word wrapping for long text
     * - Number formatting for values
     * 
     * @param text Text object to format
     * @param content String content to display
     * @param size Font size to use
     * @param color Text color
     */
    void formatText(sf::Text& text, const std::string& content, unsigned int size, const sf::Color& color);
    
    /**
     * @brief Center text within a specified area
     * 
     * Utility method for consistent text positioning.
     * 
     * @param text Text object to center
     * @param bounds Rectangle to center within
     */
    void centerText(sf::Text& text, const sf::FloatRect& bounds);
    
    /**
     * @brief Setup shop buttons and upgrade options
     * 
     * This method creates the interactive elements for the shop:
     * - Upgrade buttons for each pickaxe tier
     * - Cost display and validation
     * - Transaction confirmation dialogs
     */
    void setupShopButtons(const Player& player);
    
    /**
     * @brief Handle shop purchase attempt
     * 
     * This method demonstrates transaction processing:
     * - Validate sufficient resources
     * - Execute the purchase transaction
     * - Update player equipment
     * - Provide success/failure feedback
     * 
     * @param player Player to perform transaction for
     */
    void attemptPurchase(Player& player);
    
    /**
     * @brief Update game HUD data with current player information
     */
    void updateGameHUDData(const Player& player);
    
    /**
     * @brief Handle button click events
     */
    void handleButtonClicks(const sf::Vector2f& clickPos, Player& player);
};