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

enum class ButtonStyles{
  RECT,
  TEXT,
  IMAGE
};

class Button {
public:
  Button(std::string buttonText, Vec2<double> buttonPosition, float fontSize, ButtonTypes type);
  Button(std::string buttonText, Vec2<double> buttonPosition, float fontSize, ButtonTypes type, Color color);
  Button(Vec2<double> buttonPosition, ButtonTypes type, std::string fileName);
  Button(std::string buttonText, Vec2<double> buttonPosition, float fontSize, ButtonTypes type, ButtonStyles style);
  ~Button();
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
  void DrawTextButton();
  void DrawImageButton();
  void UpdateRectNotSelected();
  void UpdateRectSelected();
  Texture2D *image = nullptr;
  virtual void Update();
  bool isButtonClickedByMouse();
  bool isSelected, isClicked;
  int hoveringPadding = 12, padding = 20;
  Rectangle rectangle;
  Screens screen = NOTSCREEN;
  const Color selectedColor = RAYWHITE, unselectedColor = GRAY;
  Color color, textColor = selectedColor;
  std::string buttonText;
  float fontSize;
  Vec2<float> buttonWidthHeight;
  Vec2<double> buttonPosition, realButtonPosition;
  ButtonStyles style;
};
