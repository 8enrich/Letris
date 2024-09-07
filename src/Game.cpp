#include "../include/Game.hpp"
#include "../include/raylibFunctions.hpp"
#include "../include/Settings.hpp"
#include <new>
#include <raylib.h>
#include <string>

Game::Game(Board *board) :
  Game(board, settings::db["SOLOBGIMAGE"], settings::db["CONTROL"], settings::db["SKIN"], settings::level)
{}

Game::Game(Board *board, int bgImage, int control, int skin, int level) :
  board(board), Screen(std::string(ASSETS_PATH)+"gameplay.mp3"),
  i(I_Shape(*board, skin)), o(O_Shape(*board, skin)), t(T_Shape(*board, skin)),
  j(J_Shape(*board, skin)), l(L_Shape(*board, skin)), s(S_Shape(*board, skin)), z(Z_Shape(*board, skin)),
  shapes{ i, o, t, j, l, s, z },
  hold(-1), score(0), level(level), cleanedLinesCount(0), maxTickToFix(30),                                                                                                          
  player(new Player(maxTickToFix, true, shapes, control, skin)),
  backgroundTexture(settings::bgImages[bgImage]),
  clearLineSound(settings::clearLineSound),
  moveShapeSound(settings::moveShapeSound),
  gameOverSound(settings::gameOverSound),
  fixShapeSound(settings::fixShapeSound)
{
  speed = SetSpeed();
  startLevel = level;
  if(!backgroundTexture) throw std::bad_alloc(); 
  board->ResetBoardCells();
  player->shape = NewShape();
  SetNextShapes();
}

Game::~Game() {
  UnloadTexture(*backgroundTexture);
  delete backgroundTexture;
  delete player;
}

int Game::SetSpeed(){
  int speed = 15;
  if(level <= 10) return speed -= level;
  speed -= 10;
  bool conditions[4] = {level >= 13, level >= 16, level >= 19, level == 29};
  for(int i = 0; i < 4; i++){
    if(conditions[i]) speed -= 1;
  }
  return speed;
}

void Game::Tick(){
  if(HasLost()){
    nextScreen = GAMEOVER;
    OpenClose();
    return;
  }
  if(IsMusicReady(music) && IsMusicStreamPlaying(music)) {UpdateMusicStream(music);}
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
    if(board->CellExists({x, 0})){ PlaySound(gameOverSound); return true;}
  }
  return false;
}

Shape *Game::NewShape(){
  return NewShape(*(player->shapes));
}

Shape *Game::NewShape(Shape *shapes){
  return &shapes[GetRandomValue(0, 6)];
}

Shape *Game::NextShape(Player *player){
  int next = player->nextShapes[0];
  MoveNextShapes(player);
  player->shapes[next]->ResetShape();
  return player->shapes[next];
}

