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
  std::unique_ptr<Board> board = std::make_unique<Board> (settings::boardPosition, settings::boardWidthHeight,
      settings::cellSize, settings::padding);

  std::unique_ptr<Screen> screens[] = {
    std::make_unique<Menu>(),
    std::make_unique<Options>(),
    NULL,
    std::make_unique<Pause>(),
    std::make_unique<GameOver>(),
  };

  int actualScreen = MENU, lastScreen = EXIT;
  bool entered = false;

  while (!WindowShouldClose()) {
    if(actualScreen == EXIT) break;
    if(!entered){
      screens[actualScreen]->OpenClose();
      entered = true;
    }
    if(screens[actualScreen]->ShouldClose()){
      entered = false;
      if(actualScreen == OPTIONS){
        actualScreen = lastScreen;
        continue;
      }
      lastScreen = actualScreen;
      actualScreen = screens[actualScreen]->GetScreen();
      if(actualScreen == GAME && (lastScreen == MENU || lastScreen == GAMEOVER)){
        board = std::make_unique<Board>(settings::boardPosition, settings::boardWidthHeight,
      settings::cellSize, settings::padding);
        screens[GAME] = std::make_unique<Game>(*board);
      }
      continue;
    }
    screens[actualScreen]->Tick();
  }

  return 0;
}
