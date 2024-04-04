#include "../include/Game.hpp"
#include <raylib.h>
#include <assert.h>
Game::Game(int width, int height, std::string title){
  assert(!GetWindowHandle()); // Impede que sejam abertas duas janelas. caso ocorra, o programa fecha.
  InitWindow(width, height, title.c_str()); 
}

Game::~Game() noexcept{
  assert(GetWindowHandle()); // Impede que feche uma janela que não existe. caso ocorra, o programa fehca
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
  ClearBackground(RAYWHITE);
}

void Game::Update(){

}
