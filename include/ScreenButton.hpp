#pragma once
#include "Button.hpp"
#include "Settings.hpp"

class ScreenButton : public Button {
public:
  ScreenButton(std::string buttonText, Vec2<double> buttonPosition, float fontSize,Screens screen);
  void SetScreen(Screens);
};
