#include "../include/Game.hpp"
#include "../include/Settings.hpp"
int main(){
  auto board = Board(settings::boardPosition, settings::boardWidthHeight, settings::cellSize, settings::padding);
  Shape shape = J_Shape(board);
  Game game {settings::screenWidth, settings::screenHeight, settings::fps, "Letris", board, &shape};
  while (!game.GameShouldClose()) {
    game.Tick(); 
  }
}

