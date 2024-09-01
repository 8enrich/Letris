#include "../include/ButtonManager.hpp"
#include "../include/OptionsButton.hpp"
#include "../include/ScreenButton.hpp"
#include <iostream>
#include <raylib.h>

ButtonManager::ButtonManager(std::vector<Button*> buttons): buttons(buttons) {}

void ButtonManager::Tick(){
  for (Button *button : buttons) {
    button->Tick();
    MouseHandling(button);
  }
}

int ButtonManager::GetButtonIndex(Button *buttonTarget) {
  int index = 0;
  for (Button *button : buttons) {
    if (button == buttonTarget) break;
    index++;
  }
  return index;
}

void ButtonManager::MouseHandling(Button* button){
    if (!button->isMouseHoveringButton()){
      if(button->isSelected) button->Unselect();
      return;
  }
  currentSelectedButtonIndex = GetButtonIndex(button);
  button->Select();
  if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentScreen = buttons[currentSelectedButtonIndex]->Click();
  if(typeid(*button) == typeid(Button)){
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
      buttons[currentSelectedButtonIndex]->Click();
      return;
    }
    buttons[currentSelectedButtonIndex]->Unclick();
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

int ButtonManager::GetCurrentSelected(int currentSelected){
  for(int i = 0; i < 3; i++){
    Button *button = buttons[i];
    if(typeid(*button) == typeid(OptionsButton)){
      OptionsButton *optionsButton = static_cast<OptionsButton*>(button);
      if(optionsButton->GetIsClicked()) currentSelected = i;
      if(i == currentSelected){
        optionsButton->OpenMenu();
        continue;
      }
      optionsButton->CloseMenu();
    }
  }
  return currentSelected;
}

bool ButtonManager::HasButtonClicked(){
  for(Button *button : buttons){
    if(button->isButtonClicked()) return true;
  }
  return false;
}
