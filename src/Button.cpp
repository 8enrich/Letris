#include "../include/Button.hpp"
#include "../include/raylibFunctions.hpp"
#include <raylib.h>
  Button::Button(std::string buttonText, float fontSize, Vec2<double> buttonPosition):
    buttonText(buttonText), fontSize(fontSize), buttonPosition(buttonPosition)
  {
    buttonWidthHeight= Vec2<float>{(float) buttonText.size() * fontSize, (float) fontSize}; 
  }
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
    isClicked = true;
    return screen;
  }
  bool Button::isButtonClicked(){
    return isClicked;
  }
  bool Button::isButtonClickedByMouse(){}

