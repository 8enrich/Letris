#include "../include/Menu.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>
#include <iostream>
void Menu::Tick(){
  OptionsHandling();
  BeginDrawing();
  Draw();
  EndDrawing();
  if(IsMusicStreamPlaying(music)) {UpdateMusicStream(music);}
}

void Menu::Draw(){
  ClearBackground(BLACK);
  ray_functions::DrawFormatedText("LETRIS", Vec2<double>{1.0f/2, 1.0f/3}, 1.0f/10, RED);
  ray_functions::DrawFormatedText("Play", Vec2<double>{1.0f/4, 1.0f/1.5}, 1.0f/15, optionsColor[0]);
  ray_functions::DrawFormatedText("Options", Vec2<double>{1.0f/2, 1.0f/1.5}, 1.0f/15, optionsColor[1]);
  ray_functions::DrawFormatedText("Quit", Vec2<double>{3.0f/4, 1.0f/1.5}, 1.0f/15, optionsColor[2]);
}

void Menu::OptionsHandling(){
  auto keypressed = GetKeyPressed();
  switch (keypressed) {
    case KEY_RIGHT:
      currentSelected = (currentSelected + 1)%OPT_QTD_MENU;
      break;
    case KEY_LEFT:
      currentSelected = (currentSelected + (OPT_QTD_MENU * 2 - 1))%OPT_QTD_MENU;
      break;
  }
  for (int i = 0; i < OPT_QTD_MENU; i++) { optionsColor[i] = (i == currentSelected) ? RAYWHITE : GRAY; }
  if (IsKeyPressed(KEY_ENTER)) {
    nextScreen = static_cast<Screens>(currentSelected);
    OpenClose();
    currentSelected = 0;
  }
}
