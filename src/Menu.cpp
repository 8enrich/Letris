#include "../include/Menu.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>
#include <string>
Menu::Menu() :
  logoTexture(new Texture2D(LoadTexture((std::string(ASSETS_PATH) + "logo.png").c_str())))
{
  if(!logoTexture) throw std::bad_alloc();
}

Menu::~Menu(){
  UnloadTexture(*logoTexture);
  delete logoTexture;
}
void Menu::Tick(){
  OptionsHandling();
  BeginDrawing();
  Draw();
  buttonManager.Tick();
  EndDrawing();
  if(IsMusicReady(music) && IsMusicStreamPlaying(music)) {UpdateMusicStream(music);}
}

void Menu::Draw(){
  ClearBackground(Color{41, 16, 122});
  ray_functions::DrawScaledImage(logoTexture, {1.0f/2, 1.0f/3}, 0.5);
}

void Menu::OptionsHandling(){
  if(buttonManager.GetScreen() != NOTSCREEN) {
    nextScreen = buttonManager.GetScreen();
    buttonManager.ResetScreen();
    OpenClose();
  }
}
