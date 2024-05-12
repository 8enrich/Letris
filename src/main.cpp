#include "../include/Game.hpp"
#include "../include/Menu.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#endif

int main(){
  Menu menu {settings::screenWidth, settings::screenHeight, settings::fps, "Letris"};
  Board board {settings::boardPosition, settings::boardWidthHeight, settings::cellSize, settings::padding};
  Game *game = nullptr;

  enum screens{
    MENU,
    GAME,
  };

  int actualScreen = screens::MENU;

  while (!WindowShouldClose()) {
    switch(actualScreen){
      case MENU:
        if(menu.MenuShouldClose()){
          actualScreen = screens::GAME;
          game = new Game{board};
          game->OpenCloseGame();
          break;
        }
        menu.Draw();
        break;
      case GAME:
        if(game->GameShouldClose()){
          actualScreen = screens::MENU;
          delete game;
          menu.OpenCloseMenu();
          break;
        }
        game->Tick();
        break;
    }
  }

  if(game) delete game;
  return 0;
}

