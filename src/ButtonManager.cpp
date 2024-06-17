#include "../include/ButtonManager.hpp"
#include "../include/OptionsButton.hpp"
#include <raylib.h>

ButtonManager::ButtonManager(std::vector<Button> buttons): buttons(buttons) {
  buttons[0].Select();
}
void ButtonManager::Tick(){
  InputHandler();
  for (Button button : buttons) button.Tick();
}

void ButtonManager::InputHandler(){
  auto keyPressed = GetKeyPressed();
  auto buttonPressed = buttons[currentSelectedButtonIndex];
  switch (keyPressed) {
    case KEY_ENTER:
      if (buttonPressed.type == ButtonTypes::SCREEN) currentScreen = buttonPressed.Click();
      break;
    case KEY_RIGHT:
      if (buttonPressed.type != ButtonTypes::OPTIONS) MoveSelection(1);
      else buttonPressed.Move(1);
      break;
    case KEY_LEFT:
      if (buttonPressed.type != ButtonTypes::OPTIONS) MoveSelection(-1);
      else buttonPressed.Move(-1);
      break;
    case KEY_UP:
      if (buttonPressed.type == ButtonTypes::OPTIONS) MoveSelection(-1);
      break;
    case KEY_DOWN:
      if (buttonPressed.type == ButtonTypes::OPTIONS) MoveSelection(1);
      break;
  }
}
void ButtonManager::MoveSelection(int num) {
    buttons[currentSelectedButtonIndex].Unselect();
    currentSelectedButtonIndex = (currentSelectedButtonIndex + num + buttons.size()) % buttons.size();
    buttons[currentSelectedButtonIndex].Select();
}
Screens ButtonManager::GetScreen() {
  return currentScreen;
}

