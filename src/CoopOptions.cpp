#include "../include/CoopOptions.hpp"
#include "../include/AllocError.hpp"
#include "raylib.h"

using namespace settings;
using namespace std;

CoopOptions::CoopOptions(){
  for (const auto& pair : controlsIndexes) {
    if (pair.second == db["P1CONTROL"]) {
      selectedControlP1 = pair.first;
      break;
    }
  }
  for (const auto& pair : controlsIndexes) {
    if (pair.second == db["P2CONTROL"]) {
      selectedControlP2 = pair.first;
      break;
    }
  }
  controlP1 = new OptionsButton(selectedControlP1, Vec2<double>{0.15, 1/1.5}, fontSize, optionsP1);
  if(!controlP1) throw AllocError("CoopOptions", "controlP1");
  controlP2 = new OptionsButton(selectedControlP2, Vec2<double>{0.85, 1/1.5}, fontSize, optionsP2);
  if(!controlP2) throw AllocError("CoopOptions", "controlP2");
  buttons = {&readyP1, &readyP2, controlP1, controlP2, &backgroundSelector };
  buttonManager = new ButtonManager(buttons);
  if(!buttonManager) throw AllocError("CoopOptions", "buttonManager");
}

void CoopOptions::Tick(){
  CoopOptionsHandling();
  BeginDrawing();
  Draw();
  buttonManager->Tick();
  EndDrawing();
  if(GetKeyPressed() == KEY_ESCAPE){
    nextScreen = MENU;
    OpenClose();
    clicked[0] = false;
    clicked[1] = false;
  }
}

void CoopOptions::Draw(){
  ClearBackground(BLACK);
  ray_functions::DrawFormatedText(imagesName[bgImageIndex].c_str(), Vec2<double>{1.0f/2, 0.45}, 1.0f/30, RAYWHITE);
  ray_functions::DrawFormatedText("Control P1:", Vec2<double>{0.15, 0.6}, 1.0f/30, RAYWHITE);
  ray_functions::DrawFormatedText("Control P2:", Vec2<double>{0.85, 0.6}, 1.0f/30, RAYWHITE);
}

void CoopOptions::CoopOptionsHandling(){
  for(int i = 0; i < readyButtons.size(); i++) readyButtons[i]->SetButtonText(readyStr[clicked[i]]);
  ReadyButtonsHandling();
  ControlButtonsHandling();
  BgSelectorHandling();
}

void CoopOptions::ReadyButtonsHandling(){
  for(int i = 0; i < readyButtons.size(); i++){
    if(readyButtons[i]->isButtonClicked()){
      clicked[i] = 1 - clicked[i];
      readyButtons[i]->Unclick();
    }
  }
  if(clicked[0] == clicked[1] && clicked[0]){
    nextScreen = COOP;
    OpenClose();
    clicked[0] = false;
    clicked[1] = false;
  }
}

void CoopOptions::ControlButtonsHandling(){
  string controlString = controlP1->GetText();
  if (selectedControlP1 != controlString){
    db["P1CONTROL"] = controlsIndexes[controlString];
    selectedControlP1 = controlString;
  }
  controlString = controlP2->GetText();
  if (selectedControlP2 != controlString){
    db["P2CONTROL"] = controlsIndexes[controlString];
    selectedControlP2 = controlString;
  }
}

void CoopOptions::BgSelectorHandling(){
  if(backgroundSelector.isButtonClicked()){
    bgImageIndex= (bgImageIndex + 1)%bgImagesNames.size();
    backgroundSelector.SetImage(bgImages[bgImageIndex]);
    backgroundSelector.Unclick();
    coopBgImage = bgImageIndex;
    db["COOPBGIMAGE"] = bgImageIndex;
  }
}
