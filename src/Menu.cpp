#include "../include/Menu.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>

Menu::Menu() : Screen(-1, Screens::GAME) {}

void Menu::Tick(){
  OptionsHandling();
  BeginDrawing();
  Draw();
  EndDrawing();
}

void Menu::Draw(){
  ClearBackground(BLACK);
  DrawText("LETRIS", settings::screenWidth/3, settings::screenHeight/3, settings::screenHeight/10, RED);
  DrawText("Jogar", settings::screenWidth/4, settings::screenHeight/1.5, settings::screenHeight/15, optionsColor[0]);
  DrawText("Sair", settings::screenWidth/1.75, settings::screenHeight/1.5, settings::screenHeight/15, optionsColor[1]);
}

void Menu::OptionsHandling(){
  auto keypressed = GetKeyPressed();
  switch (keypressed) {
    case KEY_RIGHT:
      currentSelected < OPT_QTD - 1 ? ++currentSelected : currentSelected = 0;
      break;
    case KEY_LEFT:
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
