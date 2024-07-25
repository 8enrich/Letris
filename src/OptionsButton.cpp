#include "../include/OptionsButton.hpp"
#include "../include/ScreenButton.hpp"
#include "../include/raylibFunctions.hpp"
#include "../include/Settings.hpp"
#include <iostream>
#include <ostream>
#include <raylib.h>
#include <vector>

OptionsButton::OptionsButton(std::string buttonText, Vec2<double> buttonPosition, float fontSize, std::vector<std::string> options, std::string optionInSettings) : 
  Button(buttonText, buttonPosition, fontSize, ButtonTypes::OPTIONS){
    this->options = options;
    this->optionInSettings = optionInSettings;
    std::vector<Button*> buttons;
    realButtonPosition = ray_functions::FakePositionToRealPosition(buttonPosition, buttonText, fontSize);
    buttonWidthHeight = Vec2<float>{(float)MeasureText(buttonText.c_str(), fontSize*settings::screenHeight), (float)fontSize * settings::screenHeight}; 
    for (int i = 0, size = options.size(); i < size; i++) {
      if (options[i] == optionInSettings) currentSelectedOptionIndex = i;
          buttons.push_back(new ScreenButton(options[i], {buttonPosition.GetX(), buttonPosition.GetY() + (i+1) * 1.0f/15},
                fontSize, Screens::STRING));
    }
    buttonOptions = new ButtonManager(buttons, true);
  }

OptionsButton::OptionsButton(std::string buttonText, Vec2<double> buttonPosition, float fontSize, std::vector<Button*> buttons) :
  Button(buttonText, buttonPosition, fontSize, ButtonTypes::OPTIONS){
    buttonOptions = new ButtonManager(buttons, true);
    this->options = {};
  }

void OptionsButton::Move(int n) {}

void OptionsButton::DrawMenu() {
  ray_functions::DrawFormatedRectangle(buttonPosition, GetMenuWidthHeight(), LIGHTGRAY);
}
void OptionsButton::Update(){
  if(options.size() > 0) buttonText = options[currentSelectedOptionIndex];
  realButtonPosition = ray_functions::FakePositionToRealPosition(buttonPosition, buttonText, fontSize);
  buttonWidthHeight = Vec2<float>{(float)MeasureText(buttonText.c_str(), fontSize*settings::screenHeight), (float)fontSize * settings::screenHeight}; 
}

void OptionsButton::MenuHandling(){
  DrawMenu();
  buttonOptions->Tick();
  if(options.size() > 0){
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !isMouseHoveringVec(buttonPosition, GetMenuWidthHeight())) CloseMenu();
    if(buttonOptions->GetScreen() == Screens::STRING) {
      currentSelectedOptionIndex = buttonOptions->GetSelectedButtonIndex();
      buttonOptions->ResetScreen();
      isClicked = false;
      isMenuOpen = false;
    }
  }
}
void OptionsButton::OpenMenu(){
  isMenuOpen = true;
}
void OptionsButton::CloseMenu(){
  isClicked=false;
  isMenuOpen = false;
}
void OptionsButton::Tick(){
  Update();
  if(isClicked) OpenMenu();
  isClicked = false;
  if(isMenuOpen) MenuHandling();
  Color selectedColor = (isMenuOpen)? BLACK : DARKGRAY;
  Color color = (options.size() > 0)? DARKGRAY : selectedColor;
  ray_functions::DrawFormatedRectangle(buttonPosition, Vec2<double>{(GetLargestOptionText() + 10)/(float)settings::screenWidth,
      1.0f/20}, color);
  Draw();
}
int OptionsButton::GetSelectedItemIndex(){
  return currentSelectedOptionIndex;
}
std::string OptionsButton::GetButtonText(){
  return buttonText;
}

bool OptionsButton::GetIsClicked(){
  return isClicked;
}

int OptionsButton::GetLargestOptionText(){
  int largest = MeasureText(buttonText.c_str(), fontSize*settings::screenHeight), value;
  for(int i = 0, size = options.size(); i < size; i++){
    value = MeasureText(options[i].c_str(), fontSize*settings::screenHeight);
    if(largest < value) largest = value;
  }
  return largest;
}

Vec2<double> OptionsButton::GetMenuWidthHeight(){
  return Vec2<double>{(GetLargestOptionText() + 10)/(float)settings::screenWidth, 1.0f * options.size()/12};
}
