# Battleship - Beta 

A classic Battleship game built in C++ with [Raylib](https://www.raylib.com/), created as a project for [Hack Club Stardance](https://stardance.hackclub.com/).

##  Game

Classic Battleship gameplay featuring:
- Hit/miss detection logic
- Animations
- Win detection
- (In progress) Manual ship placement

## Download

Download the latest playable Windows build on [itch.io](https://gian-maria01.itch.io/battleship)

### Instructions

1. Download the `.zip` file and extract it to a folder of your choice.
2. Run `Battaglia_navale.exe` to play.

> ⚠️ Windows might show a "Windows protected your PC" warning (SmartScreen) because the executable isn't digitally signed. Click **"More info" → "Run anyway"** to start the game.

> Note: this is a **Beta** version, some features (like manual ship placement) are still in development.

## Building from source

Requirements:
- [MSYS2](https://www.msys2.org/) with the MinGW64 toolchain
- [Raylib](https://www.raylib.com/) installed via pacman

The compiled executable requires the following DLLs in the same folder (found in `C:\msys64\mingw64\bin\`):
- `libraylib.dll`
- `libgcc_s_seh-1.dll`
- `libstdc++-6.dll`
- `libwinpthread-1.dll`
- `glfw3.dll`

##  Project status:

The game is currently **playable** but under active development. Next steps:
- [ ] Beater ship placement
- [ ] UI improvements
- [ ] Software optimation
