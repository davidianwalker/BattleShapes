BattleShapes
============

Visual Studio
-------------

This requires Visual Studio 2017.

1. Run `install.py` (requires Python3.6)
2. Open the project (double click `.sln`) - this should launch Visual Studio.
3. Make sure the build mode is set to Release.
4. Finally press the green play button near the top of the window.
5. Note the game only runs for a few seconds.


cmake
-----

For macOS/Linux users, or Windows users who don't want to use Visual Studio and know how to use cmake, pkg-config etc.

This uses pkg-config to discover where the SDL2 libraries are.
You'll need to install pkg-config, and the following libraries: sdl2, sdl2_image, sdl2_ttf

To build:

```
mkdir build
cd build
cmake ..
make
```

To run:

```
cd build  # if necessary
cd BattleShapes
./battleshapes
```
