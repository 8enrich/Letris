#include "../include/Game.hpp"
#include "../include/raylibFunctions.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>

Game::Game(Board *board) :
  board(board), Screen(std::string(ASSETS_PATH)+"tetris.mp3"),
  i(I_Shape(*board)), o(O_Shape(*board)), t(T_Shape(*board)),
  j(J_Shape(*board)), l(L_Shape(*board)), s(S_Shape(*board)), z(Z_Shape(*board)),
  shapes{ i, o, t, j, l, s, z }
{
  board->ResetBoardCells();
  shape = NewShape();
  SetNextShapes();
  hold = -1;
  canHold = true;
  score = 0;
  level = 0;
  speed = 15;
  cleanedLinesCount = 0;
  maxTickToFix = 30;
  tickToFix = maxTickToFix;
}

void Game::Tick(){
  if(HasLost()){
    nextScreen = GAMEOVER;
    OpenClose();
    return;
  }
  if(IsMusicStreamPlaying(music)) {UpdateMusicStream(music);}
  BeginDrawing();
  Game::Update();
  if(!HasLost()){
    Game::ClearLines();
    Game::Draw();
    Game::Score();
    Game::DropLines();
  }
  EndDrawing();
  tickCount++;
}

bool Game::HasLost(){
  for(int x = 0, width = board->GetWidth(); x < width; x++){
    if(board->CellExists({x, 0})){ return true; }
  }
  return false;
}

Shape *Game::NewShape(){
  return NewShape(shapes);
}

Shape *Game::NewShape(Shape *vector){
  return &vector[GetRandomValue(0, 6)];
}

Shape *Game::NextShape(Shape *vector){
  int next = nextShapes[0];
  MoveNextShapes(vector);
  vector[next].ResetShape();
  return &vector[next];
}

void Game::ClearLines(){
  int width = board->GetWidth(), height = board->GetHeight(), index = 0;
  for (int y = 0; y < height; y++){
    for (int x = 0; x < width; x++){
      if(!board->CellExists({x, y})){ break; }
      if(x + 1 != width){ continue; }
      for (int i = 0; i < width; i++){ board->RemoveCell({i, y}); }
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
  int width = board->GetWidth();
  bool haveCell;
  for (int y = line - 1; y > 0; y--) {
    haveCell = false;
    for (int x = 0; x < width; x++) {
      if (board->CellExists({x, y})){
        haveCell = true;
        board->SetCell({x, y + 1}, board->GetCellColor({x, y}));
        board->RemoveCell({x, y});
      }
    }
    if(!haveCell){ return; }
  }
}

void Game::UpdateShape(){
  UpdateShape(shape, &tickToFix, shapes);
}

void Game::UpdateShape(Shape*& s, int *tick, Shape *vector){
  if (s->WillCollideDown()){
    (*tick)--;
    if(*tick > 0) return;
    Vec2<int> cellPosition;
    int dimension = s->GetDimension();
    for (int x = 0; x < dimension; ++x){
      for (int y = 0; y < dimension; ++y){
        bool cell = s->GetShapeRotation(x, y);
        if(cell){
          cellPosition = s->GetBoardPos() + Vec2<int>{x, y};
          board->SetCell(cellPosition, s->GetColor());
        }
      }
    }
    s = NextShape(vector);
    canHold = true;
  }
  if(*tick > maxTickToFix || *tick <= 0) *tick = maxTickToFix;
  if(*tick < maxTickToFix) (*tick)--;
}

void Game::Draw(){
  ClearBackground(BLACK);
  buttonManager.Tick();
  board->Draw();
  board->DrawStats(score, level, cleanedLinesCount);
  if(hold >= 0) DrawHoldShape();
  DrawNextShapes();
  shape->Draw();
}

void Game::Update(){
  UpdateBoard();
  UpdateShape();
  UpdateLevel();
  if(buttonManager.GetScreen() != NOTSCREEN) {
    nextScreen = buttonManager.GetScreen();
    buttonManager.ResetScreen();
    OpenClose();
  }
}

void Game::UpdateBoard(){
  UpdateBoard(shape, settings::db["CONTROL"], &tickToFix);
}

void Game::UpdateBoard(Shape *s, int control, int *tick){
  if(!s->WillCollideDown() && !(tickCount % speed)){ s->Fall(); }
  auto keyPressed = ray_functions::GetAction(control);
  int fallen;
  switch(keyPressed){
    case INSTANTFALL:
      fallen = s->InstantFall();
      UpdateScore(2 * fallen);
      *tick = 1;
      return;
    case ROTATECW:
      if(s->HasSpaceToRotate()){
        s->Rotate();
        s->MoveIfCollided();
        (*tick)++;
      }
      break;
    case ROTATEACW:
      if(s->HasSpaceToRotate()){
        s->RotateAntiClockWise();
        s->MoveIfCollided();
        (*tick)++;
      }
      break;
    case KEY_C:
      if(canHold){ Hold(); }
      break;
    case KEY_ESCAPE:
      nextScreen = PAUSE;
      OpenClose();
    default:
      break;
  }
  if (!(tickCount%3)){
    auto keyDown = ray_functions::GetKeyDown(control);
    switch(keyDown){
      case RIGHT:
        if (!s->WillCollideRight()){
          s->MoveRight();
          (*tick)++;
        }
        break;
      case LEFT:
        if (!s->WillCollideLeft()) {
          s->MoveLeft();
          (*tick)++;
        }
        break;
      case DOWN:
        if (!s->WillCollideDown()){
          s->MoveDown();
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
  shape = NextShape(shapes);
}

void Game::SwapShapeAndHold(int index){
  shape = &shapes[hold];
  hold = index;
}

void Game::SetNextShapes(){
  for(int i = 0; i < 3; i++){ nextShapes[i] = NewShape()->GetIndex(); }
}

void Game::MoveNextShapes(Shape *vector){
  for(int i = 0; i < 3; i++){
    if(i + 1 != 3){
      nextShapes[i] = nextShapes[i + 1];
      continue;
    }
    nextShapes[i] = NewShape(vector)->GetIndex();
  }
}

void Game::UpdateScore(int points){
  score += (points * (level + 1));
}

void Game::Score(){
  int lines = QuantityOfLines(), points;
  if(lines){
    int scores[4] = {40, 100, 300, 1200};
    points = scores[lines - 1];
    cleanedLinesCount += lines;
    UpdateScore(points);
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
  if(cleanedLinesCount >= 10 * (level + 1) && level < 29){
    level++;
    if(level <= 10 || level == 13 || level == 16 || level == 19 || level == 29){
      speed--;
      maxTickToFix -= 2;
    }
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

int Game::GetScore(){
  return score;
}
