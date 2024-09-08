#pragma once
#include "Button.hpp"
#include "Settings.hpp"

class ScreenButton : public Button {
public:
  ScreenButton(std::string buttonText, Vec2<double> buttonPosition, float fontSize,Screens screen);
  ScreenButton(std::string buttonText, Vec2<double> buttonPosition, float fontSize,Screens screen, Color color);
  ScreenButton(Vec2<double> buttonPosition, Screens screen, Texture2D *image, Vec2<double> size);
  void SetScreen(Screens);
};
