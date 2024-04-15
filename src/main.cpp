#include "../include/Game.hpp"
#include "../include/Settings.hpp"
int main(){

  Game game {settings::screenWidth, settings::screenHeight, settings::fps, "Letris"};
  while (!game.GameShouldClose()) {
    game.Tick(); 
  }
}

