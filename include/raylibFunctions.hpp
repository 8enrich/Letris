#pragma once
#include <raylib.h>
#include "Vec2.hpp"
#include "Settings.hpp"

namespace ray_functions {
  void DrawRectangle(Vec2<int> pos, Vec2<int> widthHeight, Color color);
  void DrawRectangle(Vec2<double> pos, Vec2<double> widthHeight, Color color);
  void DrawFormatedRectangle(Vec2<double> pos, Vec2<double> widthHeight, Color color);
  void DrawRectangleLinesEx(Vec2<int> pos, Vec2<int> widthHeight, int lineThickness, Color color);
  void DrawRectangleLinesEx(Vec2<double> pos, Vec2<double> widthHeight, int lineThickness, Color color);
  void DrawText(const char * text, Vec2<int> pos, int fontSize, Color Color);
  void DrawText(const char * text, Vec2<double> pos, int fontSize, Color Color);
  constexpr int KeySequence[7] = {ROTATECW, LEFT, DOWN, RIGHT, INSTANTFALL, ROTATEACW, HOLD};
  int GetKeyDown(int);
  int GetAction(int);
  void DrawFormatedText(const char * text, Vec2<double> pos, float fontSize, Color color);
  Vec2<double> FakePositionToRealPosition(Vec2<double> pos, std::string text, float fontSize);
    
  template<typename T, typename U>
  Rectangle CreateRectangleVec(Vec2<T> pos, Vec2<U> widthHeight){
    Rectangle rec;
    rec.x = pos.GetX();
    rec.y = pos.GetY();
    rec.width = widthHeight.GetX();
    rec.height = widthHeight.GetY();
    return rec;
  }
}
