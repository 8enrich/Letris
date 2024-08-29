#include "../include/Pause.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>

void Pause::Tick(){
  if(IsMusicStreamPlaying(music)) {UpdateMusicStream(music);}
  OptionsHandling();
  BeginDrawing();
  Draw();
  buttonManager.Tick();
  EndDrawing();
}

void Pause::Draw(){
  DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{0,0,0,100});
  ray_functions::DrawFormatedText("PAUSED", Vec2<double>{(float)1/2, (float)1/5}, (float) 1/13, RAYWHITE);
}

void Pause::OptionsHandling(){
  if (buttonManager.GetScreen() != NOTSCREEN) {
    nextScreen = buttonManager.GetScreen();
    buttonManager.ResetScreen();
    OpenClose();
  }
}

void Pause::OpenClose(){
  Screen::OpenClose();
  if(nextScreen == GAME || nextScreen == COOP) Continue.SetScreen(nextScreen);
}
