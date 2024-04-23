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
  if (!(shape->willFellOffTheBoard())){
    Vec2<int> position_cells;
    int dimension = shape->GetDimension();
    for (int i = 0; i < dimension; i++){
      for (int j = 0; j < dimension; j++){
        bool cell = shape->GetShapeRotation(i, j);
        if(cell){
          position_cells = shape->GetBoardPos() + Vec2<int>{i, j};
          board.SetCell(position_cells, shape->GetColor());
        }
      }
    }
    Shape* next_shape = new O_Shape(board);
    shape = next_shape;
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
    if (IsKeyDown(KEY_D) && shape->willEscapeRight()){shape->moveRight();}
    if (IsKeyDown(KEY_A) && shape->willEscapeLeft()){ shape->moveLeft();}
    if (IsKeyDown(KEY_S) && shape->willFellOffTheBoard()){shape->moveDown();}
  }
  if(!(tickCount % 15)){/*Esse 15 é um número mágico por enquanto(só coloquei num valor razoável),
                      ele define a velocidade que a peça vai cair, com os níveis é suposto pra ela ir aumentando.
                      Acho que esse número pode até ficar em settings, mas ele não é constante justamente por causa
                      da dificudalde aumentar*/
    shape->fall();
  }
}
