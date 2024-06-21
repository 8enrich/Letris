#include "../include/GameOver.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>

GameOver::~GameOver(){
  for (auto button : buttons) delete button;
}
GameOver::GameOver(){}
void GameOver::Tick(){
  if(IsMusicStreamPlaying(music)) {UpdateMusicStream(music);}
  OptionsHandling();
  BeginDrawing();
  Draw();
  buttonManager.Tick();
  EndDrawing();
}

void GameOver::Draw(){
  ClearBackground(BLACK);
  ray_functions::DrawFormatedText("GAME OVER", Vec2<double>{(float)1/2, (float)1/5}, (float) 1/13, RAYWHITE);
}

void GameOver::OptionsHandling(){
  if (buttonManager.GetScreen() != NOTSCREEN) {
    nextScreen = buttonManager.GetScreen();
    buttonManager.ResetScreen();
    OpenClose();
  }
}
