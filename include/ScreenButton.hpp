#include "Button.hpp"
#include "Settings.hpp"

class ScreenButton : Button {
public:
  ScreenButton(std::string buttonText, float fontSize, Vec2<double> buttonPosition, Screens screen);
};
