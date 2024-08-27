#include "../include/Button.hpp"
#include "../include/raylibFunctions.hpp"
#include <raylib.h>

Button::Button(std::string buttonText, Vec2<double> buttonPosition, float fontSize, ButtonTypes type):
  Button(buttonText, buttonPosition, fontSize, type, Color{0,0,0,0})
{
  isSelected = false;
}

Button::Button(std::string buttonText, Vec2<double> buttonPosition, float fontSize, ButtonTypes type, Color color):
  buttonText(buttonText), buttonPosition(buttonPosition), fontSize(fontSize), type(type), color(color)
{
  isSelected = false;
}

void Button::Draw(){
  Rectangle rectangle;
  int padding = 20;
  rectangle.width = buttonWidthHeight.GetX() + padding;
  rectangle.height = buttonWidthHeight.GetY() + padding;
  rectangle.x = realButtonPosition.GetX() - padding/2;
  rectangle.y = realButtonPosition.GetY() - padding/2;
  if (isSelected) {
    int hoveringPadding = 12;
    rectangle.width += hoveringPadding;
    rectangle.height += hoveringPadding;
    rectangle.x -=hoveringPadding/2;
    rectangle.y -=hoveringPadding/2;
  }
  DrawRectangleRounded(rectangle, 0.3, 0, RED);
  ray_functions::DrawFormatedText(buttonText.c_str(), buttonPosition, fontSize, RAYWHITE);
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
bool Button::isMouseHoveringVec(Vec2<double> pos, Vec2<double> widthHeight){
  float mouseX = (float) GetMouseX(), mouseY = (float) GetMouseY();
  return mouseX >= pos.GetX() && mouseX <= pos.GetX() + widthHeight.GetX() &&
         mouseY >= pos.GetY() && mouseY <= pos.GetY() + widthHeight.GetY();
}
Vec2<double> Button::GetButtonPosition() {
  return buttonPosition;
}

void Button::Unclick(){
  isClicked = false;
}

double Button::GetMousePositionX(){
  if(isMouseHoveringButton() && isButtonClicked()) return GetMouseX();
  return 0;
}

void Button::SetButtonText(std::string buttonText){
  this->buttonText = buttonText;
}
