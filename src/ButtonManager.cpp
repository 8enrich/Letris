#include "../include/ButtonManager.hpp"
#include <raylib.h>

ButtonManager::ButtonManager(std::vector<Button> buttons): buttons(buttons) {
  buttons[0].Select();
}
void ButtonManager::Tick(){
  ButtonTypeHandler(); 
  for (Button button : buttons) button.Tick();
}

void ButtonManager::InputHandler(){
  auto keyPressed = GetKeyPressed();
  auto buttonPressed = buttons[currentSelectedButtonIndex];
  switch (keyPressed) {
    case KEY_ENTER:
      if (buttonPressed.type != ButtonTypes::OPTIONS) currentScreen = buttonPressed.Click();
      break;
    case KEY_RIGHT:
      if (buttonPressed.type != ButtonTypes::OPTIONS) currentSelectedButtonIndex = currentSelectedButtonIndex == (buttons.size() -1)? 0 : currentSelectedButtonIndex + 1;
      else {} // Mudar a opção do botão de tipo options
      break;
    case KEY_LEFT:
      if (buttonPressed.type != ButtonTypes::OPTIONS) currentSelectedButtonIndex = currentSelectedButtonIndex == 0? buttons.size()-1 : currentSelectedButtonIndex - 1;
      else {} // Mudar a opção do botão de tipo options
      break;
    case KEY_UP:
      if (buttonPressed.type == ButtonTypes::OPTIONS) currentSelectedButtonIndex = currentSelectedButtonIndex == 0? buttons.size()-1 : currentSelectedButtonIndex - 1;
      break;
    case KEY_DOWN:
      if (buttonPressed.type == ButtonTypes::OPTIONS) currentSelectedButtonIndex = currentSelectedButtonIndex == (buttons.size() -1)? 0 : currentSelectedButtonIndex + 1;
      break;
  }
}
void ButtonManager::ButtonTypeHandler() {
  for (Button button : buttons) {
    auto buttonType = button.type;
    switch (buttonType) {
      case ButtonTypes::APPLY:
      case ButtonTypes::SCREEN:
        ButtonSelector();
        break;
      case ButtonTypes::OPTIONS:
        break;
    }
  } 
}

void ButtonManager::ButtonSelector() {

}

