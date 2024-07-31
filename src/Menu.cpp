#include "../include/Menu.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>

void Menu::Tick(){
  OptionsHandling();
  BeginDrawing();
  Draw();
  buttonManager.Tick();
  EndDrawing();
  if(IsMusicStreamPlaying(music)) {UpdateMusicStream(music);}
}

void Menu::Draw(){
  ClearBackground(BLACK);
  ray_functions::DrawFormatedText("LETRIS", Vec2<double>{1.0f/2, 1.0f/3}, 1.0f/10, RED);
}

void Menu::OptionsHandling(){
  if(buttonManager.GetScreen() != NOTSCREEN) {
    nextScreen = buttonManager.GetScreen();
    buttonManager.ResetScreen();
    OpenClose();
  }
}
