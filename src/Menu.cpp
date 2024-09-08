#include "../include/Menu.hpp"
#include "../include/Settings.hpp"
#include "../include/AllocError.hpp"
#include <raylib.h>
#include <string>

Menu::Menu() :
  logoTexture(new Texture2D(LoadTexture((std::string(ASSETS_PATH) + "logo.png").c_str()))),
  backgroundTexture(new Texture2D(LoadTexture((std::string(ASSETS_PATH) + "menubg.png").c_str()))),
  Screen(std::string(ASSETS_PATH)+"menu.mp3")
{
  if(!logoTexture) throw AllocError("Menu", "logoTexture");
  if(!backgroundTexture) throw AllocError("Menu", "backgroundTexture");
}

Menu::~Menu(){
  UnloadTexture(*logoTexture);
  delete logoTexture;
  UnloadTexture(*backgroundTexture);
  delete backgroundTexture;
}
void Menu::Tick(){
  if(isFirstEntrance) Intro();
  OptionsHandling();
  BeginDrawing();
  Draw();
  buttonManager.Tick();
  EndDrawing();
  if(IsMusicReady(music) && IsMusicStreamPlaying(music)) {UpdateMusicStream(music);}
}

void Menu::Draw(){
  ClearBackground(Color{41, 16, 122});
  ray_functions::DrawImage(backgroundTexture);
  ray_functions::DrawScaledImage(logoTexture, {1.0f/2, 1.0f/3}, 0.5);
  //DrawFPS(0, 0);
}

void Menu::OptionsHandling(){
  if(buttonManager.GetScreen() != NOTSCREEN) {
    nextScreen = buttonManager.GetScreen();
    buttonManager.ResetScreen();
    OpenClose();
  }
}

void Menu::Intro(){
  std::vector<std::string> texts = {"A dabzr & 8enrich production", "Sound by Daniel Santos & Art by José Iramar"};
  Sound intro = LoadSound((std::string(ASSETS_PATH)+ "intro.mp3").c_str());
  PlaySound(intro);
  int value = 0;
  Color tipColor = Color{255, 255, 255, 0};
  Color color = Color{255, 255, 255, 0};
  float posY = 1.0f/2;
  for(int i = 0; i < 3; i++){
    if(i) value = 115 + (i - 1) * 100;
    for(int j = 0; j < 340 - value; j++){
      int key = GetKeyPressed();
      if(key == KEY_ENTER){
        isFirstEntrance = false;
        StopSound(intro);
        return;
      }
      if(key != KEY_NULL) tipColor.a = 255;
      BeginDrawing();
      ClearBackground(BLACK);
      ray_functions::DrawFormatedText("Press Enter to Skip ->", Vec2<double>{1.0f/1.15, 1.0f/1.1}, 1.0f/30, tipColor);
      if(i < 2) ray_functions::DrawFormatedText(texts[i].c_str(), Vec2<double>{1.0f/2, 1.0f/2}, 1.0f/20, color);
      else ray_functions::DrawScaledImage(logoTexture, {1.0f/2, posY}, 0.5);
      EndDrawing();
      if(tipColor.a != 0 && tipColor.a > 3)tipColor.a-=3;
      if(!i && j < 115) continue;
      if(j < 240 - value && color.a < 254) color.a+=2;
      else if (color.a >= 3) color.a-=3;
      if(i == 2 && j > 20 && posY > 1.0f/3) posY-=0.0016;
    }
  }
  isFirstEntrance = false;
}
