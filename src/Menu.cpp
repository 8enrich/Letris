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
  if(IsMusicStreamPlaying(music)) {UpdateMusicStream(music);}
}

void Menu::Draw(){
  ClearBackground(Color{14, 15, 92});
  float scale = (GetScreenWidth() * 0.5)/(float)(logoTexture->width);
  float x = 1.0f/2 * settings::screenWidth - (float)(logoTexture->width)/2 * scale;
  float y = 1.0f/3 * settings::screenHeight - (float)(logoTexture->height)/2 * scale;
  DrawTextureEx(*logoTexture, Vector2{x, y}, 0, scale, WHITE);
}

void Menu::OptionsHandling(){
  if(buttonManager.GetScreen() != NOTSCREEN) {
    nextScreen = buttonManager.GetScreen();
    buttonManager.ResetScreen();
    OpenClose();
  }
}
