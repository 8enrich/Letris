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
  Button(Vec2<double> buttonPosition, ButtonTypes type, std::string fileName, Vec2<double> size);
  Button(std::string buttonText, Vec2<double> buttonPosition, float fontSize, ButtonTypes type, ButtonStyles style);
  ~Button();
  void Draw();
  virtual void Tick();
  bool isSelected;
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
  void SetImage(Texture2D *image);
  void SetColor(Color color);
  void SetButtonPosition(Vec2<double> buttonPosition);
protected:
  void DrawRectButton();
  void DrawTextButton();
  void DrawImageButton();
  Texture2D *image = nullptr;
  virtual void Update();
  bool isButtonClickedByMouse();
  Sound hoveringSound;
  bool isClicked;
  int hoveringPadding = 20, padding = 27;
  Screens screen = NOTSCREEN;
  const Color selectedColor = RAYWHITE, unselectedColor = GRAY;
  Color color, textColor = selectedColor;
  std::string buttonText;
  float fontSize;
  Vec2<float> buttonWidthHeight;
  Vec2<double> buttonPosition, realButtonPosition, size;
  ButtonStyles style;
};
