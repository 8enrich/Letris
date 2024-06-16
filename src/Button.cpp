#include "../include/Button.hpp"
#include "../include/raylibFunctions.hpp"
#include <raylib.h>
  Button::Button(std::string buttonText, float fontSize, Vec2<double> buttonPosition, Screens screen, bool isSelected):
    buttonText(buttonText), fontSize(fontSize), buttonPosition(buttonPosition), screen(screen), isSelected(isSelected)
  {
    buttonWidthHeight= Vec2<float>{(float) buttonText.size() * fontSize, (float) fontSize}; 
  }
  Button::Button(std::string buttonText, float fontSize, Vec2<double> buttonPosition):Button(buttonText, fontSize, buttonPosition, NOTSCREEN){}
  void Button::Draw(){
    Color color = isSelected ? selectedColor: unselectedColor;
    ray_functions::DrawFormatedText(buttonText.c_str(), buttonPosition, fontSize, color);
  }
  void Button::Tick(){
    BeginDrawing();
    Draw();
    EndDrawing();
  }
  void Button::Select(){
    if (!isSelected) isSelected = true;
  }
  void Button::Unselect(){
    if (isSelected) isSelected = false;
  }
  Screens Button::Click(){
    return screen;
  }
  bool Button::ClickBool(){
    return true;
  }

