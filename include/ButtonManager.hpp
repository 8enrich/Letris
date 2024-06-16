#include "Button.hpp"
#include "Settings.hpp"
#include <vector>
class ButtonManager{
public:
  ButtonManager(std::vector<Button> buttons);
  void Tick();
private:
  void ButtonTypeHandler();
  void ButtonSelector();
  void InputHandler();
  Screens GetScreen();
  int currentSelectedButtonIndex = 0;
  Screens currentScreen = NOTSCREEN;
  std::vector<Button> buttons;
};
