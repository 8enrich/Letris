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

Vec2<double> ray_functions::FakePositionToRealPosition(Vec2<double> pos, std::string text, int fontSize){
  return {settings::screenWidth * pos.GetX() - MeasureText(text.c_str(), settings::screenHeight * fontSize)/2, settings::screenHeight * pos.GetY()};  
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
  for(int i = 0; i < 6; i++) if(keyPressed == settings::controls[control][i]) return KeySequence[i];
  if(keyPressed == KEY_C) return KEY_C;
  if(keyPressed == KEY_ESCAPE) return KEY_ESCAPE;
  return keyPressed;
}

void ray_functions::DrawFormatedText(const char *text, Vec2<double> pos, float fontSize, Color color){
  int width = settings::screenWidth, height = settings::screenHeight;
  DrawText(text, width * pos.GetX() - MeasureText(text, height * fontSize)/2, height * pos.GetY(), height * fontSize, color);
}

bool ray_functions::HorizontalSlideAnimation(const char *textOut, const char *textIn, int x, int y, int speed, float fontSize, Color color){
  int signal = (speed > 0)? 1: -1, newX = x - speed, width = settings::screenWidth;
  DrawText(textOut, newX, y, fontSize, color);
  if(newX < 0 || newX > settings::screenWidth)
    DrawText(textIn, newX + (signal * width), y, fontSize, color);
  if(newX + width <= x || newX - width >= x) return true;
  return false;
}

bool ray_functions::HorizontalSlideAnimation(const char *textOut, const char *textIn, float x, float y, int speed, float fontSize, Color color){
  int signal = (speed > 0)? 1: -1, height = settings::screenHeight;
  float newX = x - (float)speed/1000;
  DrawFormatedText(textOut, Vec2<double>{(float)newX, (float)y}, fontSize, color);
  if(newX - MeasureText(textOut, height * fontSize)/2 <= 0 || newX + MeasureText(textOut, height * fontSize)/2 >= 1)
    DrawFormatedText(textIn, Vec2<double>{(float)newX + signal, (float)y}, fontSize, color);
  if(newX + 1 <= x || newX - 1 >= x) return true;
  return false;
}
