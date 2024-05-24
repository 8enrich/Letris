#include "../include/Menu.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>

void Menu::Tick(){
  OptionsHandling();
  BeginDrawing();
  Draw();
  EndDrawing();
}

void Menu::Draw(){
  ClearBackground(BLACK);
  ray_functions::DrawFormatedText("LETRIS", Vec2<double>{(float)1/2, (float)1/3}, (float)1/10, RED);
  ray_functions::DrawFormatedText("Jogar", Vec2<double>{(float)1/4, (float)1/1.5}, (float)1/15, optionsColor[0]);
  ray_functions::DrawFormatedText("Opções", Vec2<double>{(float)1/2, (float)1/1.5}, (float)1/15, optionsColor[1]);
  ray_functions::DrawFormatedText("Sair", Vec2<double>{(float)3/4, (float)1/1.5}, (float) 1/15, optionsColor[2]);
}

void Menu::OptionsHandling(){
  auto keypressed = GetKeyPressed();
  switch (keypressed) {
    case KEY_RIGHT:
      currentSelected = (currentSelected + 1)%OPT_QTD_MENU;
      break;
    case KEY_LEFT:
      currentSelected = (currentSelected + 5)%OPT_QTD_MENU;
      break;
  }
  for (int i = 0; i < OPT_QTD_MENU; i++) { optionsColor[i] = (i == currentSelected) ? RAYWHITE : GRAY; }
  if (IsKeyPressed(KEY_ENTER)) {
    switch (currentSelected) {
      case 0:
        nextScreen = GAME;
        break;
      case 1:
        nextScreen = OPTIONS;
        break;
      case 2:
        nextScreen = EXIT;
        break;
    }
    OpenClose();
    currentSelected = 0;
  }
}
