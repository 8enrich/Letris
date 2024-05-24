#include "../include/Window.hpp"
#include "../include/Settings.hpp"
#include "../include/Menu.hpp"
#include "../include/Options.hpp"
#include "../include/Game.hpp"
#include "../include/Pause.hpp"
#include "../include/GameOver.hpp"
#include <raylib.h>
#include <memory>

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#endif

int main(){
  Window window {settings::screenWidth, settings::screenHeight, settings::fps, "Letris"};
  Board board {settings::boardPosition, settings::boardWidthHeight, settings::cellSize, settings::padding};

  std::unique_ptr<Screen> screens[] = {
    std::make_unique<Menu>(),
    std::make_unique<Options>(),
    std::make_unique<Game>(board),
    std::make_unique<Pause>(),
    std::make_unique<GameOver>(),
  };

  int actualScreen = MENU;
  bool entered = false;

  while (!WindowShouldClose()) {
    if(actualScreen == EXIT) break;
    if(actualScreen == MENU || actualScreen == GAMEOVER)
      screens[GAME] = std::make_unique<Game>(board);
    if(!entered){
      screens[actualScreen]->OpenClose();
      entered = true;
    }
    if(screens[actualScreen]->ShouldClose()){
      actualScreen = screens[actualScreen]->GetScreen();
      entered = false;
      continue;
    }
    screens[actualScreen]->Tick();
  }

  return 0;
}

