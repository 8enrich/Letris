#include "../include/ScreenButton.hpp"
#include <string>

ScreenButton::ScreenButton(std::string buttonText,  Vec2<double> buttonPosition,float fontSize, Screens screen): 
  Button(buttonText, buttonPosition, fontSize, ButtonTypes::SCREEN)
{
  this->screen = screen;
}
ScreenButton::ScreenButton(std::string buttonText, Vec2<double> buttonPosition, float fontSize, Screens screen, Color color):
  Button(buttonText, buttonPosition, fontSize, ButtonTypes::SCREEN, color)
{
  this->screen = screen;  
}
void ScreenButton::SetScreen(Screens newScreen){
  screen = newScreen;
}
