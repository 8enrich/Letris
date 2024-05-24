#pragma once
#include "Vec2.hpp"
#include <raylib.h>
namespace settings {
  constexpr int screenWidth = 800;
  constexpr int screenHeight = 600;
  constexpr int fps = 30;

  constexpr int cellSize = 23;
  constexpr int padding = 2;
  constexpr Vec2<int> boardPosition {250, 70};
  constexpr Vec2<int> boardWidthHeight {10, 20};
  constexpr KeyboardKey controls[2][6] = {
    {KEY_W, KEY_A, KEY_S, KEY_D, KEY_SPACE, KEY_Z},
    {KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_SPACE, KEY_Z}
  };
}

enum Screens {
  EXIT = -1,
  MENU,
  OPTIONS,
  GAME,
  PAUSE,
  GAMEOVER,
};
