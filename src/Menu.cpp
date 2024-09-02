#include "../include/Menu.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>
#include <string>

Menu::Menu() :
  logoTexture(new Texture2D(LoadTexture((std::string(ASSETS_PATH) + "logo.png").c_str()))),
  Screen(std::string(ASSETS_PATH)+"menu.mp3")
{
  if(!logoTexture) throw std::bad_alloc();
}

Menu::~Menu(){
  UnloadTexture(*logoTexture);
  delete logoTexture;
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
  ray_functions::DrawScaledImage(logoTexture, {1.0f/2, 1.0f/3}, 0.5);
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
  bool tip = false;
  for(int i = 0; i < 3; i++){
    int colorA = 0;
    float posY = 1.0f/2;
    for(int j = 0; j < 350; j++){
      int key = GetKeyPressed();
      if(key == KEY_ENTER){
        isFirstEntrance = false;
        StopSound(intro);
        return;
      }
      if(key != KEY_NULL) tip = true;
      Color color = Color{255, 255, 255, (unsigned char) colorA};
      BeginDrawing();
      ClearBackground(BLACK);
      if(tip) ray_functions::DrawFormatedText("Press Enter to Skip ->", Vec2<double>{1.0f/1.15, 1.0f/1.1}, 1.0f/30, RAYWHITE);
      if(i < 2) ray_functions::DrawFormatedText(texts[i].c_str(), Vec2<double>{1.0f/2, 1.0f/2}, 1.0f/20, color);
      else ray_functions::DrawScaledImage(logoTexture, {1.0f/2, posY}, 0.5);
      EndDrawing();
      if(!i && j < 115) continue;
      if(j < 250){
        colorA+=2;
        if(colorA > 255) colorA = 255;
      }
      else{
        colorA-=3;
        if(colorA < 0) colorA = 0;
      }
      if(j > 31 && posY > 1.0f/3) posY-=0.00158;
    }
  }
  isFirstEntrance = false;
}
