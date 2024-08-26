#pragma once
#include "Vec2.hpp"
#include <raylib.h>
#include <fstream>
#include <unordered_map>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#ifndef ASSETS_PATH
#define ASSETS_PATH "./assets/"
#endif

namespace settings {
  extern std::ifstream f; 
  extern json db; 
  extern int screenWidth;
  extern int screenHeight;
  extern bool isWindowed;
  constexpr int fps = 30;
  extern int cellSize;
  constexpr int padding = 2;
  extern Vec2<int> boardPosition;
  extern Vec2<int> boardWidthHeight;
  extern int volume;
  extern std::vector<int> highscores;
  constexpr KeyboardKey controls[5][7] = {
    {KEY_W, KEY_A, KEY_S, KEY_D, KEY_SPACE, KEY_LEFT_SHIFT, KEY_C},
    {KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_SPACE, KEY_Z, KEY_C},
    {KEY_I, KEY_J, KEY_K, KEY_L, KEY_SPACE, KEY_Z, KEY_C},
    {KEY_K, KEY_H, KEY_J, KEY_L, KEY_SPACE, KEY_Z, KEY_C},
    {KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_ENTER, KEY_RIGHT_CONTROL, KEY_RIGHT_SHIFT}
  };
  constexpr Vec2<int> screenSizes[5] = {{800, 600}, {1280, 720}, {1366, 768}, {1600, 900}, {1920, 1080}};
  void UpdateWindowSize(Vec2<int>);
  void UpdateBoardPosition();
  void FullScreen();
}

enum Screens {
  GAME,
  COOP,
  COOPOPTIONS,
  OPTIONS,
  EXIT,
  MENU,
  PAUSE,
  GAMEOVER,
  NOTSCREEN,
};

enum Keys{
  ROTATECW = -7,
  LEFT,
  DOWN,
  RIGHT,
  INSTANTFALL,
  ROTATEACW,
  HOLD,
};
