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
  SetTargetFPS(fps);
  InitWindow(width, height, title.c_str());
  SetExitKey(KEY_ESCAPE);
  shape = NewShape();
  SetNextShapes();
  hold = -1;
  canHold = true;
  score = 0;
  level = 0;
  speed = 14;
  cleanedLinesCount = 0;
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
  Game::ClearLines();
  Game::Draw();
  Game::UpdateLevel();
  Game::Score();
  Game::DropLines();
  EndDrawing();
  tickCount++;
}

Shape *Game::NewShape(){
  return &shapes[GetRandomValue(0, 6)];
}

Shape *Game::NextShape(){
  shape = &shapes[nextShapes[0]];
  MoveNextShapes();
  shape->ResetShape();
  return shape;
}

void Game::ClearLines(){
  int width = board.GetWidth(), height = board.GetHeight(), index = 0;
  for (int y = 0; y < height; y++){
    for (int x = 0; x < width; x++){
      if(!board.CellExists({x, y})){ break; }
      if(x + 1 != width){ continue; }
      for (int i = 0; i < width; i++){ board.RemoveCell({i, y}); }
      cleanedLines[index++] = y;
    }
  }
}

void Game::DropLines(){
  for(int i = 0; i < 4; i++){
    DropLine(cleanedLines[i]);
    cleanedLines[i] = 0;
  }
}

void Game::DropLine(int line) {
  int width = board.GetWidth();
  bool haveCell;
  for (int y = line - 1; y > 0; y--) {
    haveCell = false;
    for (int x = 0; x < width; x++) {
      if (board.CellExists({x, y})){
        haveCell = true;
        board.SetCell({x, y + 1}, board.GetCellColor({x, y}));
        board.RemoveCell({x, y});
      }
    }
    if(!haveCell){ return; }
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
    canHold = true;
  }
}

void Game::Draw(){
  ClearBackground(BLACK);
  board.Draw();
  shape->Draw();
}

void Game::Update(){
  if(!shape->WillCollideDown() && !(tickCount % speed)){ shape->Fall(); }
  if(IsKeyPressed(KEY_SPACE)){
    int fallen = shape->InstantFall();
    UpdateScore(fallen);
  }
  if(shape->HasSpaceToRotate() && IsKeyPressed(KEY_W)) {
    shape->Rotate();
    shape->MoveIfCollided();
  }
  if(IsKeyPressed(KEY_C)){ Hold(); }
  if (!(tickCount%3)){
    if (!shape->WillCollideRight() && IsKeyDown(KEY_D)){shape->MoveRight();}
    if (!shape->WillCollideLeft() && IsKeyDown(KEY_A)){shape->MoveLeft();}
    if (!shape->WillCollideDown() && IsKeyDown(KEY_S)){
      shape->MoveDown();
      UpdateScore(1);
    }
  }
}

void Game::Hold(){
  if(canHold){
    canHold = false;
    int index = IndexOf(shape);
    if(hold >= 0){
      SwapShapeAndHold(index);
      shape->ResetShape();
      return;
    }
    hold = index;
    shape = NextShape();
  }
}

int Game::IndexOf(Shape *shapeToFind){
  int i;
  for(i = 0; i < 7; i++){ if(&shapes[i] == shapeToFind){ break; }}
  return i;
}

void Game::SwapShapeAndHold(int index){
  shape = &shapes[hold];
  hold = index;
}

void Game::SetNextShapes(){
  for(int i = 0; i < 3; i++){ nextShapes[i] = IndexOf(NewShape()); }
}

void Game::MoveNextShapes(){
  for(int i = 0; i < 3; i++){
    if(i + 1 == 3){
      nextShapes[i] = IndexOf(NewShape());
      break;
    }
    nextShapes[i] = nextShapes[i + 1];
  }
}

void Game::UpdateScore(int points){
  score += points;
}

void Game::Score(){
  int lines = QuantityOfLines(), points;
  if(lines){
    int scores[4] = {40, 100, 300, 1200};
    points = scores[lines - 1];
    cleanedLinesCount += lines;
    UpdateScore(points * (level + 1));
  }
}

int Game::QuantityOfLines(){
  int lines = 0;
  for(int i = 0; i < 4; i++){
    if(cleanedLines[i] == 0){ break; }
    lines++;
  }
  return lines;
}

void Game::UpdateLevel(){
  if(cleanedLinesCount >= 10 * (level + 1)){
    level++;
    if(level <= 10 || level == 13 || level == 16 || level == 19 || level == 29){ speed--;}
  }
}
