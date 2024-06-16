#include <raylib.h>
#include "Settings.hpp"
#include "Vec2.hpp"
#include <string>

class Button {
public:
  Button(std::string buttonText, float fontSize, Vec2<double> buttonPosition, Screens screen, bool isSelected=false);
  Button(std::string buttonText, float fontSize, Vec2<double> buttonPosition);
  void Draw();
  void Tick();
  void Select();
  void Unselect();
  Screens Click();
  bool ClickBool();

private:
  bool isMouseHovering();
  bool isButtonClicked();
  bool hasBorder;
  bool isSelected;
  Screens screen;
  Color selectedColor = RAYWHITE;
  Color unselectedColor = GRAY;
  std::string buttonText;
  float fontSize;
  Vec2<float> buttonWidthHeight;
  Vec2<double> buttonPosition;
};
