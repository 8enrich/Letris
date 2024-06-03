#include "../include/GameOver.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>

void GameOver::Tick(){
  OptionsHandling();
  BeginDrawing();
  Draw();
  EndDrawing();
}

void GameOver::Draw(){
  ClearBackground(BLACK);
  ray_functions::DrawFormatedText("Game Over", Vec2<double>{(float)1/2, (float)1/5}, (float) 1/13, RAYWHITE);
  ray_functions::DrawFormatedText("Jogar Novamente", Vec2<double>{(float)1/2, (float)1/2.5}, (float)1/20, optionsColor[0]);
  ray_functions::DrawFormatedText("Opções", Vec2<double>{(float)1/2, (float)1/1.8}, (float)1/20, optionsColor[1]);
  ray_functions::DrawFormatedText("Voltar ao Menu", Vec2<double>{(float)1/2, (float)32/45}, (float)1/20, optionsColor[2]);
}

void GameOver::OptionsHandling(){
  auto keypressed = GetKeyPressed();
  switch (keypressed) {
    case KEY_DOWN:
      currentSelected = (currentSelected + 1)%OPT_QTD;
      break;
    case KEY_UP:
      currentSelected = (currentSelected + (OPT_QTD * 2 - 1))%OPT_QTD;
      break;
  }
  for (int i = 0; i < OPT_QTD; i++) { optionsColor[i] = (i == currentSelected) ? RAYWHITE : GRAY; }
  if (IsKeyPressed(KEY_ENTER)) {
    switch (currentSelected) {
      case 0:
        nextScreen = GAME;
        break;
      case 1:
        nextScreen = OPTIONS;
        break;
      case 2:
        nextScreen = MENU;
        break;
    }
    OpenClose();
    currentSelected = 0;
  }
}
