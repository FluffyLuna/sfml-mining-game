# SFML Mining Game

A fun and educational mining game built with SFML 2.6+ where you collect ores and upgrade your pickaxe!

## 🎮 Game Features

- **Movement**: Move around with WASD or Arrow keys
- **Mining**: Collect ores by getting close and pressing SPACE
- **4 Ore Types**: 
  - 🟤 **Copper** (Common) - Basic building material
  - ⚪ **Iron** (Common) - Stronger than copper
  - 🟡 **Gold** (Uncommon) - Valuable precious metal  
  - 💎 **Diamond** (Rare) - The most valuable ore
- **Upgrade Shop**: Press 'S' to trade ores for pickaxe improvements
- **Three Upgrade Types**:
  1. **Mining Speed** - Mine ores faster
  2. **Mining Range** - Mine from further away
  3. **Ore Multiplier** - Get more ores per mine

## 🛠️ Building the Game

### Prerequisites

- **C++ Compiler** (GCC 7+ or equivalent)
- **CMake** (3.16+)
- **SFML 2.6+** development libraries

### Ubuntu/Debian Installation

```bash
# Install dependencies
sudo apt update
sudo apt install build-essential cmake libsfml-dev

# Clone and build
git clone https://github.com/FluffyLuna/sfml-mining-game.git
cd sfml-mining-game
mkdir build && cd build
cmake ..
make

# Run the game
./bin/mining_game
```

### Other Linux Distributions

Install SFML development packages using your package manager:
- **Fedora**: `sudo dnf install SFML-devel cmake gcc-c++`
- **Arch**: `sudo pacman -S sfml cmake gcc`

### Windows

1. Install [SFML](https://www.sfml-dev.org/download.php) and [CMake](https://cmake.org/download/)
2. Open Command Prompt in the project directory
3. Run:
```cmd
mkdir build
cd build
cmake .. -DSFML_DIR=path/to/sfml
cmake --build .
```

### macOS

```bash
# Install dependencies with Homebrew
brew install sfml cmake

# Build and run
mkdir build && cd build
cmake ..
make
./bin/mining_game
```

## 🎯 How to Play

1. **Move Around**: Use WASD or arrow keys to move your blue character
2. **Mine Ores**: Walk close to colored circles (ores) and press SPACE to mine them
3. **Check Inventory**: Your collected ores are shown on the left side of the screen
4. **Open Shop**: Press 'S' to open the upgrade shop
5. **Buy Upgrades**: In the shop, press 1, 2, or 3 to buy different upgrades
6. **Close Shop**: Press 'S' again to close the shop and continue mining
7. **Quit Game**: Press ESC to exit

## 📚 Educational Aspects

This game is designed to be educational and easy to understand:

### Code Structure
- **Object-Oriented Design**: Each game element (Player, Ore, Shop, etc.) is its own class
- **Separation of Concerns**: Game logic, rendering, and input handling are clearly separated
- **Extensive Comments**: Every function and important code section is documented

### Game Programming Concepts Demonstrated
- **Game Loop**: Main loop handling input, update, and render phases
- **Delta Time**: Frame-rate independent movement and timing
- **Collision Detection**: Checking if player is close enough to mine ores
- **State Management**: Switching between game and shop states
- **Random Generation**: Procedural ore spawning with weighted probabilities
- **Resource Management**: Inventory system and upgrade costs

### Files Overview
- `src/main.cpp` - Entry point and error handling
- `src/Game.cpp` - Main game loop and state management
- `src/Player.cpp` - Player movement and upgrades
- `src/Ore.cpp` - Ore types, spawning, and properties
- `src/Inventory.cpp` - Resource tracking and management
- `src/Shop.cpp` - Upgrade system and costs
- `include/*.h` - Header files with detailed documentation

## 🔧 Game Balance

The game is balanced to provide a satisfying progression:

### Ore Rarity (spawn rates)
- Copper: 50% chance
- Iron: 30% chance  
- Gold: 15% chance
- Diamond: 5% chance

### Upgrade Costs
Upgrades become progressively more expensive, requiring rarer ores for higher levels.

### Starting Stats
- Mining Speed: 1.0 seconds per mine
- Mining Range: 50 pixels
- Ore Multiplier: 1x (1 ore per mine)

## 🎨 Customization Ideas

Want to modify the game? Here are some ideas:

1. **Add More Ores**: Create new ore types in `Ore.h/cpp`
2. **New Upgrades**: Add different upgrade types in `Shop.h/cpp`
3. **Visual Improvements**: Add sprites instead of simple shapes
4. **Sound Effects**: Add audio feedback for mining and upgrades
5. **Save System**: Implement progress saving between sessions
6. **Achievements**: Add goals and unlockables

## 🐛 Troubleshooting

### Game Won't Start
- Make sure SFML is properly installed
- Check that your graphics drivers are up to date
- Verify the executable has proper permissions

### Text Not Displaying
- The game uses SFML's default font, which may not always work
- To fix: Add a font file and load it in `Game.cpp` and `Shop.cpp`

### Building Issues
- Ensure all dependencies are installed
- Try `make clean` and rebuild
- Check CMake output for missing libraries

## 📝 License

This project is open source and available for educational use. Feel free to modify and learn from it!

## 🤝 Contributing

This is an educational project, but improvements are welcome! Areas for contribution:
- Better graphics and animations
- Sound effects and music
- Additional game mechanics
- Code optimizations
- Documentation improvements

---

**Have fun mining and learning! 🎮⛏️💎**