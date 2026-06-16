*This project has been created as part of the 42 curriculum by wintoo and phonekha.*

## Description
**cub3D** is a 3D game engine project inspired by the world-famous 90s classic, Wolfenstein 3D. The primary goal of this project is to explore the mathematics and mechanics of raycasting by creating a dynamic, graphical 3D representation from a 2D map. 

### Features
- **Raycasting Engine:** Utilizes the DDA (Digital Differential Analyzer) algorithm to render walls with accurate perspective and distance handling.
- **Texture Mapping:** Support for distinct textures on the North, South, East, and West faces of walls.
- **Interactive Doors:** Animated doors that can be opened and closed using a key press, complete with an auto-close timer.
- **Dynamic Sprites:** Features animated sprites that move towards the player and respawn across the map.
- **Minimap:** A heads-up 2D display showing the player's position, line of sight, and immediate surroundings (walls, floors, doors).
- **Camera Control:** Support for smooth keyboard rotation as well as toggleable mouse-based camera movement.

## Instructions

### Prerequisites
- **C Compiler:** `cc` or `gcc`
- **Make**
- **CMake:** Required to build the MLX42 library.
- **GLFW:** Dependency for MLX42 window management.

### Compilation
Clone the repository and compile the project using the provided Makefile. The build process will automatically configure and compile the required MLX42 library alongside the game.
```bash
make

## Execution

Run the game by passing a valid `.cub` map file as an argument:
./cub3D ./maps/your_map.cub

## Controls

* **W, A, S, D:** Move forward, backward, left, and right.
* **Left / Right Arrows:** Rotate the camera.
* **Mouse:** Look around (when mouse lock is active).
* **TAB:** Toggle mouse lock and cursor visibility.
* **F:** Interact with doors (open/close).
* **ESC:** Exit the game.

### Helpful Resources & Tutorials
* **[3D Ray Casting Game with cub3D](https://devabdilah.medium.com/3d-ray-casting-game-with-cub3d-7a116376056a)** - A Medium article detailing the development process and concepts behind the project.
* **[cub3D Video Guide](https://www.youtube.com/watch?v=eOCQfxRQ2pY)** - A visual walkthrough and explanation of raycasting mechanics.
* **[Map Parsing and Validating Guide](https://hackmd.io/@nszl/H1LXByIE2#Map-parsing-and-validating)** - A comprehensive HackMD resource focusing specifically on the map parsing and validation requirements.
* **[MLX42 GitHub Repository](https://github.com/codam-coding-college/MLX42)** - The official documentation and source code for the graphics library used to build this project.