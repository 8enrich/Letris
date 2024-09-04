#include "../include/CoopOptions.hpp"
#include "../include/AllocError.hpp"
#include "raylib.h"
#include <string>

using namespace settings;
using namespace std;

CoopOptions::CoopOptions(){

  for(int i = 0; i < 2; i++){
    for (const auto& pair : controlsIndexes) {
      if (pair.second == db[playersControls[i]]){
        selectedControls[i] = pair.first;
        break;
      }
    }
    controlButtons[i] = new OptionsButton(selectedControls[i], Vec2<double>{0.15 + i * 0.70, 1/1.5}, fontSize, controlOptions[i]);
    if(!controlButtons[i]) throw AllocError("CoopOptions", "controlButtons[" + to_string(i) + "]");
    buttons.push_back(&(readyButtons[i]));
    buttons.push_back(controlButtons[i]);
  }
  buttons.push_back(&backgroundSelector);
  buttonManager = new ButtonManager(buttons);
  if(!buttonManager) throw AllocError("CoopOptions", "buttonManager");
}

CoopOptions::~CoopOptions(){
  for(int i = 0; i < 2; i++) delete controlButtons[i];
  delete buttonManager;
}

void CoopOptions::Tick(){
  CoopOptionsHandling();
  BeginDrawing();
  Draw();
  buttonManager->Tick();
  EndDrawing();
  if(GetKeyPressed() == KEY_ESCAPE) Close(MENU);
}

void CoopOptions::Draw(){
  ClearBackground(BLACK);
  ray_functions::DrawFormatedText(imagesName[bgImageIndex].c_str(), Vec2<double>{1.0f/2, 0.45}, 1.0f/30, RAYWHITE);
  ray_functions::DrawFormatedText("Control P1:", Vec2<double>{0.15, 0.6}, 1.0f/30, RAYWHITE);
  ray_functions::DrawFormatedText("Control P2:", Vec2<double>{0.85, 0.6}, 1.0f/30, RAYWHITE);
}

void CoopOptions::CoopOptionsHandling(){
  for(int i = 0; i < 2; i++) readyButtons[i].SetButtonText(readyStr[clicked[i]]);
  ReadyButtonsHandling();
  ControlButtonsHandling();
  BgSelectorHandling();
}

void CoopOptions::ReadyButtonsHandling(){
  for(int i = 0; i < 2; i++){
    if(readyButtons[i].isButtonClicked()){
      clicked[i] = !clicked[i];
      readyButtons[i].Unclick();
    }
  }
  if(clicked[0] == clicked[1] && clicked[0]) Close(COOP);
}

void CoopOptions::ControlButtonsHandling(){
  string controlString;
  for(int i = 0; i < 2; i++){
    controlString = controlButtons[i]->GetText();
    db[playersControls[i]] = controlsIndexes[controlString];
    selectedControls[i] = controlString;
  }
}

void CoopOptions::BgSelectorHandling(){
  if(backgroundSelector.isButtonClicked()){
    bgImageIndex = (bgImageIndex + 1)%bgImagesSize;
    backgroundSelector.SetImage(bgImages[bgImageIndex]);
    backgroundSelector.Unclick();
    coopBgImage = bgImageIndex;
    db["COOPBGIMAGE"] = bgImageIndex;
  }
}

void CoopOptions::Close(Screens screen){
  nextScreen = screen;
  OpenClose();
  for(int i = 0; i < 2; i++) clicked[i] = false;
}
