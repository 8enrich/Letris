#include "../include/Coop.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>

Coop::Coop(Board *board) :
  Game(board, settings::coopBgImage, settings::db["COOPCONTROLS"][0]),
  i(I_Shape(*board)), o(O_Shape(*board)), t(T_Shape(*board)),
  j(J_Shape(*board)), l(L_Shape(*board)), s(S_Shape(*board)), 
  z(Z_Shape(*board)),
  shapes{i, o, t, j, l, s, z},
  player2(new Player(maxTickToFix, true, shapes, settings::db["COOPCONTROLS"][1]))
{
  player2->shape = NewShape(*(player2->shapes));
  SetPlayers();
  ResetShapes();
  SetNextShapes(player2);
}
void Coop::SetPlayers(){
  players[0] = player;
  players[1] = player2;
}

void Coop::Tick(){
  if(HasLost()){
    nextScreen = GAMEOVER;
    OpenClose();
    return;
  }
  if(IsMusicReady(music) && IsMusicStreamPlaying(music)) {UpdateMusicStream(music);}
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

void Coop::Draw(){
  ClearBackground(BLACK);
  float scale = (GetScreenWidth() * 1.2)/(float)backgroundTexture->width;
  DrawTextureEx(*backgroundTexture, Vector2{0, 0}, 0, scale, WHITE);
  buttonManager.Tick();
  DrawBoard();
  for(int i = 0; i < 2; i++){
    (players[i]->shape)->Draw();
  }
  board->DrawBorder();
  DrawNextShapes();
  if(hold >= 0) DrawHoldShape();  
}

void Coop::Update(){
  int index = ((player->shape)->GetDistanceUntilCollision() >= (player2->shape)->GetDistanceUntilCollision())? 0 : 1;
  for(int i = 0; i < 2; i++){
    UpdatePlayer(index);
    (players[1 - index]->shape)->MoveIfCollided();
    index = 1 - index;
  }
}

void Coop::UpdatePlayer(int index){
  if(index){
    Game::Update(player2);
    return;
  }
  Game::Update();
}

Shape *Coop::NextShape(Player* player){
  Shape *s = Game::NextShape(player);
  ResetShape(GetPlayerIndex(player), s);
  return s;
}

void Coop::ResetShapes(){
  for(int i = 0; i < 2; i++) ResetShape(i, players[i]->shape);
}

void Coop::ResetShape(int index, Shape*& s){
  s->ResetShape(positions[index]);
}

void Coop::ResetShape(Player *player){
  ResetShape(GetPlayerIndex(player), player->shape);
}

int Coop::GetPlayerIndex(Player *player){
  return (&(player->shapes) == &(player2->shapes))? 1 : 0;
}

void Coop::DrawNext() const{
  int boardSize = board->GetWidth();
  board->DrawText("P1",Vec2<double>{(double)3, (double)2.1}, 1.0f/30, RAYWHITE);
  Game::DrawNext(Vec2<double>{(double)-6, (double)-0.47});
  board->DrawText("P2",Vec2<double>{(double)-12, (double)2}, 1.0f/30, RAYWHITE);
  Game::DrawNext(Vec2<double>{(double)boardSize + 0.1, (double)(-1/2.1)});
} 

void Coop::DrawHold() const{
  Game::DrawHold(Vec2<double>{-12, -15}, Vec2<double>{10.1, 16.53});
}

void Coop::DrawStats() const{
  Game::DrawStats(12);
}

void Coop::DrawNextShapes() const{
  double boardSize = (double) board->GetWidth();
  Game::DrawNextShapes(player, -6);
  Game::DrawNextShapes(player2, (2*boardSize + 6));
}

void Coop::DrawHoldShape() const{
  double boardSize = (double) board->GetWidth();
  Game::DrawHoldShape(Vec2<double>{(double)-(2*boardSize + 6), (double)4.25}, player->canHold || player2->canHold);
}
