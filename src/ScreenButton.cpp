#include "../include/ScreenButton.hpp"

ScreenButton::ScreenButton(std::string buttonText, float fontSize, Vec2<double> buttonPosition, Screens screen): 
  Button(buttonText, fontSize, buttonPosition, ButtonTypes::SCREEN)
{
  this->screen = screen;
} 
