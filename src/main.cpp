#include "../include/Game.hpp"
#include "../include/Menu.hpp"
#include "../include/Pause.hpp"
#include "../include/GameOver.hpp"
#include "../include/Settings.hpp"
#include "../include/Window.hpp"
#include <raylib.h>
#include <memory>

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#endif

int main(){
  Window window {settings::screenWidth, settings::screenHeight, settings::fps, "Letris"};
  Menu menu;
  Pause pause;
  GameOver gameOver;
  Board board {settings::boardPosition, settings::boardWidthHeight, settings::cellSize, settings::padding};
  std::unique_ptr<Game> game;

  int actualScreen = Screens::MENU;
  bool entered = false;

  while (!WindowShouldClose()) {
    switch(actualScreen){
      case MENU:
        if(!entered){
          menu.OpenClose();
          entered = true;
        }
        if(menu.ShouldClose()){
          actualScreen = menu.GetScreen();
          game = std::make_unique<Game>(board);
          entered = false;
          break;
        }
        menu.Tick();
        break;
      case GAME:
        if(!entered){
          game->OpenClose();
          entered = true;
        }
        if(game->ShouldClose()){
          actualScreen = game->GetScreen();
          entered = false;
          break;
        }
        game->Tick();
        break;
      case PAUSE:
        if(!entered){
          pause.OpenClose();
          entered = true;
        }
        if(pause.ShouldClose()){
          actualScreen = pause.GetScreen();
          entered = false;
          break;
        }
        pause.Tick();
        break;
      case GAMEOVER:
        if(!entered){
          gameOver.OpenClose();
          entered = true;
        }
        if(gameOver.ShouldClose()){
          actualScreen = gameOver.GetScreen();
          game = std::make_unique<Game>(board);
          entered = false;
          break;
        }
        gameOver.Tick();
        break;
      default:
        return 0;
    }
  }

  return 0;
}

