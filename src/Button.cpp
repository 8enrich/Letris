#include "../include/Button.hpp"
#include "../include/raylibFunctions.hpp"
#include <raylib.h>

Button::Button(std::string buttonText, Vec2<double> buttonPosition, float fontSize, ButtonTypes type):
  Button(buttonText, buttonPosition, fontSize, type, ButtonStyles::TEXT)
{}

Button::Button(std::string buttonText, Vec2<double> buttonPosition, float fontSize, ButtonTypes type, Color color):
  Button(buttonText, buttonPosition, fontSize, type, ButtonStyles::RECT)
{
  this->color = color;
}

Button::Button(Vec2<double> buttonPosition, ButtonTypes type, std::string fileName):
  buttonPosition(buttonPosition), style(ButtonStyles::IMAGE), 
  image(new Texture2D(LoadTexture((std::string(ASSETS_PATH) + fileName).c_str()))),
  isSelected(false), isClicked(false), buttonWidthHeight({0, 0})
{}

Button::Button(std::string buttonText, Vec2<double> buttonPosition, float fontSize, ButtonTypes type, ButtonStyles style):
  buttonText(buttonText), buttonPosition(buttonPosition), fontSize(fontSize), type(type), style(style),
  isClicked(false), isSelected(false), rectangle{0}, buttonWidthHeight({0, 0}), realButtonPosition(0, 0)
{}

Button::~Button(){
  if(image){
    UnloadTexture(*image);
    delete image;
  }
}

void Button::UpdateRectNotSelected(){
    Vec2<double> pos = realButtonPosition - padding/2;
    Vec2<float> widthHeight = buttonWidthHeight + padding;
    rectangle = ray_functions::CreateRectangleVec(pos - hoveringPadding/2, widthHeight + hoveringPadding);
}

void Button::UpdateRectSelected(){
  rectangle = ray_functions::CreateRectangleVec(Vec2{realButtonPosition - padding/2}, Vec2{buttonWidthHeight + padding});
}

void Button::DrawRectButton() {
  !isSelected?UpdateRectSelected():UpdateRectNotSelected();
  DrawRectangleRounded(rectangle, 0.3, 0, color);
}

void Button::DrawTextButton(){
  ray_functions::DrawFormatedText(buttonText.c_str(), buttonPosition, fontSize, textColor);
}

void Button::DrawImageButton(){
  Rectangle src = (Rectangle){0, 0, (float)image->width, (float)image->height};
  Rectangle dest = (Rectangle){(float)realButtonPosition.GetX(), (float)realButtonPosition.GetY(), 
    (float)buttonWidthHeight.GetX(), (float)buttonWidthHeight.GetY()};
  DrawTexturePro(*image, src, dest, Vector2{0, 0},0, RAYWHITE);
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
  realButtonPosition = Vec2<double>{buttonPosition.GetX() * GetScreenWidth(), buttonPosition.GetY() * GetScreenHeight()};
  buttonWidthHeight = Vec2<float>{GetScreenWidth()/25.0f, GetScreenWidth()/25.0f};
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
