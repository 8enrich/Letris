#include "../include/Button.hpp"
#include "../include/raylibFunctions.hpp"
#include <raylib.h>

Button::Button(std::string buttonText, Vec2<double> buttonPosition, float fontSize, ButtonTypes type):
  buttonText(buttonText), buttonPosition(buttonPosition), fontSize(fontSize), type(type)
{
  isSelected = false;
}

void Button::Draw(){
  Color color = isSelected ? selectedColor : unselectedColor;
  ray_functions::DrawFormatedText(buttonText.c_str(), buttonPosition, fontSize, color);
}

void Button::Tick(){
  Update();
  Draw();
}

void Button::Update() {
  realButtonPosition = ray_functions::FakePositionToRealPosition(buttonPosition, buttonText, fontSize);
  buttonWidthHeight = Vec2<float>{(float)MeasureText(buttonText.c_str(), fontSize*settings::screenHeight), (float)fontSize * settings::screenHeight}; 
}

std::string Button::GetText() {
  return buttonText;
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

bool Button::isMouseHoveringButton(){
  float mouseX = (float) GetMouseX(), mouseY = (float) GetMouseY();
  return mouseX >= realButtonPosition.GetX() && mouseX <= realButtonPosition.GetX() + buttonWidthHeight.GetX() &&
         mouseY >= realButtonPosition.GetY() && mouseY <= realButtonPosition.GetY() + buttonWidthHeight.GetY();
}

Vec2<double> Button::GetButtonPosition() {
  return buttonPosition;
}

