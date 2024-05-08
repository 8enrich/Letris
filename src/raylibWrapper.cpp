#include "../include/raylibWrapper.hpp"
#include <assert.h>
#include <raylib.h>
void ray_wrapper::DrawRectangle(Vec2<int> pos, Vec2<int> widthHeight, Color color){
  assert((pos >= 0 && pos < Vec2{GetScreenWidth(), GetScreenHeight()}));
  DrawRectangle(pos.GetX(), pos.GetY(), widthHeight.GetX(), widthHeight.GetY(), color);
}
  
void ray_wrapper::DrawRectangleLinesEx(Vec2<int> pos, Vec2<int> widthHeight, int lineThickness, Color color){
  assert((pos >= 0 && pos < Vec2{GetScreenWidth(), GetScreenHeight()}));
  assert(lineThickness > 0);
  DrawRectangleLinesEx({(float)pos.GetX(), (float) pos.GetY(), (float) widthHeight.GetX(), (float) widthHeight.GetY()}, lineThickness, color);
}
  
void ray_wrapper::DrawText(const char * text, Vec2<int> pos, int fontSize, Color Color){
  assert((pos >= 0 && pos < Vec2{GetScreenWidth(), GetScreenHeight()}));
  assert(fontSize > 0);
  DrawText(text, pos.GetX(), pos.GetY(), fontSize, Color);
}
