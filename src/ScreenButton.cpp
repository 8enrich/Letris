#include "../include/ScreenButton.hpp"

ScreenButton::ScreenButton(std::string buttonText,  Vec2<double> buttonPosition,float fontSize, Screens screen): 
  Button(buttonText, fontSize, buttonPosition, ButtonTypes::SCREEN)
{
  this->screen = screen;
}

