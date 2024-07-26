#pragma once
#include "Button.hpp"
#include "Settings.hpp"
#include <vector>
class ButtonManager{
public:
  ButtonManager(std::vector<Button*> buttons);
  void Tick();
  Screens GetScreen();
  void ResetScreen();
  int GetSelectedButtonIndex();
  std::vector<Button*> GetButtons();
  int GetCurrentSelected(int);
  bool HasButtonClicked();
private:
  int currentSelectedButtonIndex = 0;
  int GetButtonIndex(Button *button);
  void MouseHandling(Button *button);
  Screens currentScreen = NOTSCREEN;
  std::vector<Button*> buttons;
};
