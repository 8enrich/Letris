#include "../include/SoloOptions.hpp"
#include "../include/AllocError.hpp"
#include "raylib.h"

using namespace std;
using namespace settings;
using namespace ray_functions;

SoloOptions::SoloOptions() :
  board(Board({{(int)(screenWidth * 1.0f/4) - 2 * cellSize, (int)(screenHeight * 0.20)}, {4, 5}, cellSize, padding})), 
  skinSelector(OptionsButton(selectedSkin, Vec2<double>{1.0f/4, 0.20 + (float)(5.55 * cellSize)/screenHeight}, fontSize, skinNames)),
  backgroundSelector(ScreenButton(Vec2<double>{0.62, 0.18}, COOP, bgImagesNames[soloBgImage], Vec2<double>{4, 8})),
  inputText(ScreenButton("                ", Vec2<double>{1.0f/2, 1.0f/2}, fontSize, GAME)),
  play(ScreenButton("Play", Vec2<double>{1.0f/2, 1.0f/1.2}, 1.0f/20, GAME, Color{11,229,248, 255})),
  returnButton(ScreenButton("<", Vec2<double>{1.0f/30, 1.0f/50}, 1.0f/20, MENU)),
  bgImageIndex(0), bgImagesSize(settings::bgImagesNames.size()), inputTextSelected(false),
  inputTextStr("0")
{
  shape = new L_Shape(board, db["SKIN"]);
  if(!shape) throw AllocError("SoloOptions", "shape");
  shape->Fall();
  buttons = {&skinSelector, &backgroundSelector, &inputText, &play, &returnButton};
  buttonManager = new ButtonManager(buttons);
  if(!buttonManager) throw AllocError("SoloOptions", "buttonManager");
}

SoloOptions::~SoloOptions(){
  delete shape;
  delete buttonManager;
}

void SoloOptions::Tick(){
  bool error = SoloOptionsHandling();
  if(error) throw AllocError("SoloOptions", "shape");
  SetBoardPosition();
  BeginDrawing();
  Draw();
  buttonManager->Tick();
  Color color = RAYWHITE;
  if(!inputTextSelected) color = GRAY;
  DrawFormatedText(inputTextStr.c_str(), Vec2<double>{1.0f/2, 1.0f/2}, fontSize, color);
  EndDrawing();
}

void SoloOptions::Draw(){
  ClearBackground(BLACK);
  board.Draw();
  board.DrawBorder();
  shape->DrawSkin(db["SKIN"]);
  DrawFormatedText("Skin", Vec2<double>{1.0f/4, 0.13}, fontSize, RAYWHITE);
  DrawFormatedText("Select background:", Vec2<double>{3.0f/4, 0.13}, fontSize, RAYWHITE);
  DrawFormatedText("Level:", Vec2<double>{1.0f/2, 0.45}, fontSize, RAYWHITE);
}

bool SoloOptions::SoloOptionsHandling(){
  bool error = SkinSelectorHandling();
  if(error) return true;
  BgSelectorHandling();
  InputTextHandling();
  ScreenButtonsHandling();
  return false;
}

void SoloOptions::BgSelectorHandling(){
  if(backgroundSelector.isButtonClicked()){
    bgImageIndex = (bgImageIndex + 1)%bgImagesSize;
    backgroundSelector.SetImage(bgImages[bgImageIndex]);
    backgroundSelector.Unclick();
    db["SOLOBGIMAGE"] = bgImageIndex;
  }
}

void SoloOptions::InputTextHandling(){
  InputTextSettings();
  DrawRectangle(Vec2<double>{1.0f/2 * screenWidth - 1.0f/20 * screenWidth, 1.0f/2 * screenHeight}, Vec2<double>{1.0f/10 * screenWidth, 1.0f/20 * screenHeight}, DARKGRAY);
  if(inputText.isMouseHoveringButton()) SetMouseCursor(MOUSE_CURSOR_IBEAM);
  if(inputTextSelected){
    string buttonText = GetKeyboardInput();
    inputTextStr = buttonText;
    level = stoi(buttonText);
  }
}

void SoloOptions::InputTextSettings(){
  if(inputText.isButtonClicked()){
    inputTextSelected = true;
    inputText.Unclick();
  }
  if(!inputText.isMouseHoveringButton() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) inputTextSelected = false;
}

string SoloOptions::GetKeyboardInput(){
  string cursor, buttonText = inputTextStr;
  int value = 0, letterCount = buttonText.size();
  if(buttonText == "0") value = 1;
  for(int i = 0; i < letterCount - value; i++) cursor +=  "  ";
  cursor += "_";
  DrawFormatedText(cursor.c_str(), Vec2<double>{1.0f/2, 0.51}, fontSize, RAYWHITE);
  int key = GetKeyPressed();
  if(key == KEY_ENTER) inputTextSelected = false;
  if(key >= 48 && key <= 57 && letterCount < 2){
    if(!value) buttonText += '\0';
    buttonText[letterCount - value] = (char)key;
    if(stoi(buttonText) > 29) buttonText = "29";
  }
  if(key == KEY_BACKSPACE){
    letterCount--;
    buttonText.pop_back();
    if(letterCount < 1) buttonText = "0";
  }
  return buttonText;
}

bool SoloOptions::SkinSelectorHandling(){
  string skinString;
  int skinIndex;
  for(int i = 0; i < 2; i++){
    skinString = skinSelector.GetText();
    for(skinIndex = 0; skinIndex < skinNames.size(); skinIndex++) if(skinNames[skinIndex] == skinString) break;
    db["SKIN"] = skinIndex;
    selectedSkin = skinString;
    delete shape;
    shape = new L_Shape(board, db["SKIN"]);
    if(!shape) return true;
    shape->Fall();
  }
  return false;
}

void SoloOptions::ScreenButtonsHandling(){
  if(GetKeyPressed() == KEY_ESCAPE || returnButton.isButtonClicked()){
    Close(MENU);
    returnButton.Unclick();
  }
  if(play.isButtonClicked()){
    Close(GAME);
    play.Unclick();
  }
}

void SoloOptions::Close(Screens screen){
  nextScreen = screen;
  OpenClose();
}

void SoloOptions::SetBoardPosition(){
  int posX = (int)(screenWidth * 1.0f/4) - 2 * cellSize;
  if(board.GetScreenPos().GetX() != posX){
    board.ResetBoardSettings(cellSize, {posX, (int)(screenHeight * 0.20)});
    skinSelector.SetButtonPosition(Vec2<double>{1.0f/4, 0.20 + (float)(5.55 * cellSize)/screenHeight});
  }
}
