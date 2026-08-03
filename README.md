# Level Editor

This is the standalone level editor for the game engine, used to create and manage room-based level data. 

## Controls

| Action - Input |
| **Change Rooms** - Arrow Keys |
| **Toggle Object Mode** - Tab |
| **Select & Draw Tiles** - Left Mouse Button (`LMB`) |
| **Copy Tiles** - Right Mouse Button (`RMB`) |
| **Scroll / View More Tiles** - Scroll Wheel |
| **Save Level Data** - `S` Key |
| **Load Level Data** - `L` Key |
| **Change Level up** - `Page up` Key |
| **Change Level down** - `Page down` Key |
| **Replace all of that tile** - `R` Key |
| **Copy chunk** - `C` Key |
| **Paste chunk** - `V` Key |

### Requirements
requires pygame and python 3.11

# Game Engine
A 2d retro game engine built in C/C++ using the level editor made in python. You can move with ASDW and fire with space.

## Features
* **Room-Based Entity System:** Dynamically stores and manages entities within specific game rooms.
* **Custom Level Editor:** Tooling built to design and export world layouts.

## Prerequisites & Building
To compile and run this project, you must have **SDL2** installed and properly linked in your compiler settings. It's configured to run using sdl2 in the project directory.

### Setup & Dependencies
IDE: Visual Studio 2017
Library: SDL2 / SDL_image / SDL_Mixer

*Note: This project links to external SDL2 directories. To compile on a different machine, please update the Visual Studio Project Properties Include Directories and Linker Additional Dependencies to point to your local SDL2 installation path.

Instructions can be found here: https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php *

### Author
Robert(Tony) Minniti Jr