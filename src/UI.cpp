#include "UI.h"
#include "Player.h"
#include "Inventory.h"
#include "Pickaxe.h"
#include <sstream>
#include <iomanip>
#include <iostream>

/**
 * @brief Constructor initializes UI fonts and elements
 * 
 * This demonstrates SFML font loading and UI component setup.
 * In a real game, you'd load fonts from TTF files.
 */
UI::UI() 
    : m_currentState(UIState::Game)
    , m_previousState(UIState::Game)
    , m_currentPlayer(nullptr)
    , m_animationTimer(0.0f)
    , m_highlightColor(sf::Color::Yellow)
{
    // Initialize font (using SFML's default font for simplicity)
    // In a real game: m_font.loadFromFile("assets/fonts/arial.ttf");
    
    // Set up text objects with default properties
    formatText(m_titleText, "", 24, sf::Color::White);
    formatText(m_bodyText, "", 16, sf::Color::White);
    formatText(m_smallText, "", 12, sf::Color::White);
    formatText(m_statsText, "", 14, sf::Color::White);
    formatText(m_inventoryText, "", 14, sf::Color::White);
    formatText(m_pickaxeText, "", 14, sf::Color::White);
    
    // Set up UI panels
    m_background.setFillColor(sf::Color(0, 0, 0, 180)); // Semi-transparent black
    m_panel.setFillColor(sf::Color(50, 50, 50, 220));   // Dark gray panel
    m_panel.setOutlineColor(sf::Color::White);
    m_panel.setOutlineThickness(2.0f);
    
    // Set up HUD background
    m_hudBackground.setFillColor(sf::Color(0, 0, 0, 160));
    m_hudBackground.setSize(sf::Vector2f(800, 60));
    m_hudBackground.setPosition(0, 0);
    
    std::cout << "UI system initialized" << std::endl;
}

/**
 * @brief Update UI logic and button states
 * 
 * This method handles UI animations, data updates, and interaction states.
 */
void UI::update(float deltaTime, const Player& player) {
    // Store player reference for rendering
    m_currentPlayer = &player;
    
    // Update animation timer for UI effects
    m_animationTimer += deltaTime;
    
    // Update button hover states based on mouse position
    // In a real implementation, you'd get the actual mouse position here
    // updateButtonStates(sf::Mouse::getPosition());
    
    // Update data displays based on current state
    switch (m_currentState) {
        case UIState::Game:
            // Update HUD with current player stats
            updateGameHUDData(player);
            break;
            
        case UIState::Shop:
            // Update shop buttons and prices
            setupShopButtons(player);
            break;
            
        default:
            break;
    }
}

/**
 * @brief Render UI elements for current state
 * 
 * This method demonstrates layered UI rendering with different
 * content based on the current UI state.
 */
void UI::render(sf::RenderWindow& window) {
    switch (m_currentState) {
        case UIState::Game:
            renderGameHUD(window);
            break;
            
        case UIState::Inventory:
            renderInventoryScreen(window);
            break;
            
        case UIState::Shop:
            renderShopScreen(window);
            break;
            
        case UIState::Paused:
            renderPauseScreen(window);
            break;
    }
}

/**
 * @brief Handle UI-specific input events
 * 
 * This method demonstrates event-driven UI interaction with
 * state management and button handling.
 */
void UI::handleEvent(const sf::Event& event, Player& player) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Escape:
                // Toggle pause or return to game
                if (m_currentState == UIState::Game) {
                    setState(UIState::Paused);
                } else {
                    setState(UIState::Game);
                }
                break;
                
            case sf::Keyboard::I:
                toggleInventory();
                break;
                
            case sf::Keyboard::B: // B for "Buy" (shop)
                toggleShop();
                break;
                
            default:
                break;
        }
    }
    
        // Handle button clicks for current state
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                handleButtonClicks(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), player);
            }
        }
}

/**
 * @brief Change UI state with proper transitions
 */
void UI::setState(UIState newState) {
    if (newState != m_currentState) {
        m_previousState = m_currentState;
        m_currentState = newState;
        
        // Clear buttons when changing states
        m_buttons.clear();
        
        std::cout << "UI state changed to: " << static_cast<int>(newState) << std::endl;
    }
}

/**
 * @brief Toggle inventory display
 */
void UI::toggleInventory() {
    if (m_currentState == UIState::Inventory) {
        setState(UIState::Game);
    } else {
        setState(UIState::Inventory);
    }
}

/**
 * @brief Toggle shop display
 */
void UI::toggleShop() {
    if (m_currentState == UIState::Shop) {
        setState(UIState::Game);
    } else {
        setState(UIState::Shop);
    }
}

