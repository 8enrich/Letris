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
  
}
