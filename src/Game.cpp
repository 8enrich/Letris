#include "../include/Game.hpp"
#include "../include/raylibFunctions.hpp"
#include <cstdio>
#include <raylib.h>
#include <assert.h>
#include <cstdlib>

Game::Game(Board board) :
  board(board)
{
  shape = NewShape();
  SetNextShapes();
  hold = -1;
  canHold = true;
  score = 0;
  level = 0;
  speed = 15;
  cleanedLinesCount = 0;
}

bool Game::GameShouldClose() const{
  return shouldClose;
}

void Game::OpenCloseGame(){
  shouldClose = !shouldClose;
}
void Game::Tick(){
  BeginDrawing();
  Game::Update();
  Game::ClearLines();
  Game::Draw();
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
  board.DrawStats(score, level, cleanedLinesCount);
  if(hold >= 0) DrawHoldShape();
  DrawNextShapes();
  shape->Draw();
}

void Game::Update(){
  UpdateBoard();
  UpdateShape();
  UpdateLevel();
}

void Game::UpdateBoard(){
  if(!shape->WillCollideDown() && !(tickCount % speed)){ shape->Fall(); }
  auto keyPressed = GetKeyPressed();
  int fallen;
  switch(keyPressed){
    case KEY_SPACE:
      fallen = shape->InstantFall();
      UpdateScore(fallen);
      break;
    case KEY_W:
      if(shape->HasSpaceToRotate()){
        shape->Rotate();
        shape->MoveIfCollided();
      }
      break;
    case KEY_C:
      if(canHold){ Hold(); }
      break;
    case KEY_ESCAPE:
      shouldClose = true;
    default:
      break;
  }
  if (!(tickCount%3)){
    auto keyDown = ray_functions::GetKeyDown();
    switch(keyDown){
      case KEY_D:
        if (!shape->WillCollideRight()){shape->MoveRight();}
        break;
      case KEY_A:
        if (!shape->WillCollideLeft()) {shape->MoveLeft();}
        break;
      case KEY_S:
        if (!shape->WillCollideDown()){
          shape->MoveDown();
          UpdateScore(1);
        }
      default:
        break;
    }
  }
}

void Game::Hold(){
  canHold = false;
  int index = shape->GetIndex();
  if(hold >= 0){
    SwapShapeAndHold(index);
    shape->ResetShape();
    return;
  }
  hold = index;
  shape = NextShape();
}

void Game::SwapShapeAndHold(int index){
  shape = &shapes[hold];
  hold = index;
}

void Game::SetNextShapes(){
  for(int i = 0; i < 3; i++){ nextShapes[i] = NewShape()->GetIndex(); }
}

void Game::MoveNextShapes(){
  for(int i = 0; i < 3; i++){
    if(i + 1 != 3){
      nextShapes[i] = nextShapes[i + 1];
      continue;
    }
    nextShapes[i] = NewShape()->GetIndex();
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

void Game::DrawHoldShape(){
  int dimension = shapes[hold].GetDimension();
  shapes[hold].DrawOutOfBoard(Vec2<double>{((double)6 + dimension)/2, ((double)1/4) *
      (dimension * dimension) - ((double)5/4) * dimension + 1});
}

void Game::DrawNextShapes(){
  for(int i = 0; i < 3; i++){
    int dimension = shapes[nextShapes[i]].GetDimension();
    shapes[nextShapes[i]].DrawOutOfBoard(Vec2<double>{-((16.1 + 10.1 - dimension)/2), i * -4 + (((double)1/4) *
          (dimension * dimension) - ((double)5/4) * dimension + 1)});
  }
}
