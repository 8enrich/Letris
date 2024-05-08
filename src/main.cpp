#include "../include/Game.hpp"
#include "../include/Menu.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>
int main(){
  Menu menu {settings::screenWidth, settings::screenHeight, settings::fps, "Letris"}; 
  Board board {settings::boardPosition, settings::boardWidthHeight, settings::cellSize, settings::padding};
  Game game {board};

  bool inMenu = true;

  while (!WindowShouldClose()) {
    if (inMenu && game.GameShouldClose()) {
      menu.Draw();
      if (menu.MenuShouldClose()) {
        inMenu = false;
        game.OpenCloseGame();
        continue;
      }
    }
    if (!inMenu) {
      if (game.GameShouldClose()) {
        inMenu = true;
        menu.OpenCloseMenu();
      }
      else game.Tick();
    }
  }

}

