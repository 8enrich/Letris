#include "Button.hpp"
#include <vector>
class ButtonManager{
public:
  ButtonManager(std::vector<Button> buttons);
  void Tick();
private:
  int currentSelectedButtonIndex;
  std::vector<Button> buttons;
};
