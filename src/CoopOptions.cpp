#include "../include/CoopOptions.hpp"
#include "../include/AllocError.hpp"
#include "raylib.h"
#include <string>

using namespace settings;
using namespace std;

CoopOptions::CoopOptions() : 
  returnButton(ScreenButton("<", Vec2<double>{1.0f/30, 1.0f/50}, 1.0f/20, MENU))
{
  for(int i = 0; i < 2; i++){
    for (const auto& pair : controlsIndexes) {
      if (pair.second == coopControls[i]){
        selectedControls[i] = pair.first;
        break;
      }
    }
    controlButtons[i] = new OptionsButton(selectedControls[i], Vec2<double>{0.15 + i * 0.70, 1/1.4}, fontSize, controlOptions[i]);
    if(!controlButtons[i]) throw AllocError("CoopOptions", "controlButtons[" + to_string(i) + "]");
    buttons.push_back(&(readyButtons[i]));
    buttons.push_back(controlButtons[i]);
    shapes[i] = new L_Shape(boards[i], db["COOPSKINS"][i]);
    if(!shapes[i]) throw AllocError("CoopOptions", "shapes[" + to_string(i) + "]");
    shapes[i]->Fall();
    buttons.push_back(&(skinSelector[i]));
  }
  buttons.push_back(&backgroundSelector);
  buttons.push_back(&returnButton);
  buttonManager = new ButtonManager(buttons);
  if(!buttonManager) throw AllocError("CoopOptions", "buttonManager");
}

CoopOptions::~CoopOptions(){
  for(int i = 0; i < 2; i++){
    delete controlButtons[i];
    delete shapes[i];
  }
  delete buttonManager;
}

void CoopOptions::Tick(){
  bool error = CoopOptionsHandling();
  if(error) throw AllocError("CoopOptions", "shapes");
  SetBoardsPosition();
  BeginDrawing();
  Draw();
  buttonManager->Tick();
  EndDrawing();
  if(GetKeyPressed() == KEY_ESCAPE) Close(MENU);
  if(returnButton.isButtonClicked()){
    Close(MENU);
    returnButton.Unclick();
  }
}

void CoopOptions::Draw(){
  ClearBackground(BLACK);
  ray_functions::DrawImage(bgImage);
  ray_functions::DrawFormatedText("Select background:", Vec2<double>{1.0f/2, 0.45}, fontSize, RAYWHITE);
  ray_functions::DrawFormatedText(imagesName[bgImageIndex].c_str(), Vec2<double>{1.0f/2, 0.75}, fontSize, RAYWHITE);
  for(int i = 0; i < 2; i++){
    ray_functions::DrawFormatedText(TextFormat("Skin P%d:", i + 1), Vec2<double>{0.15 + i * 0.70, 1.0f/8}, fontSize, RAYWHITE);
    ray_functions::DrawFormatedText(TextFormat("Control P%d:", i + 1), Vec2<double>{0.15 + i * 0.70, 0.65}, fontSize, RAYWHITE);
    boards[i].Draw();
    boards[i].DrawBorder();
    shapes[i]->DrawSkin(db["COOPSKINS"][i]);
  }
}

bool CoopOptions::CoopOptionsHandling(){
  for(int i = 0; i < 2; i++) readyButtons[i].SetButtonText(readyStr[clicked[i]]);
  bool hasError = SkinSelectorHandling();
  if(hasError) return true;
  ControlButtonsHandling();
  BgSelectorHandling();
  ReadyButtonsHandling();
  return false;
}

bool CoopOptions::SkinSelectorHandling(){
  string skinString;
  int skinIndex;
  for(int i = 0; i < 2; i++){
    skinString = skinSelector[i].GetText();
    for(skinIndex = 0; skinIndex < skinNames.size(); skinIndex++) if(skinNames[skinIndex] == skinString) break;
    db["COOPSKINS"][i] = skinIndex;
    selectedSkin[i] = skinString;
    delete shapes[i];
    shapes[i] = new L_Shape(boards[i], db["COOPSKINS"][i]);
    if(!shapes[i]) return true;
    shapes[i]->Fall();
  }
  return false;
}

void CoopOptions::ControlButtonsHandling(){
  string controlString;
  for(int i = 0; i < 2; i++){
    controlString = controlButtons[i]->GetText();
    db["COOPCONTROLS"][i] = controlsIndexes[controlString];
    selectedControls[i] = controlString;
  }
}

void CoopOptions::BgSelectorHandling(){
  if(backgroundSelector.isButtonClicked()){
    bgImageIndex = (bgImageIndex + 1)%bgImagesSize;
    backgroundSelector.SetImage(bgImages[bgImageIndex]);
    backgroundSelector.Unclick();
    db["COOPBGIMAGE"] = bgImageIndex;
  }
}

void CoopOptions::ReadyButtonsHandling(){
  for(int i = 0; i < 2; i++){
    if(readyButtons[i].isButtonClicked()){
      clicked[i] = !clicked[i];
      readyButtons[i].Unclick();
      Color color = clicked[i]?GREEN:RED;
      readyButtons[i].SetColor(color);
    }
  }
  if(clicked[0] == clicked[1] && clicked[0]) Close(COOP);
}

void CoopOptions::Close(Screens screen){
  nextScreen = screen;
  OpenClose();
  for(int i = 0; i < 2; i++){
    clicked[i] = false;
    readyButtons[i].SetColor(RED);
  }
}

void CoopOptions::SetBoardsPosition(){
  int posX = 0;
  for(int i = 0; i < 2; i++){
    posX = (int)(screenWidth * (0.15 + i * 0.70)) - 2 * cellSize;
    if(boards[i].GetScreenPos().GetX() != posX){
      boards[i].ResetBoardSettings(cellSize, {posX, (int)(screenHeight * 0.20)});
      skinSelector[i].SetButtonPosition(Vec2<double>{0.15 + i * 0.70, 0.20 + (float)(5.55 * cellSize)/screenHeight});
    }
  }
}
