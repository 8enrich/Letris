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
  board->Draw();
  for(int i = 0; i < 2; i++){
    (*playersShapes[i])->Draw();
  }
}

void Coop::ResetShapes(){
  float values[2] = {1.0f/4, 3.0f/4};
  for(int i = 0; i < 2; i++){
    (*playersShapes[i])->ResetShape(values[i]);
  }
}

void Coop::Update(){
  Game::Update();
  UpdateBoard(shape2, 0, &tickToFix2);
  UpdateShape(shape2, &tickToFix2);
}
