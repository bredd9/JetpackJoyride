# Jetpack Joyride

A C++ implementation of the popular endless runner game Jetpack Joyride using the SFML graphics library. 

## Description

This project is a clone of the classic Jetpack Joyride game where players control a character with a jetpack, avoiding dangerous obstacles, collecting coins, and trying to achieve the highest score possible. The game features dynamic difficulty, a custom physics/collision engine, and various interactive UI elements that make the gameplay challenging and highly entertaining.

## Features

* **Player Character** with gravity and jetpack mechanics (controlled via Spacebar)
* **Multiple game objects and obstacles:**
  * Procedurally generated **Coin patterns** (lines, blocks, diagonals, zig-zags)
  * **Piggy Banks** that provide bonus coins upon collection
  * **Homing Missiles** with a dynamic warning/alert system
  * **Animated Laser beams (Zappers)** spawning at various angles (vertical, horizontal, diagonal)
* **Score System** tracking both collected coins and survival time, featuring persistent High Score tracking saved to a local file
* **Dynamic Difficulty** where the game speed multiplier progressively increases over time
* **Complete Audio System:**
  * Background music and specific sound effects (coin collect, laser zap, piggy bank jackpot, missile launch/alert)
  * Interactive UI Volume Slider controlled via mouse drag-and-drop
* **Advanced Menu System** featuring:
  * Main Menu with Play and Scoreboard options
  * Pause functionality (ESC key)
  * Death Screen (Game Over) displaying the final score and options to restart or exit
* **Advanced Collision Detection:** Custom hitbox shrinking and Inverse Transform mathematics to handle pixel-perfect collisions with rotated objects (like lasers)

## Prerequisites

* **CMake** (version 3.26 or higher)
* **SFML 2.6.x**
* **C++ compiler** with C++17 support
* Windows operating system (or Linux/macOS with proper SFML configuration)

## Building the Project

Make sure you have SFML 2.6 installed and properly linked in your system environment or CMake configuration (e.g., at `C:/SFML/SFML-2.6.0`).

1. Clone the repository
  
2. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```
3. Configure and build the project:
   ```bash
   cmake ..
   cmake --build .
   ```

## Controls

* **Spacebar / Up Arrow**: Hold to ignite the jetpack and fly up; release to fall
* **ESC**: Pause / Resume the game
* **Left Mouse Click**: Interact with menus (Play, Main Menu, Exit)
* **Mouse Drag**: Adjust the master volume using the in-game UI slider

## Project Structure

* `src/` - Source files (`.cpp`) implementing the game logic
* `include/` - Header files (`.h`) containing class declarations
* `resources/` - Game assets including textures (`.png`), fonts (`.ttf`), and audio files (`.wav`)
* `CMakeLists.txt` - CMake configuration file for building the project

## Game Components

### Player
* Gravity and velocity-based movement states
* Screen bound restrictions to keep the player in the playable area

### Objects
* Uses Object-Oriented Programming (OOP) with a base `Object` class for polymorphism
* **Static/Pick-up objects**: Coins, Piggy Banks
* **Moving hazards**: Missiles, Animated Lasers 

### Systems & States
* **Collision Engine**: Uses Axis-Aligned Bounding Boxes (AABB) with customizable hitbox insets, and complex Rotated Collision checks for angled obstacles
* **Game States**: Handled seamlessly within the main game loop (`isMenu`, `isPaused`, `isGameOver`)

## Author

* **Stoica Vlad-Alexandru** 

