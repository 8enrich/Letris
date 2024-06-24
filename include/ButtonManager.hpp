#pragma once
#include "Button.hpp"
#include "Settings.hpp"
#include <vector>
class ButtonManager{
public:
  ButtonManager(std::vector<Button*> buttons, bool isVertical);
  void Tick();
  Screens GetScreen();
  void ResetScreen();
  int GetSelectedButtonIndex();
  std::vector<Button*> GetButtons();
private:
  int GetButtonIndex(Button *button);
  bool isVertical;
  void ButtonTypeHandler();
  void ButtonSelector();
  void MouseHandling(Button *button);
  void VerticalInputHandler();
  void InputHandler();
  void MoveSelection(int num);
  int currentSelectedButtonIndex = 0;
  Screens currentScreen = NOTSCREEN;
  std::vector<Button*> buttons;
};
