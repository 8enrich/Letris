#include "../include/Game.hpp"
#include "../include/Settings.hpp"
int main(){
  auto board = Board(settings::boardPosition, settings::boardWidthHeight, settings::cellSize, settings::padding);
  Game game {settings::screenWidth, settings::screenHeight, settings::fps, "Letris", board};
  while (!game.GameShouldClose()) {
    game.Tick(); 
  }
}

