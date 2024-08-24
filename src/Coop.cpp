#include "../include/Coop.hpp"
#include "../include/raylibFunctions.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>

Coop::Coop(Board *board) :
  Game(board),
  i(I_Shape(*board)), o(O_Shape(*board)), t(T_Shape(*board)),
  j(J_Shape(*board)), l(L_Shape(*board)), s(S_Shape(*board)), z(Z_Shape(*board)),
  shapes2{ i, o, t, j, l, s, z }
{
  shape2 = NewShape(shapes2);
  SetPlayersShapes();
  ResetShapes();
  tickToFix2 = maxTickToFix;
}

void Coop::Tick(){
  if(HasLost()){
    nextScreen = GAMEOVER;
    OpenClose();
    return;
  }
  if(IsMusicStreamPlaying(music)) {UpdateMusicStream(music);}
  BeginDrawing();
  Update();
  if(!HasLost()){
    ClearLines();
    Draw();
    Score();
    DropLines();
  }
  EndDrawing();
  tickCount++;
}

void Coop::SetPlayersShapes(){
  playersShapes[0] = &shape;
  playersShapes[1] = &shape2;
}

void Coop::Draw(){
  ClearBackground(BLACK);
  buttonManager.Tick();
  DrawBoard();
  for(int i = 0; i < 2; i++){
    (*playersShapes[i])->Draw();
  }
}

void Coop::ResetShapes(){
  for(int i = 0; i < 2; i++) ResetShape(i, (*playersShapes[i]));
}

void Coop::Update(){
  int index = (shape->GetDistanceUntilCollision() >= shape2->GetDistanceUntilCollision())? 0 : 1;
  for(int i = 0; i < 2; i++){
    UpdatePlayer(index);
    (*playersShapes[1 - index])->MoveIfCollided();
    index = 1 - index;
  }
}

void Coop::UpdatePlayer(int index){
  if(index){
    Game::Update(shape2, 4, &tickToFix2, shapes2);
    return;
  }
  Game::Update();
}

Shape *Coop::NextShape(Shape *vector){
  Shape *s = Game::NextShape(vector);
  int index = (&(vector[0]) == &(shapes2[0]))? 1 : 0;
  ResetShape(index, s);
  return s;
}

void Coop::ResetShape(int index, Shape*& s){
  float values[2] = {1.0f/4, 3.0f/4};
  s->ResetShape(values[index]);
}

void Coop::DrawNext() const{
  int boardSize = board->GetWidth();
  board->DrawText("P1",Vec2<double>{(double)3, (double)2}, 1.0f/30, RAYWHITE);
  Game::DrawNext(Vec2<double>{(double)-6, (double)-0.47});
  board->DrawText("P2",Vec2<double>{(double)-12, (double)2}, 1.0f/30, RAYWHITE);
  Game::DrawNext(Vec2<double>{(double)boardSize, (double)(-1.0f/2)});
} 

void Coop::DrawHold() const{
  Game::DrawHold(Vec2<double>{-12, -15}, Vec2<double>{10.1, 16.53});
} 
