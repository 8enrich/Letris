#include "../include/Button.hpp"
#include "../include/raylibFunctions.hpp"
#include <raylib.h>
  Button::Button(std::string buttonText, float fontSize, Vec2<double> buttonPosition, ButtonTypes type):
    buttonText(buttonText), fontSize(fontSize), buttonPosition(buttonPosition), type(type)
  {
    isSelected = false;
    buttonWidthHeight= Vec2<float>{(float) buttonText.size() * fontSize, (float) fontSize}; 
  }
  void Button::Draw(){
    Color color = isSelected ? selectedColor: unselectedColor;
    ray_functions::DrawFormatedText(buttonText.c_str(), buttonPosition, fontSize, color);
  }
  void Button::Tick(){
    Draw();
  }
  void Button::Select(){
    isSelected = true;
  }
  void Button::Unselect(){
    isSelected = false;
  }
  Screens Button::Click(){
    isClicked = true;
    return screen;
  }
  bool Button::isButtonClicked(){
    return isClicked;
  }

