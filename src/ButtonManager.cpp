#include "../include/ButtonManager.hpp"
#include "../include/OptionsButton.hpp"
#include <raylib.h>

ButtonManager::ButtonManager(std::vector<Button*> buttons, bool isVertical): buttons(buttons), isVertical(isVertical) {
  this->buttons[0]->Select();
}
void ButtonManager::Tick(){
  if (isVertical) VerticalInputHandler();
  else InputHandler();
  for (Button *button : buttons) {
    button->Tick();
    MouseHandling(button);
  }
}

void ButtonManager::InputHandler(){
  auto keyPressed = GetKeyPressed();
  auto buttonPressed = buttons[currentSelectedButtonIndex];
  auto type = buttonPressed->type;
  switch (keyPressed) {
    case KEY_ENTER:
      if (type == ButtonTypes::SCREEN) currentScreen = buttonPressed->Click();
      break;
    case KEY_RIGHT:
      if (type != ButtonTypes::OPTIONS) MoveSelection(1);
     // else buttonPressed.Move(1);
      break;
    case KEY_LEFT:
      if (type != ButtonTypes::OPTIONS) MoveSelection(-1);
     // else buttonPressed.Move(-1);
      break;
    case KEY_UP:
      if (type == ButtonTypes::OPTIONS) MoveSelection(-1);
      break;
    case KEY_DOWN:
      if (type == ButtonTypes::OPTIONS) MoveSelection(1);
      break;
  }
}

void ButtonManager::VerticalInputHandler() {
  auto keyPressed = GetKeyPressed();
  auto buttonPressed = buttons[currentSelectedButtonIndex];
  auto type = buttonPressed->type;
  switch (keyPressed) {
    case KEY_ENTER:
      if (type == ButtonTypes::SCREEN) currentScreen = buttonPressed->Click();
      if (type == ButtonTypes::OPTIONS) buttonPressed->Click();
      break;
    case KEY_UP:
      MoveSelection(-1);
      break;
    case KEY_DOWN:
      MoveSelection(1);
      break;

  }
}
void ButtonManager::MoveSelection(int num) {
    buttons[currentSelectedButtonIndex]->Unselect();
    currentSelectedButtonIndex = (currentSelectedButtonIndex + num + buttons.size()) % buttons.size();
    buttons[currentSelectedButtonIndex]->Select();
}

int ButtonManager::GetButtonIndex(Button *button) {
  int index = 0;
  for (Button *button1 : buttons) {
    if (button1 == button) break;
    index++;
  }
  return index;
}
void ButtonManager::MouseHandling(Button* button){
  if (!button->isMouseHoveringButton()) return;
  buttons[currentSelectedButtonIndex]->Unselect();
  currentSelectedButtonIndex = GetButtonIndex(button);
  buttons[currentSelectedButtonIndex]->Select();
  if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    currentScreen = buttons[currentSelectedButtonIndex]->Click();
  }
}
Screens ButtonManager::GetScreen() {
  return currentScreen;
}

void ButtonManager::ResetScreen() {
  currentScreen = NOTSCREEN;
}
int ButtonManager::GetSelectedButtonIndex(){
  return currentSelectedButtonIndex;
}
std::vector<Button*> ButtonManager::GetButtons() {
  return buttons;
}