/**
 * @brief Render main game HUD
 * 
 * This method shows persistent UI elements that appear during gameplay.
 */
void UI::renderGameHUD(sf::RenderWindow& window) {
    if (!m_currentPlayer) return;
    
    // Draw HUD background
    window.draw(m_hudBackground);
    
    // Draw player statistics
    m_statsText.setPosition(10, 10);
    window.draw(m_statsText);
    
    // Draw inventory summary
    m_inventoryText.setPosition(10, 25);
    window.draw(m_inventoryText);
    
    // Draw pickaxe info
    m_pickaxeText.setPosition(10, 40);
    window.draw(m_pickaxeText);
    
    // Draw controls help
    sf::Text helpText;
    formatText(helpText, "Controls: WASD=Move, Space=Mine, I=Inventory, B=Shop, P=Pickaxe Info", 10, sf::Color(128, 128, 128));
    helpText.setPosition(400, 45);
    window.draw(helpText);
}

/**
 * @brief Render detailed inventory screen
 * 
 * This method demonstrates complex data display with formatting
 * and layout management.
 */
void UI::renderInventoryScreen(sf::RenderWindow& window) {
    // Draw semi-transparent background
    m_background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    window.draw(m_background);
    
    // Draw main panel
    m_panel.setSize(sf::Vector2f(500, 400));
    m_panel.setPosition(150, 100);
    window.draw(m_panel);
    
    // Draw title
    formatText(m_titleText, "INVENTORY", 24, sf::Color::White);
    m_titleText.setPosition(350, 120);
    window.draw(m_titleText);
    
    // Draw inventory contents
    if (m_currentPlayer) {
        formatText(m_bodyText, m_currentPlayer->getInventory().getInventoryDisplay(), 16, sf::Color::White);
    } else {
        formatText(m_bodyText, "No player data available", 16, sf::Color::White);
    }
    m_bodyText.setPosition(170, 180);
    window.draw(m_bodyText);
    
    formatText(m_smallText, "Press I to close", 12, sf::Color(128, 128, 128));
    m_smallText.setPosition(170, 450);
    window.draw(m_smallText);
}

/**
 * @brief Render pickaxe upgrade shop
 * 
 * This method demonstrates transaction UI with upgrade information
 * and cost display.
 */
void UI::renderShopScreen(sf::RenderWindow& window) {
    // Draw semi-transparent background
    m_background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    window.draw(m_background);
    
    // Draw main panel
    m_panel.setSize(sf::Vector2f(600, 500));
    m_panel.setPosition(100, 50);
    window.draw(m_panel);
    
    // Draw title
    formatText(m_titleText, "PICKAXE SHOP", 24, sf::Color::White);
    m_titleText.setPosition(320, 70);
    window.draw(m_titleText);
    
    // Draw shop instructions
    formatText(m_bodyText, "Upgrade your pickaxe to mine faster and break harder blocks!\nPress B to close", 16, sf::Color::White);
    m_bodyText.setPosition(120, 110);
    window.draw(m_bodyText);
    
    // Draw current pickaxe info and upgrade options
    if (m_currentPlayer) {
        std::ostringstream shopInfo;
        shopInfo << "Current: " << m_currentPlayer->getPickaxe().getName() << "\n";
        shopInfo << "Power: " << m_currentPlayer->getPickaxe().getPower() << "\n\n";
        
        if (m_currentPlayer->getPickaxe().canUpgrade()) {
            shopInfo << "Upgrade available!\n";
            shopInfo << "Cost: " << m_currentPlayer->getPickaxe().getUpgradeCost() << " ore value";
        } else {
            shopInfo << "Maximum level reached!";
        }
        
        formatText(m_smallText, shopInfo.str(), 14, sf::Color::White);
    } else {
        formatText(m_smallText, "No player data available", 14, sf::Color::White);
    }
    m_smallText.setPosition(120, 180);
    window.draw(m_smallText);
}

/**
 * @brief Render pause menu
 */
void UI::renderPauseScreen(sf::RenderWindow& window) {
    // Draw semi-transparent background
    m_background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    window.draw(m_background);
    
    // Draw pause text
    formatText(m_titleText, "GAME PAUSED", 32, sf::Color::White);
    sf::FloatRect titleBounds(200, 200, 400, 100);
    centerText(m_titleText, titleBounds);
    window.draw(m_titleText);
    
    formatText(m_bodyText, "Press ESC to resume", 16, sf::Color(128, 128, 128)); // Gray color
    sf::FloatRect resumeBounds(200, 300, 400, 50);
    centerText(m_bodyText, resumeBounds);
    window.draw(m_bodyText);
}

/**
 * @brief Create a UI button with standard properties
 */
