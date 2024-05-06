#pragma once
#include <raylib.h>
#include "Vec2.hpp"
namespace ray_wrapper {
  void DrawRectangle(Vec2<int> pos, Vec2<int> widthHeight, Color color);
  void DrawRectangleLinesEx(Vec2<int> pos, Vec2<int> widthHeight, int lineThickness, Color color);
}
