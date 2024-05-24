#include "../include/raylibFunctions.hpp"
#include "../include/Settings.hpp"
#include <assert.h>
#include <raylib.h>
void ray_functions::DrawRectangle(Vec2<int> pos, Vec2<int> widthHeight, Color color){
  assert((pos >= 0 && pos < Vec2<int>{GetScreenWidth(), GetScreenHeight()}));
  DrawRectangle(pos.GetX(), pos.GetY(), widthHeight.GetX(), widthHeight.GetY(), color);
}

void ray_functions::DrawRectangle(Vec2<double> pos, Vec2<double> widthHeight, Color color){
  DrawRectangle(pos.GetX(), pos.GetY(), widthHeight.GetX(), widthHeight.GetY(), color);
}
  
void ray_functions::DrawRectangleLinesEx(Vec2<int> pos, Vec2<int> widthHeight, int lineThickness, Color color){
  assert((pos >= 0 && pos < Vec2<int>{GetScreenWidth(), GetScreenHeight()}));
  assert(lineThickness > 0);
  DrawRectangleLinesEx({(float)pos.GetX(), (float) pos.GetY(), (float) widthHeight.GetX(), (float) widthHeight.GetY()}, lineThickness, color);
}

void ray_functions::DrawRectangleLinesEx(Vec2<double> pos, Vec2<double> widthHeight, int lineThickness, Color color){
  assert((pos >= 0 && pos < Vec2<double>{(double)GetScreenWidth(), (double)GetScreenHeight()}));
  assert(lineThickness > 0);
  DrawRectangleLinesEx({(float)pos.GetX(), (float) pos.GetY(), (float) widthHeight.GetX(), (float) widthHeight.GetY()}, lineThickness, color);
}
 
void ray_functions::DrawText(const char * text, Vec2<int> pos, int fontSize, Color Color){
  assert((pos >= 0 && pos < Vec2<int>{GetScreenWidth(), GetScreenHeight()}));
  assert(fontSize > 0);
  DrawText(text, pos.GetX(), pos.GetY(), fontSize, Color);
}

void ray_functions::DrawText(const char * text, Vec2<double> pos, int fontSize, Color Color){
  assert((pos >= 0 && pos < Vec2<double>{(double) GetScreenWidth(), (double) GetScreenHeight()}));
  assert(fontSize > 0);
  DrawText(text, pos.GetX(), pos.GetY(), fontSize, Color);
}

KeyboardKey ray_functions::GetKeyDown(){
  if(IsKeyDown(KEY_D)){ return KEY_D; }
  if(IsKeyDown(KEY_A)){ return KEY_A; }
  if(IsKeyDown(KEY_S)){ return KEY_S; }
  return KEY_NULL;
}

void ray_functions::DrawFormatedText(const char *text, Vec2<double> pos, float fontSize, Color color){
  int width = settings::screenWidth, height = settings::screenHeight;
  DrawText(text, width * pos.GetX() - (MeasureText(text, height * fontSize))/2, height * pos.GetY(), height * fontSize, color);
}
