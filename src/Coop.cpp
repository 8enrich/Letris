#include "../include/Coop.hpp"
#include "../include/raylibFunctions.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>

Coop::Coop(Board *board) :
  Game(board),
  i(I_Shape(*board)), o(O_Shape(*board)), t(T_Shape(*board)),
  j(J_Shape(*board)), l(L_Shape(*board)), s(S_Shape(*board)), z(Z_Shape(*board)),
  shapes2{ i, o, t, j, l, s, z }
{}

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
