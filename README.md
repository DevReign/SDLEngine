# Map Editor

This is the standalone map editor for the game engine, used to create and manage room-based level data. 

## Controls

| Action - Input |
| **Change Rooms** - Arrow Keys |
| **Toggle Object Mode** - Tab |
| **Select & Draw Tiles** - Left Mouse Button (`LMB`) |
| **Copy Tiles** - Right Mouse Button (`RMB`) |
| **Scroll / View More Tiles** - Scroll Wheel |
| **Save Level Data** - `S` Key |
| **Load Level Data** - `L` Key |

### Requirements
requires pygame and python 3.11

# Game Engine
A 2d game engine built in C with a map editor made in python

## Features
* **Room-Based Entity System:** Dynamically stores and manages entities within specific game rooms.
* **Custom Map Editor:** Tooling built to design and export world layouts.

## Prerequisites & Building
To compile and run this project, you must have **SDL2** installed and properly linked in your compiler settings.

### Setup & Dependencies
IDE: Visual Studio 2022
Graphics/Input Library: SDL2 / SDL_image

*Note: This project links to external SDL2 directories. To compile on a different machine, please update the Visual Studio Project Properties Include Directories and Linker Additional Dependencies to point to your local SDL2 installation path.

Instructions can be found here: https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php *

### Author
Robert(Tony) Minniti