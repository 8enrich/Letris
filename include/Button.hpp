#include <raylib.h>
#include "Settings.hpp"
#include "Vec2.hpp"
#include <string>

enum class ButtonTypes {
  SCREEN,
  OPTIONS,
  APPLY
};

class Button {
public:
  Button(std::string buttonText, float fontSize, Vec2<double> buttonPosition);
  void Draw();
  void Tick();
  void Select();
  void Unselect();
  Screens Click();
  ButtonTypes type;
protected:
  bool isMouseHovering();
  bool isButtonClicked();
  bool isButtonClickedByMouse();
  bool hasBorder;
  bool isSelected;
  bool isClicked;
  Screens screen;
  Color selectedColor = RAYWHITE;
  Color unselectedColor = GRAY;
  std::string buttonText;
  float fontSize;
  Vec2<float> buttonWidthHeight;
  Vec2<double> buttonPosition;
};