void Game::ClearLines(){
  int width = board->GetWidth(), height = board->GetHeight(), index = 0;
  for (int y = 0; y < height; y++){
    for (int x = 0; x < width; x++){
      if(!board->CellExists({x, y})){ break; }
      if(x + 1 != width){ continue; }
      PlaySound(clearLineSound);
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

void Game::UpdateShape(Player *player){
  if ((player->shape)->WillCollideDown()){
    (player->tickToFix)--;
    if((player->tickToFix) > 0) return;
    FixShape(player);
    PlaySound(fixShapeSound);
    player->shape = NextShape(player);
    player->canHold = true;
  }
  if((player->tickToFix) > maxTickToFix || (player->tickToFix) <= 0) (player->tickToFix) = maxTickToFix;
  if((player->tickToFix) < maxTickToFix) (player->tickToFix)--;
}

void Game::FixShape(Player *player){
  Shape *s = player->shape;
  Vec2<int> cellPosition;
  int dimension = s->GetDimension();
  for (int x = 0; x < dimension; ++x){
    for (int y = 0; y < dimension; ++y){
      bool cell = s->GetShapeRotation(x, y);
      if(cell){
        cellPosition = s->GetBoardPos() + Vec2<int>{x, y};
        board->SetCell(cellPosition, s->GetColor(), player->skin);
      }
    }
  }
}

void Game::Draw(){
  ClearBackground(BLACK);
  ray_functions::DrawImage(backgroundTexture);
  buttonManager.Tick();
  DrawBoard();
  (player->shape)->Draw(player->skin);
  board->DrawBorder();
  if(hold >= 0) DrawHoldShape();
  DrawNextShapes();
  DrawPontuation(); 
}

void Game::DrawBoard(){
  DrawHold();
  DrawNext();
  DrawStats();
  board->Draw();
}

void Game::DrawPontuation(){
  const std::string points[4] = {"Single", "Double", "Triple", "Letris"};
  ray_functions::DrawFormatedText(points[pontuation].c_str(), Vec2<double>{0.80, 1.0f/2}, 1.0f/10, pontuationColor);
  ray_functions::DrawFormatedText(TextFormat("+ %d", scores[pontuation] * (level + 1)), Vec2<double>{0.80, 0.60}, 1.0f/10, pontuationColor);
  if(pontuationColor.a >= 5) pontuationColor.a -= 5;
}

void Game::Update(){
  Update(player);
}

void Game::Update(Player *player){
  UpdateBoard(player);
  UpdateShape(player);
  UpdateLevel();
  if(buttonManager.GetScreen() != NOTSCREEN) {
    nextScreen = buttonManager.GetScreen();
    buttonManager.ResetScreen();
    OpenClose();
  }
}

void Game::UpdateBoard(Player *player){
  if(!(player->shape)->WillCollideDown() && !(tickCount % speed)){ (player->shape)->Fall(); }
  MoveIfKeyPressed(player);
  if (!(tickCount%3)) MoveIfKeyDown(player);
}

void Game::MoveIfKeyPressed(Player *player){  
  auto keyPressed = ray_functions::GetAction(player->control);
  int fallen;
  switch(keyPressed){
    case INSTANTFALL:
      fallen = (player->shape)->InstantFall();
      UpdateScore(2 * fallen);
      (player->tickToFix) = 1;
      return;
    case ROTATECW:
      if((player->shape)->HasSpaceToRotate()){
        (player->shape)->Rotate();
        (player->shape)->MoveIfCollided();
        (player->tickToFix)++;
      }
      break;
    case ROTATEACW:
      if((player->shape)->HasSpaceToRotate()){
        (player->shape)->RotateAntiClockWise();
        (player->shape)->MoveIfCollided();
        (player->tickToFix)++;
      }
      break;
    case HOLD:
      if(player->canHold){ Hold(player); }
      break;
    case KEY_ESCAPE:
      nextScreen = PAUSE;
      OpenClose();
    default: break;
  }
}

void Game::MoveIfKeyDown(Player *player){
  auto keyDown = ray_functions::GetKeyDown(player->control);
  switch(keyDown){
    case RIGHT:
      if (!(player->shape)->WillCollideRight()){
        (player->shape)->MoveRight();
        (player->tickToFix)++;
        PlaySound(moveShapeSound);
      }
      break;
    case LEFT:
      if (!(player->shape)->WillCollideLeft()) {
        (player->shape)->MoveLeft();
        (player->tickToFix)++;
        PlaySound(moveShapeSound);
      }
      break;
    case DOWN:
      if (!(player->shape)->WillCollideDown()){
        (player->shape)->MoveDown();
        UpdateScore(1);
      }
    default: break;
  }
}

void Game::Hold(Player *player){
  player->canHold = false;
  player->tickToFix = maxTickToFix;
  int index = (player->shape)->GetIndex();
  if(hold >= 0){
    SwapShapeAndHold(index, player);
    ResetShape(player);
    return;
  }
  hold = index;
  player->shape = NextShape(player);
}

void Game::ResetShape(Player *player){
  (player->shape)->ResetShape();
}

void Game::SwapShapeAndHold(int index, Player *player){
  player->shape = player->shapes[hold];
  hold = index;
}

void Game::SetNextShapes(){
  SetNextShapes(player);
}

void Game::SetNextShapes(Player *player){
  for(int i = 0; i < 3; i++){ player->nextShapes[i] = NewShape(*(player->shapes))->GetIndex(); }
}

void Game::MoveNextShapes(Player *player){
  for(int i = 0; i < 3; i++){
    if(i + 1 != 3){
      player->nextShapes[i] = player->nextShapes[i + 1];
      continue;
    }
    player->nextShapes[i] = NewShape(*(player->shapes))->GetIndex();
  }
}

void Game::UpdateScore(int points){
  score += (points * (level + 1));
}

void Game::Score(){
  int lines = QuantityOfLines(), points;
  if(lines){
    pontuation = lines - 1;
    pontuationColor.a = 255;
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
  if(!startLevel){
    if(cleanedLinesCount >= 10 * (level + 1)){
      level++;
      if(level <= 10 || level == 13 || level == 16 || level == 19 || level == 29) speed--;
    }
    return;
  }
  bool conditions[2] = {cleanedLinesCount == 100, cleanedLinesCount == level * 10 - 50};
  int index = 0;
  if(100 < level * 10 - 50) index = 1; 
  if(cleanedLinesCount == level * 10 + 10 || conditions[index]){
    startLevel = 0;
    level++;
  }
}

void Game::DrawHoldShape() const{
  DrawHoldShape(Vec2<double>{(double)6, (double)0}, player->canHold);
}

void Game::DrawHoldShape(Vec2<double> pos, bool canHold) const{
  int dimension = player->shapes[hold]->GetDimension();
  double posX = pos.GetX(), posY = pos.GetY();
  Color c = LIGHTGRAY;
  if(canHold) c = player->shapes[hold]->GetColor();
  player->shapes[hold]->DrawOutOfBoard(Vec2<double>{(posX + dimension)/2, posY * -4 + ((double)1/4) *
      (dimension * dimension) - ((double)5/4) * dimension + 1}, c, player->skin);
}

void Game::DrawNextShapes() const{
  double boardSize = (double) board->GetWidth();
  DrawNextShapes(player, (2*boardSize + 6));
}

void Game::DrawNextShapes(Player *player, double posX) const{
  for(int i = 0; i < 3; i++){
    int dimension = player->shapes[player->nextShapes[i]]->GetDimension();
    player->shapes[player->nextShapes[i]]->DrawOutOfBoard(Vec2<double>{-(posX - dimension)/2, 
      i * -4 + (((double)1/4) * (dimension * dimension) - ((double)5/4) * dimension + 1)}, player->skin);
  }
}

int Game::GetScore(){
  return score;
}

int Game::GetLevel(){
  return level;
}

void Game::DrawHold() const{
  DrawHold(Vec2<double>{4, 2}, Vec2<double>{-6, -1/2.1});
}

void Game::DrawHold(Vec2<double> textPos, Vec2<double> rectPos) const{
  board->DrawText("Hold", textPos, 1.0f/30, RAYWHITE);
  board->DrawRectangle(rectPos, Vec2<double>{6, 4}, BLACK);
  board->DrawRectangleLinesEx(rectPos, Vec2<double>{6, 4}, 1.0f/2, RAYWHITE);
}

void Game::DrawNext() const{  
  int boardSize = board->GetWidth();	 
  board->DrawText("Next", Vec2<double>{(double)-(boardSize + 2), 2}, 1.0f/30, RAYWHITE);
  DrawNext(Vec2<double>{(double)boardSize + 0.1, (double)(-1/2.1)});	
}

void Game::DrawNext(Vec2<double> pos) const{
  board->DrawRectangle(pos, Vec2<double>{6, 12}, BLACK);
  board->DrawRectangleLinesEx(pos, Vec2<double>{(double)6, (double)12}, 1.0f/2, RAYWHITE);
}

void Game::DrawStats() const{
  DrawStats(10);
}

void Game::DrawStats(int firstValue) const{
  int lines = cleanedLinesCount;
  int screenHeight = settings::screenHeight;
  Vec2<int> screenPos = board->GetScreenPos();
  int cellSize = board->GetCellsize();
  std::unordered_map<std::string, int> mapa =
  {
    {"Lines", lines},
    {"Level", level},
    {"Score", score},
  };
  int i = 0, y, textWidth;
  const char *numStr;
  double xPos, yPos;
  for(auto item = mapa.begin(); item != mapa.end(); i++, ++item){
    y = firstValue + i * 3;
    numStr = TextFormat("%d", item->second);
    textWidth = MeasureText(numStr, screenHeight * 1/25);
    xPos = screenPos.GetX() - cellSize*4 + (double)(MeasureText(item->first.c_str(), screenHeight * 1/30) - textWidth)/2;
    yPos = screenPos.GetY() + (cellSize*(y + 1));
    ray_functions::DrawText((item->first).c_str(), screenPos - Vec2<int>{cellSize*4, -(cellSize*y)},
        screenHeight * 1/30, RAYWHITE);
    ray_functions::DrawText(numStr, Vec2<double>{xPos,yPos}, screenHeight * 1/25, RAYWHITE);
  }
}
