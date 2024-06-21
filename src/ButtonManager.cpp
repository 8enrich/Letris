#include "../include/ButtonManager.hpp"
#include "../include/OptionsButton.hpp"
#include <raylib.h>

ButtonManager::ButtonManager(std::vector<Button> buttons, bool isVertical): buttons(buttons), isVertical(isVertical) {
  this->buttons[0].Select();
}
void ButtonManager::Tick(){
  if (isVertical) VerticalInputHandler();
  else InputHandler();
  for (Button button : buttons) {
    button.Tick();
    MouseHandling(button);
  }
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
     // else buttonPressed.Move(1);
      break;
    case KEY_LEFT:
      if (buttonPressed.type != ButtonTypes::OPTIONS) MoveSelection(-1);
     // else buttonPressed.Move(-1);
      break;
    case KEY_UP:
      if (buttonPressed.type == ButtonTypes::OPTIONS) MoveSelection(-1);
      break;
    case KEY_DOWN:
      if (buttonPressed.type == ButtonTypes::OPTIONS) MoveSelection(1);
      break;
  }
}

void ButtonManager::VerticalInputHandler() {
  auto keyPressed = GetKeyPressed();
  auto buttonPressed = buttons[currentSelectedButtonIndex];
  switch (keyPressed) {
    case KEY_ENTER:
      if (buttonPressed.type == ButtonTypes::SCREEN) currentScreen = buttonPressed.Click();
      break;
    case KEY_UP:
      if (buttonPressed.type != ButtonTypes::OPTIONS) MoveSelection(-1);
      break;
    case KEY_DOWN:
      if (buttonPressed.type != ButtonTypes::OPTIONS) MoveSelection(1);
      break;

  }
}
void ButtonManager::MoveSelection(int num) {
    buttons[currentSelectedButtonIndex].Unselect();
    currentSelectedButtonIndex = (currentSelectedButtonIndex + num + buttons.size()) % buttons.size();
    buttons[currentSelectedButtonIndex].Select();
}

int ButtonManager::GetButtonIndex(Button button) {
  int index = 0;
  for (Button button1 : buttons) {
    if (button1.GetButtonPosition() == button.GetButtonPosition()) break;
    index++;
  }
  return index;
}
void ButtonManager::MouseHandling(Button button){
  if (!button.isMouseHoveringButton()) return;
  buttons[currentSelectedButtonIndex].Unselect();
  currentSelectedButtonIndex = GetButtonIndex(button);
  buttons[currentSelectedButtonIndex].Select();
  if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    currentScreen = buttons[currentSelectedButtonIndex].Click();
  }
}
Screens ButtonManager::GetScreen() {
  return currentScreen;
}

void ButtonManager::ResetScreen() {
  currentScreen = NOTSCREEN;
}
