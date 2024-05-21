#include "../include/Pause.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>

Pause::Pause() : Screen() {}

void Pause::Tick(){
  OptionsHandling();
  BeginDrawing();
  Draw();
  EndDrawing();
}

void Pause::Draw(){
  ClearBackground(BLACK);
  DrawText("Pause", (settings::screenWidth - MeasureText("Pause", settings::screenHeight/13))/2,
      settings::screenHeight/5, settings::screenHeight/13, RAYWHITE);
  DrawText("Continuar", (settings::screenWidth - MeasureText("Continuar", settings::screenHeight/20))/2,
      settings::screenHeight/2.5, settings::screenHeight/20, optionsColor[0]);
  DrawText("Voltar ao menu", (settings::screenWidth - MeasureText("Voltar ao menu", settings::screenHeight/20))/2,
      settings::screenHeight/1.8, settings::screenHeight/20, optionsColor[1]);
}

void Pause::OptionsHandling(){
  auto keypressed = GetKeyPressed();
  switch (keypressed) {
    case KEY_DOWN:
      currentSelected < OPT_QTD - 1 ? ++currentSelected : currentSelected = 0;
      break;
    case KEY_UP:
      currentSelected > 0 ? currentSelected-- : currentSelected = OPT_QTD-1;
      break;
  }
  for (int i = 0; i < OPT_QTD; i++) optionsColor[i] = (i == currentSelected)? RAYWHITE : GRAY;
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
