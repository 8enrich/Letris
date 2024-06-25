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
    for (int i =0; i < options.size(); i++) {
      if (options[i] == optionInSettings) currentSelectedOptionIndex = i; 
          buttons.push_back(new ScreenButton(options[i], {buttonPosition.GetX(), buttonPosition.GetY()*(i+3)/2}, fontSize, Screens::STRING));
    }
    buttonOptions = new ButtonManager(buttons, true);

  }
void OptionsButton::Move(int n) {}

void OptionsButton::DrawMenu() {
  DrawRectangle(realButtonPosition.GetX(), realButtonPosition.GetY() + settings::screenHeight/16, buttonWidthHeight.GetX()+2, buttonWidthHeight.GetY() * options.size() * 4, LIGHTGRAY);
}
void OptionsButton::Update(){
  buttonText = options[currentSelectedOptionIndex]; 
  realButtonPosition = ray_functions::FakePositionToRealPosition(buttonPosition, buttonText, fontSize);
  buttonWidthHeight = Vec2<float>{(float)MeasureText(buttonText.c_str(), fontSize*settings::screenHeight), (float)fontSize * settings::screenHeight}; 
}

void OptionsButton::MenuHandling(){
  BeginDrawing();
  DrawMenu();
  buttonOptions->Tick();
  EndDrawing();
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
      !isMouseHoveringVec({realButtonPosition.GetX(), realButtonPosition.GetY()+ settings::screenHeight/16},
      {buttonWidthHeight.GetX()+2, buttonWidthHeight.GetY() * options.size() * 4})) CloseMenu();

  if(buttonOptions->GetScreen() == Screens::STRING) {
    currentSelectedOptionIndex = buttonOptions->GetSelectedButtonIndex();
    buttonOptions->ResetScreen();
    isClicked = false;
    isMenuOpen = false;
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
  DrawRectangle(realButtonPosition.GetX(), realButtonPosition.GetY(), buttonWidthHeight.GetX()+2, buttonWidthHeight.GetY()+2, DARKGRAY);
  Draw();
  if(isClicked) OpenMenu();
  while(isMenuOpen) MenuHandling();
}
int OptionsButton::GetSelectedItemIndex(){
  return currentSelectedOptionIndex;
}
std::string OptionsButton::GetButtonText(){
  return buttonText;
}
