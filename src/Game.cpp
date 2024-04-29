#include "../include/Game.hpp"
#include <cstdio>
#include <raylib.h>
#include <assert.h>
#include <cstdlib>
#include <time.h>

Game::Game(int width, int height, int fps, std::string title, Board board) :
  board(board) 
{
  assert(!GetWindowHandle());
  shape = NextShape();
  cleanedCount = 0;
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
  Game::CleanLines();
  Game::Draw();
  Game::DropLines();
  Game::DropLines();
  EndDrawing();
  tickCount++;
}

Shape *Game::NewShape(){
  return &shapes[GetRandomValue(0, 6)];
}

Shape *Game::NextShape(){
  shape = NewShape();
  shape->ResetBoardPos();
  shape->ResetRotation();
  return shape;
}
void Game::CleanLines(){
  int count = 0;
  for (int y = board.GetHeight(); y >= 0; y--){
    for (int x = board.GetWidth()-1; x >= 0; x--){
      if(board.CellExists({x, y})){ count++; }
    }
    if (count == board.GetWidth()){
      cleanedCount++;
      for (int x = board.GetWidth()-1; x >= 0; x--){ board.RemoveCell({x, y}); }
    }
    count = 0;
  }
}
void Game::DropLines() {
    if (cleanedCount) {
      for (int y = board.GetHeight() - 1; y >= 0; y--) {
        bool lineClean = true;
        for (int x = 0; x < board.GetWidth(); x++) {
          if (board.CellExists({x, y})) {
            lineClean = false;
            break;
          }
      }

        if (lineClean) {
          for (int i = y - cleanedCount; i >= 0; i--) {
            for (int x = 0; x < board.GetWidth(); x++) {
              if (board.CellExists({x, i})) {
                board.SetCell({x, i + cleanedCount}, board.GetCellColor({x, i}));
                board.RemoveCell({x, i});
              }
            }
          }
        }
    }
    cleanedCount = 0;
  }
}
void Game::UpdateShape(){
  if (shape->WillCollideDown()){
    Vec2<int> cellPosition;
    int dimension = shape->GetDimension();
    for (int x = 0; x < dimension; ++x){
      for (int y = 0; y < dimension; ++y){
        bool cell = shape->GetShapeRotation(x, y);
        if(cell){
          cellPosition = shape->GetBoardPos() + Vec2<int>{x, y};
          board.SetCell(cellPosition, shape->GetColor());
        }
      }
    }
    shape = NextShape();
  }
}

void Game::Draw(){
  ClearBackground(BLACK);
  board.Draw();
  shape->Draw();
}

void Game::Update(){
  if(!shape->WillCollideDown() && !(tickCount % 15)){/*Esse 15 é um número mágico por enquanto(só coloquei num valor razoável),
                      ele define a velocidade que a peça vai cair, com os níveis é suposto pra ela ir aumentando.
                      Acho que esse número pode até ficar em settings, mas ele não é constante justamente por causa
                      da dificudalde aumentar*/
    shape->Fall();
  }
  if(shape->HasSpaceToRotate() && IsKeyPressed(KEY_W)) {
    shape->Rotate();
    shape->MoveIfCollided();
  }
  if (!(tickCount%3)){
    if (!shape->WillCollideRight() && IsKeyDown(KEY_D)){shape->MoveRight();}
    if (!shape->WillCollideLeft() && IsKeyDown(KEY_A)){shape->MoveLeft();}
    if (!shape->WillCollideDown() && IsKeyDown(KEY_S)){shape->MoveDown();}
  }

}
