#include "../include/Game.hpp"
#include <raylib.h>
#include <assert.h>
#include <cstdlib>
#include <time.h>

Game::Game(int width, int height, int fps, std::string title, Board board) :
  board(board) 
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

Shape *Game::newShape(){
  srand(time(NULL));
  return &shapes[rand()%7];
}

Shape *Game::nextShape(){
  shape = newShape();
  shape->resetBoardPos();
  shape->resetRotation();
  return shape;
}

void Game::UpdateShape(){
  if (shape->willCollideDown()){
    Vec2<int> position_cells;
    int dimension = shape->GetDimension();
    for (int x = 0; x < dimension; ++x){
      for (int y = 0; y < dimension; ++y){
        bool cell = shape->GetShapeRotation(x, y);
        if(cell){
          position_cells = shape->GetBoardPos() + Vec2<int>{x, y};
          board.SetCell(position_cells, shape->GetColor());
        }
      }
    }
    shape = nextShape();
  }
}

void Game::Draw(){
  ClearBackground(BLACK);
  board.Draw();
  shape->Draw();
}

void Game::Update(){
  if (!(tickCount%3)){
    if(IsKeyDown(KEY_W)) { shape->Rotate(); }
    if (!shape->willCollideRight() && IsKeyDown(KEY_D)){shape->moveRight();}
    if (!shape->willCollideLeft() && IsKeyDown(KEY_A)){ shape->moveLeft();}
    if (!shape->willCollideDown() && IsKeyDown(KEY_S)){shape->moveDown();}
  }
  if(!(tickCount % 15) && !shape->willCollideDown()){/*Esse 15 é um número mágico por enquanto(só coloquei num valor razoável),
                      ele define a velocidade que a peça vai cair, com os níveis é suposto pra ela ir aumentando.
                      Acho que esse número pode até ficar em settings, mas ele não é constante justamente por causa
                      da dificudalde aumentar*/
    shape->fall();
  }
}
