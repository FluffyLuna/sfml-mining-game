#include "Game.h"
#include <random>
#include <iostream>

Game::Game() 
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Mining Game")
    , showShop(false)
    , oreSpawnInterval(2.0f) // Spawn ore every 2 seconds
{
    // Limit framerate to 60 FPS for consistent performance
    window.setFramerateLimit(60);
    
    // Create game objects
    player = std::make_unique<Player>(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
    inventory = std::make_unique<Inventory>();
    shop = std::make_unique<Shop>();
    
    // Set up UI text
    // Note: We're not loading a font file, so text might not display
    // In a real game, you'd load a font: font.loadFromFile("path/to/font.ttf")
    instructionText.setFont(font);
    instructionText.setString(
        "MINING GAME CONTROLS:\n"
        "WASD/Arrow Keys - Move\n"
        "SPACE - Mine nearby ores\n"
        "S - Open/Close Shop\n"
        "ESC - Quit Game"
    );
    instructionText.setCharacterSize(16);
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition(10, 10);
    
    inventoryText.setFont(font);
    inventoryText.setCharacterSize(14);
    inventoryText.setFillColor(sf::Color::Yellow);
    inventoryText.setPosition(10, 150);
    
    // Spawn some initial ores so the player has something to mine immediately
    for (int i = 0; i < 10; ++i) {
        spawnOre();
    }
    
    updateInventoryDisplay();
}

void Game::run() {
    // Main game loop - this is the heart of the game!
    // The loop continues until the player closes the window
    
    sf::Clock clock; // Used to measure time between frames
    
    while (window.isOpen()) {
        // Calculate delta time for smooth, frame-rate independent movement
        float deltaTime = clock.restart().asSeconds();
        
        // Handle events (input, window close, etc.)
        sf::Event event;
        while (window.pollEvent(event)) {
            handleEvents(event);
        }
        
        // Update game state
        update(deltaTime);
        
        // Render everything
        render();
    }
}

void Game::handleEvents(sf::Event& event) {
    // Handle window close event
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    
    // Handle key press events
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Escape:
                // Quit the game
                window.close();
                break;
                
            case sf::Keyboard::S:
                // Toggle shop
                toggleShop();
                break;
                
            case sf::Keyboard::Space:
                // Try to mine ores
                if (!showShop) {
                    // Check all ores to see if any are in mining range
                    for (size_t i = 0; i < ores.size(); ++i) {
                        if (canMineOre(*ores[i])) {
                            mineOre(i);
                            break; // Only mine one ore per space press
                        }
                    }
                }
                break;
                
            default:
                // If shop is open, let it handle the input
                if (showShop) {
                    if (shop->handleInput(event.key.code, *inventory, *player)) {
                        // An upgrade was purchased, update shop display
                        shop->updateDisplay(*inventory);
                        updateInventoryDisplay();
                    }
                }
                break;
        }
    }
}

void Game::update(float deltaTime) {
    if (!showShop) {
        // Only update game objects when shop is closed
        
        // Handle player input and update player
        player->handleInput();
        player->update(deltaTime);
        player->constrainToWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
        
        // Spawn new ores periodically
        if (oreSpawnClock.getElapsedTime().asSeconds() >= oreSpawnInterval) {
            spawnOre();
            oreSpawnClock.restart();
        }
        
        // Remove ores that are off-screen or if we have too many
        // This prevents the game from slowing down with too many ores
        if (ores.size() > MAX_ORES) {
            ores.erase(ores.begin());
        }
    }
}

void Game::render() {
    // Clear the screen with a dark background
    window.clear(sf::Color(20, 40, 60)); // Dark blue background
    
    if (!showShop) {
        // Render game objects
        
        // Draw all ores
        for (const auto& ore : ores) {
            ore->render(window);
        }
        
        // Draw player
        player->render(window);
        
        // Draw UI
        window.draw(instructionText);
        window.draw(inventoryText);
    } else {
        // Shop is open, render shop instead
        shop->render(window);
    }
    
    // Display everything we just drew
    window.display();
}

void Game::spawnOre() {
    // Don't spawn ores if we already have too many
    if (ores.size() >= MAX_ORES) {
        return;
    }
    
    // Generate random position for the new ore
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xDist(50.0f, WINDOW_WIDTH - 50.0f);
    std::uniform_real_distribution<float> yDist(50.0f, WINDOW_HEIGHT - 50.0f);
    
    float x = xDist(gen);
    float y = yDist(gen);
    
    // Create a random ore at this position
    ores.push_back(Ore::createRandomOre(x, y));
}

bool Game::canMineOre(const Ore& ore) const {
    // Check if the player is close enough to mine this ore
    return ore.isWithinRange(player->getPosition(), player->getMiningRange());
}

void Game::mineOre(size_t oreIndex) {
    if (oreIndex >= ores.size()) {
        return; // Invalid index
    }
    
    // Get the ore we're mining
    const auto& ore = ores[oreIndex];
    
    // Add ore to inventory (considering the player's ore multiplier)
    int amountToAdd = static_cast<int>(player->getOreMultiplier());
    inventory->addOre(ore->getType(), amountToAdd);
    
    // Remove the ore from the world
    ores.erase(ores.begin() + oreIndex);
    
    // Update the inventory display
    updateInventoryDisplay();
    
    // Optional: Print to console for debugging
    std::cout << "Mined " << amountToAdd << " " << ore->getName() << "(s)!" << std::endl;
}

void Game::updateInventoryDisplay() {
    // Update the inventory text display
    inventoryText.setString(inventory->getInventoryString());
}

void Game::toggleShop() {
    showShop = !showShop;
    
    if (showShop) {
        // Shop opened, update its display
        shop->updateDisplay(*inventory);
    }
}