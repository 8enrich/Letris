#include "../include/Game.hpp"
#include "../include/Menu.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>
#include <memory>

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#endif

int main(){
  Menu menu {settings::screenWidth, settings::screenHeight, settings::fps, "Letris"};
  Board board {settings::boardPosition, settings::boardWidthHeight, settings::cellSize, settings::padding};
  std::unique_ptr<Game> game;

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
          game = std::make_unique<Game>(board);
          game->OpenCloseGame();
          break;
        }
        menu.Draw();
        break;
      case GAME:
        if(game->GameShouldClose()){
          actualScreen = screens::MENU;
          game.reset();
          menu.OpenCloseMenu();
          break;
        }
        game->Tick();
        break;
    }
  }

  return 0;
}

