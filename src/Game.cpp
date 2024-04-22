#include "../include/Game.hpp"
#include <raylib.h>
#include <assert.h>
Game::Game(int width, int height, int fps, std::string title, Board board, Shape *shape) :
  board(board), 
  shape(shape)
{
  assert(!GetWindowHandle()); // Impede que sejam abertas duas janelas. caso ocorra, o programa fecha.
  SetTargetFPS(fps);
  InitWindow(width, height, title.c_str());
  SetExitKey(KEY_ESCAPE);
}

Game::~Game() noexcept{
  assert(GetWindowHandle()); // Impede que feche uma janela que não existe. caso ocorra, o programa fecha.
  CloseWindow();
}
bool Game::GameShouldClose() const{
  return WindowShouldClose();
}

void Game::Tick(){
  BeginDrawing();
  Game::Update();
  Game::UpdateShape();
  Game::Draw();
  EndDrawing();
  tickCount++;
}

void Game::UpdateShape(){
  if (!(shape->GetBoardPos().GetY() >= 0 && shape->GetBoardPos().GetY() < board.GetHeight())){
    for (int i = 0; i < shape->GetDimension(); i++){
      for (int j = 0; j < shape->GetDimension(); i++){
        board.SetCell(shape->GetBoardPos() +Vec2{i, j}, shape->GetColor());
      }
    }
    Shape tempshape = O_Shape(board);
    shape = &tempshape;
  }

}
void Game::Draw(){
  ClearBackground(BLACK);
  board.Draw();
  shape->Draw();
}

void Game::Update(){
  if (!(tickCount%3)){  
    if (IsKeyDown(KEY_W)) { shape->Rotate(); }
    if (IsKeyDown(KEY_D)) { shape->moveRight();}
    if (IsKeyDown(KEY_A)) { shape->moveLeft();}
    if (IsKeyDown(KEY_S)) { shape->moveDown();}
  }
  if(!(tickCount % 15)){/*Esse 15 é um número mágico por enquanto(só coloquei num valor razoável),
                      ele define a velocidade que a peça vai cair, com os níveis é suposto pra ela ir aumentando.
                      Acho que esse número pode até ficar em settings, mas ele não é constante justamente por causa
                      da dificudalde aumentar*/
    shape->fall();
  }
}
