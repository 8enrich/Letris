#pragma once
#include <raylib.h>
#include "Vec2.hpp"
namespace ray_functions {
  void DrawRectangle(Vec2<int> pos, Vec2<int> widthHeight, Color color);
  void DrawRectangle(Vec2<double> pos, Vec2<double> widthHeight, Color color);
  void DrawRectangleLinesEx(Vec2<int> pos, Vec2<int> widthHeight, int lineThickness, Color color);
  void DrawRectangleLinesEx(Vec2<double> pos, Vec2<double> widthHeight, int lineThickness, Color color);
  void DrawText(const char * text, Vec2<int> pos, int fontSize, Color Color);
  void DrawText(const char * text, Vec2<double> pos, int fontSize, Color Color);
  KeyboardKey GetKeyDown();
  void DrawFormatedText(const char * text, Vec2<double> pos, float fontSize, Color color);
}
