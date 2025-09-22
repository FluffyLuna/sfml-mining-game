# SFML Mining Game - Educational Edition

A complete 2D mining game built with SFML 3.0.1, designed as both an engaging game and a comprehensive learning resource for SFML game development. This project demonstrates essential game programming concepts with extensive educational comments.

## 🎮 Game Features

### Core Gameplay
- **Mining Mechanics**: Mine different terrain blocks to collect valuable ores
- **Four Ore Types**: Copper, Iron, Gold, and Diamond with varying rarity and value
- **Pickaxe Progression**: Upgrade your mining tools for improved efficiency
- **Procedural World**: Randomly generated underground world with caves and ore deposits

### Technical Features
- **Object-Oriented Design**: Clean class separation (Player, World, Ore, Pickaxe, etc.)
- **Comprehensive UI**: Inventory management, shop interface, and game statistics
- **Educational Comments**: Detailed explanations of SFML concepts and game programming patterns
- **Modern C++**: Uses C++17 features and best practices

## 🚀 Quick Start

### Prerequisites
- SFML 3.0.1 or later
- CMake 3.16 or later
- C++17 compatible compiler (GCC, Clang, or MSVC)

### Building the Game

```bash
# Clone the repository
git clone https://github.com/FluffyLuna/sfml-mining-game.git
cd sfml-mining-game

# Create build directory
mkdir build && cd build

# Generate build files
cmake ..

# Build the game
cmake --build .

# Run the game
./SFMLMiningGame
```

### Installing SFML

#### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install libsfml-dev
```

#### macOS (Homebrew)
```bash
brew install sfml
```

#### Windows
Download SFML from [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php) and follow the installation guide.

## 🎯 Controls

| Key | Action |
|-----|--------|
| **WASD** or **Arrow Keys** | Move player |
| **Space** | Mine blocks |
| **I** | Open/close inventory |
| **B** | Open/close shop |
| **P** | Display pickaxe information |
| **ESC** | Pause/unpause game |
| **F1** | Show debug information |

## 🏗️ Project Structure

```
sfml-mining-game/
├── include/           # Header files with comprehensive documentation
│   ├── Game.h        # Main game class and loop management
│   ├── Player.h      # Player movement and mining mechanics
│   ├── World.h       # Terrain generation and tile management
│   ├── Ore.h         # Ore types and properties
│   ├── Pickaxe.h     # Tool progression system
│   ├── Inventory.h   # Resource management
│   └── UI.h          # User interface and menus
├── src/              # Implementation files
├── assets/           # Game resources (textures, sounds, fonts)
└── CMakeLists.txt    # Build configuration
```

## 📚 Learning Objectives

This project demonstrates key SFML and game development concepts:

### SFML Core Concepts
- **Window Management**: Creating windows, handling events, managing views
- **Graphics Rendering**: Sprites, shapes, textures, and render states
- **Event Handling**: Keyboard input, mouse interaction, window events
- **Audio System**: Sound effects and background music integration
- **Resource Management**: Loading and managing game assets

### Game Programming Patterns
- **Game Loop**: Update-render cycle with delta time
- **Entity Management**: Player, world objects, and interactions
- **State Management**: Game states, UI states, and transitions
- **Collision Detection**: Tile-based collision for movement and mining
- **Procedural Generation**: Algorithm-based world creation

### Software Engineering
- **Object-Oriented Design**: Proper class hierarchy and encapsulation
- **Resource Management**: RAII and smart pointers
- **Error Handling**: Robust error checking and recovery
- **Documentation**: Comprehensive code comments and explanations

## 🎮 Gameplay Guide

### Starting Out
1. **Movement**: Use WASD to move your character around the world
2. **Mining**: Press Space while near blocks to mine them with your pickaxe
3. **Collecting**: Mined ores automatically go into your inventory

### Progression System
1. **Collect Ores**: Start by mining common Copper ore
2. **Upgrade Tools**: Trade ores in the shop (B key) for better pickaxes
3. **Mine Deeper**: Better pickaxes can break harder blocks and mine faster
4. **Find Rare Ores**: Deeper underground, discover Iron, Gold, and Diamond

### Ore Types and Values
- **Copper** (Value: 1) - Common, found shallow to deep
- **Iron** (Value: 3) - Less common, found at moderate depths
- **Gold** (Value: 8) - Rare, found deep underground
- **Diamond** (Value: 20) - Very rare, found only at great depths

### Pickaxe Progression
- **Wood Pickaxe** - Starting tool, basic mining capability
- **Stone Pickaxe** - Faster mining, requires 5 Copper
- **Iron Pickaxe** - Much faster, requires 8 Copper + 3 Iron
- **Gold Pickaxe** - Very fast, requires 5 Iron + 2 Gold
- **Diamond Pickaxe** - Ultimate tool, requires 3 Gold + 1 Diamond

## 🔧 Technical Details

### Architecture Overview
The game uses a modular architecture with clear separation of concerns:

- **Game Class**: Main game coordinator, handles the game loop and system integration
- **Player Class**: Character control, mining actions, and equipment management
- **World Class**: Terrain generation, tile management, and mining mechanics
- **UI Class**: User interface, menus, and player feedback
- **Resource Classes**: Ore, Pickaxe, and Inventory for game progression

### Performance Considerations
- **View Culling**: Only visible tiles are rendered for optimal performance
- **Efficient Collision**: Simple AABB collision detection for responsive movement
- **Memory Management**: Smart pointers and RAII for automatic cleanup
- **Frame Rate**: Capped at 60 FPS with vertical sync for smooth gameplay

### Educational Value
Every major class and method includes detailed comments explaining:
- **What** the code does
- **Why** specific approaches were chosen  
- **How** SFML features are being utilized
- **Where** similar patterns apply in other games

## 🤝 Contributing

This project welcomes contributions, especially those that enhance its educational value:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/educational-improvement`)
3. Commit your changes (`git commit -am 'Add helpful explanation of X concept'`)
4. Push to the branch (`git push origin feature/educational-improvement`)
5. Create a Pull Request

### Contribution Ideas
- Additional ore types or biomes
- Enhanced visual effects and animations
- Save/load game functionality
- More detailed audio implementation
- Additional educational comments and documentation

## 📄 License

This project is released under the MIT License. See the LICENSE file for details.

## 🙏 Acknowledgments

- **SFML Team** - For creating an excellent multimedia library
- **Game Development Community** - For sharing knowledge and best practices
- **Educational Resources** - Various tutorials and documentation that inspired this project

## 📞 Support

If you encounter issues or have questions about the code:

1. Check the extensive comments in the source files
2. Review this README for common solutions
3. Open an issue on GitHub with detailed information
4. Join discussions about SFML game development

---

**Happy Mining and Happy Learning!** 🎮📚