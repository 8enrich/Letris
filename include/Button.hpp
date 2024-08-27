#include <raylib.h>
#include "Settings.hpp"
#include "Vec2.hpp"
#include <string>
#pragma once
enum class ButtonTypes {
  SCREEN,
  OPTIONS,
};

class Button {
public:
  Button(std::string buttonText, Vec2<double> buttonPosition, float fontSize, ButtonTypes type);
  Button(std::string buttonText, Vec2<double> buttonPosition, float fontSize);
  void Draw();
  virtual void Tick();
  void Select();
  void Unselect();
  Screens Click();
  ButtonTypes type;
  bool isMouseHoveringButton();
  bool isMouseHoveringVec(Vec2<double>, Vec2<double>);
  Vec2<double> GetButtonPosition();
  std::string GetText();
  void Unclick();
  double GetMousePositionX();
  bool isButtonClicked();
  void SetButtonText(std::string);
protected:
  virtual void Update();
  bool isButtonClickedByMouse();
  bool hasBorder;
  bool isSelected;
  bool isClicked;
  Screens screen = NOTSCREEN;
  Color selectedColor = RAYWHITE;
  Color unselectedColor = GRAY;
  std::string buttonText;
  float fontSize;
  Vec2<float> buttonWidthHeight;
  Vec2<double> buttonPosition;
  Vec2<double> realButtonPosition;
};
