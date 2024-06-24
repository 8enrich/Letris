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
    for (int i =0; i < options.size(); i++) {
      buttons.push_back(new ScreenButton(options[i], {buttonPosition.GetX(), buttonPosition.GetY()*(float)(i+3)/2}, fontSize, Screens::STRING));
    }
    buttonOptions = new ButtonManager(buttons, true);

  }
void OptionsButton::Move(int n) {}

void OptionsButton::DrawMenu() {
  int width = settings::screenWidth, height = settings::screenHeight;
  Vec2<double> realPos = buttonPosition * Vec2<double>{(float)width, (float)height};
  DrawRectangle(realPos.GetX() - width/8, realPos.GetY(), width/4, height/2.5, BLUE);
}
void OptionsButton::Update(){
  buttonText = options[currentSelectedOptionIndex]; 
}

void OptionsButton::MenuHandling(){
  BeginDrawing();
  DrawMenu();
  buttonOptions->Tick();
  EndDrawing();
  if(buttonOptions->GetScreen() == Screens::STRING) {
    currentSelectedOptionIndex = buttonOptions->GetSelectedButtonIndex();
    buttonOptions->ResetScreen();
    std::cout << options[currentSelectedOptionIndex] << std::endl;
    isClicked = false;
    isMenuOpen = false;
  }
}
void OptionsButton::OpenMenu(){
  isMenuOpen = true;
}
void OptionsButton::Tick(){
  Update();
  Draw();
  if(isClicked) OpenMenu();
  while(isMenuOpen) MenuHandling();
}
int OptionsButton::GetSelectedItemIndex(){
  return currentSelectedOptionIndex;
}
