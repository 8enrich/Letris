#include <raylib.h>
#include "Settings.hpp"
#include "Vec2.hpp"
#include <string>
#pragma once
enum class ButtonTypes {
  SCREEN,
  OPTIONS,
  VOLUME,
  KEYBUTTON,
  NULLBUTTON
};

class Button {
public:
  Button(std::string buttonText, Vec2<double> buttonPosition, float fontSize, ButtonTypes type);
  Button(std::string buttonText, Vec2<double> buttonPosition, float fontSize, ButtonTypes type, Color color);
  Button(std::string buttonText, Vec2<double> buttonPosition, float fontSize, ButtonTypes type, bool isRectangle);
  void Draw();
  virtual void Tick();
  void Select();
  void Unselect();
  Screens Click();
  bool isMouseHoveringButton();
  bool isMouseHoveringVec(Vec2<double>, Vec2<double>);
  Vec2<double> GetButtonPosition();
  std::string GetText();
  void Unclick();
  double GetMousePositionX();
  bool isButtonClicked();
  void SetButtonText(std::string);
  ButtonTypes type;
protected:
  void DrawRectButton();
  void UpdateRectNotSelected();
  void UpdateRectSelected();
  virtual void Update();
  bool isButtonClickedByMouse();
  bool isRectButton, isSelected, isClicked;
  int hoveringPadding = 12, padding = 20;
  Rectangle rectangle;
  Screens screen = NOTSCREEN;
  const Color selectedColor = RAYWHITE, unselectedColor = GRAY;
  Color color, textColor = selectedColor;
  std::string buttonText;
  const float fontSize;
  Vec2<float> buttonWidthHeight;
  Vec2<double> buttonPosition, realButtonPosition;
};
