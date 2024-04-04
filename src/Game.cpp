#include "../include/Game.hpp"
#include <raylib.h>
Game::Game(int width, int height, std::string title){
  InitWindow(width, height, title.c_str()); 
}

Game::~Game() noexcept{
  CloseWindow();
}
bool Game::GameShouldClose() const{
  return WindowShouldClose();
}

void Game::Tick(){
  BeginDrawing();
  Game::Update();
  Game::Draw();
  EndDrawing();
}

void Game::Draw(){

}

void Game::Update(){

}
