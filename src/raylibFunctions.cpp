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

void ray_functions::DrawFormatedRectangle(Vec2<double> pos, Vec2<double> widthHeight, Color color){
  int width = settings::screenWidth, height = settings::screenHeight;
  DrawRectangle(width * (pos.GetX() - widthHeight.GetX()/2.0f), height * pos.GetY(), width * widthHeight.GetX(), height * widthHeight.GetY(), color);
}

Vec2<double> ray_functions::FakePositionToRealPosition(Vec2<double> pos, std::string text, float fontSize){
  int width = settings::screenWidth, height = settings::screenHeight;
  return {width * pos.GetX() - MeasureText(text.c_str(), height * fontSize)/2, height * pos.GetY()};
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

int ray_functions::GetKeyDown(int control){
  for(int i = 1; i < 4; i++) if(IsKeyDown(settings::controls[control][i])) return KeySequence[i];
  return KEY_NULL;
}

int ray_functions::GetAction(int control){
  auto keyPressed = GetKeyPressed();
  for(int i = 0; i < 7; i++) if(IsKeyPressed(settings::controls[control][i])) return KeySequence[i];
  return keyPressed;
}

void ray_functions::DrawFormatedText(const char *text, Vec2<double> pos, float fontSize, Color color){
  int width = settings::screenWidth, height = settings::screenHeight;
  DrawText(text, width * pos.GetX() - MeasureText(text, height * fontSize)/2, height * pos.GetY(), height * fontSize, color);
}

