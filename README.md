<p align="center">
  <a href="https://github.com/8enrich/Letris" target="blank"><img src="https://github.com/user-attachments/assets/2c076b86-635c-428d-8e32-2f2df8bd239c" width="400" alt="Letris Logo" /></a>
</p>

<h4 align="center">A Simple and Minimalistic Tetris Clone (Powered by <a href="https://github.com/raysan5/raylib">raylib</a>)</h4>

<p align="center">
  <a href="https://github.com/8enrich/Letris/releases"><img src="https://img.shields.io/github/downloads/8enrich/Letris/total" alt="Total Downloads" /></a>
  <a href="https://github.com/8enrich/Letris/stargazers"><img src="https://img.shields.io/github/stars/8enrich/Letris?style=flat&label=stars" alt="Stars" /></a>
  <a href="https://github.com/8enrich/Letris/commits/master"><img src="https://img.shields.io/github/commits-since/8enrich/Letris/0.1v" alt="Commits" /></a>
  <a href="https://opensource.org/licenses/MIT"><img src="https://img.shields.io/github/license/8enrich/Letris" alt="License" /></a>
  <a href="https://github.com/8enrich/Letris/actions"><img src="https://img.shields.io/github/actions/workflow/status/8enrich/Letris/cmake-multi-platform.yml" alt="Build Status" /></a>
</p>

# Description

Letris is an open-source Tetris clone developed in C++ using [raylib](https://github.com/raysan5/raylib) and [nlohmann/json](https://github.com/nlohmann/json). It features a simple and minimalistic design, aiming to capture the essence of the classic game with modern touches.

# Features

- **Minimalistic Design**: A clean and straightforward user interface.
- **Cross-Platform**: Compatible with multiple operating systems.
- **Customizable Settings**: Adjust game settings to your preference.
- **High Score Tracking**: Keep track of your best scores.


# Installation

## Windows
To download the latest Windows version, click [here](https://github.com/8enrich/Letris/releases).

### Running the game from the ZIP
1. Download Letris-Windows-amd64.zip from the latest release and unzip it.
2. Run the executable (letris.exe) inside the folder.

### Running the game from the Installer
1. Download the installer (letris-amd64-Windows.exe).
2. Follow the on-screen instructions to install the game.

## Linux
### Installing the .deb Package

To download the latest version for Ubuntu/Debian, click [here](https://github.com/8enrich/Letris/releases/download/0.1v/letris.deb).

Simply run the .deb file and follow the installation instructions. The package is compatible with GLIBC_2.27 and higher (was compiled in Ubuntu 18.04 LTS).

### Compiling the Game

If you're using a non-Ubuntu/Debian based distribution, you can compile the code yourself. You'll need a relatively recent version of CMake, which can be downloaded [here](https://cmake.org/files/LatestRelease/) or found in your distribution's package manager.

#### Build tools

You will need to install some build tools, such as GCC, Make, Git and CMake 

For Ubuntu/Debian, you can run:
```bash
sudo apt install build-essential git cmake
```
For Fedora you can run
```
sudo dnf install -y gcc gcc-c++ make git cmake
```
For Arch Linux you can run
```bash
sudo pacman -S git base-devel cmake
```
#### Required libraries

[Some libraries are required by raylib](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux) for displaying graphics and audio correctly (ALSA, OpenGL/Mesa and X11)

For Ubuntu/Debian you can run: 

```bash
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```
For Fedora you can run:

```bash
sudo dnf install alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel libatomic
```
For Arch Linux you can run:

```bash
sudo pacman -S alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama
```

Once the dependencies are installed, follow these steps to build the game:

```bash
git clone https://github.com/8enrich/Letris.git # Clone the repository
cd Letris # Enter the repository
mkdir build && cd build # Create and navigate to the build directory
cmake -S .. # Configure the project with CMake
make # Build the game binary
./letris # Run the game
```

Feel free to customize further, but this should make it more structured and clear!


# Usage

in progress

# License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

# Contact

For any inquiries or support, please open an issue on the [GitHub repository](https://github.com/8enrich/Letris).
.
