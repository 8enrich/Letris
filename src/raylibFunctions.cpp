#include "../include/raylibFunctions.hpp"
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

KeyboardKey ray_wrapper::GetKeyDown(){
  if(IsKeyDown(KEY_D)){ return KEY_D; }
  if(IsKeyDown(KEY_A)){ return KEY_A; }
  if(IsKeyDown(KEY_S)){ return KEY_S; }
  return KEY_NULL;
}


