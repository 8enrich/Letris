#include "../include/Game.hpp"

int main(){
  const int screenW = 800;
  const int screenH = 600;
  Game game {screenW, screenH,60, "Tetris"};
  while (!game.GameShouldClose()) {
    game.Tick(); 
  }
}

