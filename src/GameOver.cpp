#include "../include/GameOver.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>

GameOver::GameOver() : Screen(Screens::MENU, Screens::GAME) {}

void GameOver::Tick(){
  OptionsHandling();
  BeginDrawing();
  Draw();
  EndDrawing();
}

void GameOver::Draw(){
  ClearBackground(BLACK);
  DrawText("Game Over", (settings::screenWidth - MeasureText("Game Over", settings::screenHeight/13))/2,
      settings::screenHeight/5, settings::screenHeight/13, RAYWHITE);
  DrawText("Jogar Novamente", (settings::screenWidth - MeasureText("Jogar Novamente", settings::screenHeight/20))/2,
      settings::screenHeight/2.5, settings::screenHeight/20, optionsColor[0]);
  DrawText("Voltar ao menu", (settings::screenWidth - MeasureText("Voltar ao menu", settings::screenHeight/20))/2,
      settings::screenHeight/1.8, settings::screenHeight/20, optionsColor[1]);
}

void GameOver::OptionsHandling(){
  auto keypressed = GetKeyPressed();
  switch (keypressed) {
    case KEY_DOWN:
      currentSelected < OPT_QTD - 1 ? ++currentSelected : currentSelected = 0;
      break;
    case KEY_UP:
      currentSelected > 0 ? currentSelected-- : currentSelected = OPT_QTD-1;
      break;
  }
  for (int i = 0; i < OPT_QTD; i++) { optionsColor[i] = i == currentSelected ? RAYWHITE : GRAY; }
  if (IsKeyPressed(KEY_ENTER)) {
    switch (currentSelected) {
      case 0:
        screenToReturn = nextScreen;
        break;
      case 1:
        screenToReturn = previousScreen;
        break;
    }
    OpenClose();
    currentSelected = 0;
  }
}
