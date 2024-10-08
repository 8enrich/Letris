#include "../include/Button.hpp"
#include "../include/raylibFunctions.hpp"
#include <raylib.h>
#include <string>

Button::Button(std::string buttonText, Vec2<double> buttonPosition, float fontSize, ButtonTypes type):
  Button(buttonText, buttonPosition, fontSize, type, ButtonStyles::TEXT)
{}

Button::Button(std::string buttonText, Vec2<double> buttonPosition, float fontSize, ButtonTypes type, Color color):
  Button(buttonText, buttonPosition, fontSize, type, ButtonStyles::RECT)
{
  this->color = color;
}

Button::Button(Vec2<double> buttonPosition, ButtonTypes type, Texture2D *image, Vec2<double> size):
  buttonPosition(buttonPosition), style(ButtonStyles::IMAGE), 
  image(image),
  isSelected(false), isClicked(false), buttonWidthHeight({0, 0}), realButtonPosition({0, 0}),
  hoveringSound(settings::hoveringSound), size(size)
{}

Button::Button(std::string buttonText, Vec2<double> buttonPosition, float fontSize, ButtonTypes type, ButtonStyles style):
  buttonText(buttonText), buttonPosition(buttonPosition), fontSize(fontSize), type(type), style(style),
  isClicked(false), isSelected(false), buttonWidthHeight({0, 0}), realButtonPosition(0, 0),
  hoveringSound(settings::hoveringSound)
{}

Button::~Button(){
  if(image){
    UnloadTexture(*image);
    delete image;
  }
}

void Button::DrawRectButton() {
  Vec2<float> pos = Vec2<float>(realButtonPosition) - padding/2.0f;
  Vec2<float> size = buttonWidthHeight + padding;
  if(isSelected){
    size += hoveringPadding;
    pos -= hoveringPadding/2.0f;
  }
  Rectangle rect = {pos.GetX(), pos.GetY(), size.GetX(), size.GetY()};
  DrawRectangleRounded(rect, 0.3, 2, color);
}

void Button::DrawTextButton(){
  ray_functions::DrawFormatedText(buttonText.c_str(), buttonPosition, fontSize, textColor);
}

void Button::DrawImageButton(){
  if(isSelected){
    ray_functions::DrawResizedImage(image, realButtonPosition - hoveringPadding/2.0f, buttonWidthHeight + hoveringPadding);
    return;
  }
  ray_functions::DrawResizedImage(image, realButtonPosition, buttonWidthHeight);
}

void Button::Draw(){
  switch(style){
    case ButtonStyles::RECT:
      DrawRectButton();
      DrawTextButton();
      break;
    case ButtonStyles::TEXT:
      textColor = isSelected ? selectedColor : unselectedColor;
      DrawTextButton();
      break;
    case ButtonStyles::IMAGE:
      DrawImageButton();
      break;
    default:
      break;
  }
}

void Button::Tick(){
  Update();
  Draw();
}

void Button::Update() {
  if(style != ButtonStyles::IMAGE){
    realButtonPosition = ray_functions::FakePositionToRealPosition(buttonPosition, buttonText, fontSize);
    buttonWidthHeight = Vec2<float>{(float)MeasureText(buttonText.c_str(), fontSize*settings::screenHeight), (float)fontSize * settings::screenHeight}; 
    return;
  }
  realButtonPosition = ray_functions::FakePositionToRealPosition(buttonPosition);
  buttonWidthHeight = Vec2<float>{GetScreenWidth()/(float)size.GetX(), GetScreenWidth()/(float)size.GetY()};
}

std::string Button::GetText() {
  return buttonText;
}
void Button::Select(){
  isSelected = true;
  SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
  PlaySound(hoveringSound);
}

void Button::Unselect(){
  isSelected = false;
  SetMouseCursor(MOUSE_CURSOR_DEFAULT);
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

void Button::SetImage(Texture2D *image){
  this->image = image;
}

void Button::SetColor(Color color){
  this->color = color;
}

void Button::SetButtonPosition(Vec2<double> buttonPosition){
  this->buttonPosition = buttonPosition;
}
