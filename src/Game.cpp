#include "../include/Game.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>
#include <assert.h>
Game::Game(int width, int height, int fps, std::string title) :
  board(settings::boardPosition, settings::boardWidthHeight, settings::cellSize, settings::padding),
  shape(board)
{
  assert(!GetWindowHandle()); // Impede que sejam abertas duas janelas. caso ocorra, o programa fecha.
  SetTargetFPS(fps);
  InitWindow(width, height, title.c_str());
  SetExitKey(KEY_ESCAPE);
  
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
  ClearBackground(BLACK);
  board.Draw();
  shape.Draw();
}

void Game::Update(){
  if (IsKeyPressed(KEY_W)){
    shape.Rotate();
  }
}
