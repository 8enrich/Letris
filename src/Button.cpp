#include "../include/Button.hpp"
#include "../include/raylibFunctions.hpp"
#include <raylib.h>
#include <iostream>

Button::Button(std::string buttonText, float fontSize, Vec2<double> buttonPosition, ButtonTypes type):
  buttonText(buttonText), fontSize(fontSize), buttonPosition(buttonPosition), type(type)
{
  isSelected = false;
  realButtonPosition ={settings::screenWidth * buttonPosition.GetX() - MeasureText(buttonText.c_str(), settings::screenHeight * fontSize)/2, settings::screenHeight * buttonPosition.GetY()}; 
  buttonWidthHeight = Vec2<float>{(float)MeasureText(buttonText.c_str(), fontSize*settings::screenHeight), (float)fontSize * settings::screenHeight}; 
}

void Button::Draw(){
  Color color = isSelected ? selectedColor : unselectedColor;
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

bool Button::isMouseHoveringButton(){
  float mouseX = (float) GetMouseX(), mouseY = (float) GetMouseY(); 
  return mouseX >= realButtonPosition.GetX() && mouseX <= realButtonPosition.GetX() + buttonWidthHeight.GetX() &&
         mouseY >= realButtonPosition.GetY() && mouseY <= realButtonPosition.GetY() + buttonWidthHeight.GetY();
}

Vec2<double> Button::GetButtonPosition() {
  return buttonPosition;
}

