#include "../include/CoopOptions.hpp"
#include "raylib.h"

void CoopOptions::Tick(){
  CoopOptionsHandling();
  BeginDrawing();
  Draw();
  buttonManager.Tick();
  EndDrawing();
}

void CoopOptions::Draw(){
  ClearBackground(BLACK);
}

void CoopOptions::CoopOptionsHandling(){
  for(int i = 0; i < readyButtons.size(); i++){
    if(readyButtons[i]->isButtonClicked() && buttonManager.GetScreen() != NOTSCREEN){
      clicked[i] = 1 - clicked[i];
      buttonManager.ResetScreen();
      readyButtons[i]->Unclick();
    }
  }
  if(clicked[0] == clicked[1] && clicked[0]){
    nextScreen = COOP;
    OpenClose();
    clicked[0] = false;
    clicked[1] = false;
  }
  for(int i = 0; i < readyButtons.size(); i++) readyButtons[i]->SetButtonText(readyStr[clicked[i]]);
}
