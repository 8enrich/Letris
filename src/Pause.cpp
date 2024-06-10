#include "../include/Pause.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>

void Pause::Tick(){
  OptionsHandling();
  BeginDrawing();
  Draw();
  EndDrawing();
}

void Pause::Draw(){
  ClearBackground(BLACK);
  ray_functions::DrawFormatedText("PAUSE", Vec2<double>{(float)1/2, (float)1/5}, (float)1/13, RAYWHITE);
  float x = (float)1/2, y = (float)1/2.2, fontSize = (float)1/20, lineDistance = (float)7/33;
  ray_functions::DrawFormatedText("Continuar", Vec2<double>{x, y}, fontSize, optionsColor[0]);
  ray_functions::DrawFormatedText("Voltar ao Menu", Vec2<double>{x, y + lineDistance}, fontSize, optionsColor[1]);
}

void Pause::OptionsHandling(){
  auto keypressed = GetKeyPressed();
  switch (keypressed) {
    case KEY_DOWN:
      currentSelected = (currentSelected + 1)%OPT_QTD_PAUSE;
      break;
    case KEY_UP:
      currentSelected = (currentSelected + (OPT_QTD_PAUSE * 2 - 1))%OPT_QTD_PAUSE;
      break;
  }
  for (int i = 0; i < OPT_QTD_PAUSE; i++) optionsColor[i] = (i == currentSelected)? RAYWHITE : GRAY;
  if (IsKeyPressed(KEY_ENTER)) {
    switch (currentSelected) {
      case 0:
        nextScreen = GAME;
        break;
      case 1:
        nextScreen = MENU;
        break;
    }
    OpenClose();
    currentSelected = 0;
  }
}
