#include "../include/Game.hpp"

int main(){
  const int screenW = 800;
  const int screenH = 450;
  Game game {screenW, screenH, "Tetris"};
  while (!game.GameShouldClose()) {
    game.Tick(); 
  }
}

