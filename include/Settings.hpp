#pragma once
#include "Vec2.hpp"
#include <raylib.h>
namespace settings {
  extern int screenWidth;
  extern int screenHeight;
  constexpr int fps = 30;

  extern int cellSize;
  constexpr int padding = 2;
  extern Vec2<int> boardPosition;
  constexpr Vec2<int> boardWidthHeight {10, 20};
  constexpr KeyboardKey controls[4][6] = {
    {KEY_W, KEY_A, KEY_S, KEY_D, KEY_SPACE, KEY_Z},
    {KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_SPACE, KEY_Z},
    {KEY_I, KEY_J, KEY_K, KEY_L, KEY_SPACE, KEY_Z},
    {KEY_K, KEY_H, KEY_J, KEY_L, KEY_SPACE, KEY_Z}
  };
  constexpr Vec2<int> screenSizes[3] = {{800, 600}, {1080, 720}, {1366, 768}};
  void UpdateWindowSize(Vec2<int>);
  void UpdateBoardPosition();
}

enum Screens {
  GAME,
  OPTIONS,
  EXIT,
  MENU,
  PAUSE,
  GAMEOVER,
};

enum Keys{
  ROTATECW = -6,
  LEFT,
  DOWN,
  RIGHT,
  INSTANTFALL,
  ROTATEACW,
};