UIButton UI::createButton(const std::string& text, float x, float y, std::function<void()> callback) {
    UIButton button;
    
    // Set up button shape
    button.shape.setSize(sf::Vector2f(200, 40));
    button.shape.setPosition(x, y);
    button.shape.setFillColor(sf::Color(70, 70, 70));
    button.shape.setOutlineColor(sf::Color::White);
    button.shape.setOutlineThickness(2.0f);
    
    // Set up button text
    formatText(button.label, text, 16, sf::Color::White);
    sf::FloatRect buttonBounds(x, y, 200, 40);
    centerText(button.label, buttonBounds);
    
    // Set callback
    button.onClick = callback;
    button.isEnabled = true;
    button.isHovered = false;
    
    return button;
}

/**
 * @brief Update button visual states based on mouse position
 */
void UI::updateButtonStates(const sf::Vector2f& mousePos) {
    for (auto& button : m_buttons) {
        // Check if mouse is over button
        button.isHovered = button.shape.getGlobalBounds().contains(mousePos);
        
        // Update button appearance based on state
        if (button.isHovered && button.isEnabled) {
            button.shape.setFillColor(sf::Color(100, 100, 100)); // Lighter when hovered
        } else if (button.isEnabled) {
            button.shape.setFillColor(sf::Color(70, 70, 70));    // Normal color
        } else {
            button.shape.setFillColor(sf::Color(50, 50, 50));    // Darker when disabled
        }
    }
}

/**
 * @brief Format text with consistent styling
 */
void UI::formatText(sf::Text& text, const std::string& content, unsigned int size, const sf::Color& color) {
    text.setString(content);
    text.setCharacterSize(size);
    text.setFillColor(color);
    // text.setFont(m_font); // Uncomment when font is loaded
}

/**
 * @brief Center text within a rectangle
 */
void UI::centerText(sf::Text& text, const sf::FloatRect& bounds) {
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(
        bounds.left + (bounds.width - textBounds.width) / 2.0f,
        bounds.top + (bounds.height - textBounds.height) / 2.0f
    );
}

/**
 * @brief Update game HUD data with current player information
 */
void UI::updateGameHUDData(const Player& player) {
    // Update statistics display
    std::ostringstream statsStream;
    statsStream << "Total Ore Value: " << player.getInventory().getTotalValue();
    m_statsText.setString(statsStream.str());
    
    // Update inventory summary
    std::ostringstream invStream;
    invStream << "Ores: " << player.getInventory().getTotalOreCount();
    m_inventoryText.setString(invStream.str());
    
    // Update pickaxe info
    std::ostringstream pickStream;
    pickStream << "Pickaxe: " << player.getPickaxe().getName() 
               << " (Power: " << player.getPickaxe().getPower() << ")";
    m_pickaxeText.setString(pickStream.str());
}

/**
 * @brief Setup shop buttons based on current player state
 */
void UI::setupShopButtons(const Player& player) {
    (void)player; // Suppress unused parameter warning
    // Clear existing buttons
    m_buttons.clear();
    
    // Add upgrade button if player can upgrade
    // For simplicity in this educational example, we'll just show static info
    // In a real game, you'd create interactive upgrade buttons here
}

/**
 * @brief Handle button click events
 */
void UI::handleButtonClicks(const sf::Vector2f& clickPos, Player& player) {
    (void)player; // Suppress unused parameter warning
    for (auto& button : m_buttons) {
        if (button.shape.getGlobalBounds().contains(clickPos) && button.isEnabled) {
            if (button.onClick) {
                button.onClick();
            }
        }
    }
}

/**
 * @brief Attempt to purchase/upgrade using player resources
 */
void UI::attemptPurchase(Player& player) {
    if (player.getPickaxe().canUpgrade()) {
        // Get required ores for upgrade
        auto recipe = player.getPickaxe().getUpgradeRecipe();
        std::map<OreType, int> requiredOres;
        for (const auto& ingredient : recipe) {
            requiredOres[ingredient.oreType] = ingredient.quantity;
        }
        
        // Check if player has enough ores
        if (player.getInventory().hasEnoughOres(requiredOres)) {
            // Consume ores and upgrade pickaxe
            for (const auto& requirement : requiredOres) {
                player.getInventory().removeOres(requirement.first, requirement.second);
            }
            
            // Upgrade the pickaxe
            player.getPickaxe().attemptUpgrade(player.getInventory().getOreCountsRef());
            
            std::cout << "Pickaxe upgraded to " << player.getPickaxe().getName() << "!" << std::endl;
        } else {
            std::cout << "Not enough ores for upgrade!" << std::endl;
        }
    } else {
        std::cout << "Pickaxe is already at maximum level!" << std::endl;
    }
}