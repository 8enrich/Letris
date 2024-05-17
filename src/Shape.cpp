#include "../include/Shape.hpp"

Shape::Shape(const bool* shape_matrix, int dimension, Color color, const Board& board, int index) :
  shape_matrix(shape_matrix), 
  dimension(dimension), 
  color(color), 
  boardPos((board.GetWidth() - dimension)/2,0),
  board(board),
  index(index),
  currentRotation(Rotation::UP)
{}
Shape::Shape(const Shape &other):
  shape_matrix(other.shape_matrix), 
  dimension(other.dimension), 
  color(other.color), 
  boardPos(other.boardPos), 
  board(other.board),
  index(other.index),
  currentRotation(other.currentRotation)
{}

Vec2<int> Shape::GetBoardPos(){
  return boardPos;
}

Color Shape::GetColor(){
  return color;
}

int Shape::GetDimension(){
  return dimension;
}

int Shape::GetIndex(){
  return index;
}

void Shape::Draw() const {
  Color offColor = Color{color.r, color.g, color.b, 150};
  int distanceFromTheGround;
  for (int y = 0; y < dimension; ++y){
    for (int x = 0; x < dimension; ++x) {
      bool cell = GetShapeRotation(x, y);
      if (cell) {
        distanceFromTheGround = GetShortestDistanceFromTheGround();
        board.DrawCell(boardPos + Vec2<int>{x, y}, color);
        board.DrawOffCell(boardPos + Vec2<int>{x, y + distanceFromTheGround}, offColor);
      }
    }
  }
}

void Shape::DrawOutOfBoard(Vec2<double> pos){
  for(int y = 0; y < dimension; ++y){
    for(int x = 0; x < dimension; ++x){
      bool cell = GetShapeRotation(x, y, Rotation::UP);
      if(cell) board.DrawCellAnyLocal(Vec2<double>(Vec2<int>{x, y}) - pos, color);
    }
  }
}

bool Shape::GetShapeRotation(int x, int y, Rotation rotation) const{
  switch (rotation) {
    case Shape::Rotation::UP:
      break;
    case Shape::Rotation::DOWN:
      return shape_matrix[dimension * (dimension-1) - dimension * x + y];
    case Shape::Rotation::LEFT:
      return shape_matrix[(dimension * dimension - 1) - dimension * y - x];
    case Shape::Rotation::RIGHT:
      return shape_matrix[dimension-1 + dimension * x - y];
  }
  return shape_matrix[y * dimension + x];
}

bool Shape::GetShapeRotation(int x, int y) const{
  return GetShapeRotation(x, y, currentRotation);
}

void Shape::UpdatePosition(Vec2<int> addVector){
  boardPos += addVector;
}

void Shape::Fall(){
  MoveDown();
}

void Shape::MoveRight(){
  UpdatePosition(rightAddVector);
}

void Shape::MoveLeft(){
  UpdatePosition(leftAddVector);
}

void Shape::MoveDown(){
  UpdatePosition(downAddVector);
}

int Shape::InstantFall(){
  int shortestDistance = GetShortestDistanceFromTheGround();
  UpdatePosition(Vec2<int>{0, shortestDistance});
  return shortestDistance;
}

bool Shape::WillEscapeRight(){
 return GetRightestXCell() + rightAddVector.GetX() >= board.GetWidth();
}

bool Shape::WillEscapeLeft(){
  return GetLeftestXCell() + leftAddVector.GetX() < 0;
}

bool Shape::WillEscapeDown(){
  return GetLowestYCell() + downAddVector.GetY() >= board.GetHeight();
}

bool Shape::WillCollideRight(){
  return WillEscapeRight() || HasCellRight();
}

bool Shape::WillCollideLeft(){
  return WillEscapeLeft() || HasCellLeft();
}

bool Shape::WillCollideDown(){
  return WillEscapeDown() || HasCellDown();
}

bool Shape::HasSpaceToRotate(){
  int highestCell = GetHighestYCell();
  int rightFirstCollision = GetFirstRightCollisionX(Vec2<int>{GetRightestXCell(), highestCell});
  int leftFirstCollision = GetFirstLeftCollisionX(Vec2<int>{GetLeftestXCell(), highestCell});
  int difference = board.GetHeight() + dimension -
    GetShortestDistanceFromTheCeiling() + GetShortestDistanceFromTheGround();
  return rightFirstCollision - leftFirstCollision > dimension && difference > dimension;
}

int Shape::GetFirstLeftCollisionX(Vec2<int> pos){
  int factor = 1;
  Vec2<int> leftCollision;
  do{ leftCollision = pos + (leftAddVector * factor++);}
  while(!(board.CellExists(leftCollision)) && leftCollision.GetX() >= 0);
  return leftCollision.GetX();
}

int Shape::GetFirstRightCollisionX(Vec2<int> pos){
  int factor = 1, width = board.GetWidth();
  Vec2<int> rightCollision;
  do{ rightCollision = pos + (rightAddVector * factor++);}
  while(!(board.CellExists(rightCollision)) && rightCollision.GetX() < width);
  return rightCollision.GetX();
}

int Shape::GetDistanceFromTheGround(Vec2<int> pos) const{
  int factor = 1, height = board.GetHeight();
  Vec2<int> downCollision;
  do{ downCollision = pos + (downAddVector * factor++);}
  while(!(board.CellExists(downCollision)) && downCollision.GetY() < height);
  return factor;
}

int Shape::GetShortestDistanceFromTheGround() const{
  int shortest = board.GetHeight() + 1, distance;
  for(int x = 0; x < dimension; ++x){
    for(int y = 0; y < dimension; ++y){
      bool cell = GetShapeRotation(x, y);
      if(cell){
        Vec2<int> pos = boardPos + Vec2<int>{x, y};
        distance = GetDistanceFromTheGround(pos);
        if(distance < shortest){ shortest = distance; }
      }
    }
  }
  return shortest - 2;
}

int Shape::GetDistanceFromTheCeiling(Vec2<int> pos) const{
  int factor = 1;
  Vec2<int> upCollision;
  do{ upCollision = pos + (upAddVector * factor++);}
  while(!(board.CellExists(upCollision)) && upCollision.GetY() >= 0);
  return factor;
}

int Shape::GetShortestDistanceFromTheCeiling() const{
  int shortest = board.GetHeight(), distance;
  for(int x = 0; x < dimension; ++x){
    for(int y = 0; y < dimension; ++y){
      bool cell = GetShapeRotation(x, y);
      if(cell){
        Vec2<int> pos = boardPos + Vec2<int>{x, y};
        distance = GetDistanceFromTheCeiling(pos);
        if(distance < shortest){ shortest = distance; }
      }
    }
  }
  return shortest - 2;
}

void Shape::MoveIfCollided(){
  bool canContinue;
  int count = 0;
  do{
    canContinue = CheckIfCollided();
    count++;
    if(count == (dimension * dimension) * 10) break;
  } while(canContinue);
}

bool Shape::CheckIfCollided(){
  bool cell, collided = false;
  for(int y = 0; y < dimension; y++){
    for(int x = 0; x < dimension; x++){
      cell = GetShapeRotation(x, y);
      if (cell) if(!collided) collided = Move(x, y);
    }
  }
  return collided;
}

bool Shape::Move(int x, int y){
  bool collidedVertical, collidedHorizontal;
  Vec2<int> pos = Vec2<int>{x, y};
  collidedVertical = CollidedVertical(boardPos + pos);
  if(collidedVertical){
    if(y >= dimension/2 || GetLowestYCell() == (boardPos + pos).GetY()) UpdatePosition(upAddVector);
    if(y < dimension/2 || GetHighestYCell() == (boardPos + pos).GetY()) UpdatePosition(downAddVector);
  }
  collidedHorizontal = CollidedHorizontal(boardPos + pos);
  if(collidedHorizontal){
    if(x >= dimension/2) UpdatePosition(leftAddVector);
    if(x < dimension/2) UpdatePosition(rightAddVector);
  }
  return collidedHorizontal || collidedVertical;
}

bool Shape::CollidedHorizontal(Vec2<int> pos){
  int width = board.GetWidth(), posX = pos.GetX();
  return posX >= width || posX < 0 || board.CellExists(pos);
}

bool Shape::CollidedVertical(Vec2<int> pos){
  int height = board.GetHeight(), posY = pos.GetY();
  return pos.GetY() >= height || posY < 0 || board.CellExists(pos);
}

bool Shape::HasCellRight(){
  bool cell;
  Vec2<int> pos;
  for(int x = dimension - 1; x >= 0; --x){
    for(int y = dimension - 1; y >= 0; --y){
      cell = GetShapeRotation(x, y);
      pos = boardPos + Vec2<int>{x, y} + rightAddVector;
      if (cell && board.CellExists(pos)) {return true;}
    }
  }
  return false;
}

bool Shape::HasCellLeft(){
  bool cell;
  Vec2<int> pos;
  for(int x = 0; x < dimension; ++x){
    for(int y = 0; y < dimension; ++y){
      cell = GetShapeRotation(x, y);
      pos = boardPos + Vec2<int>{x, y} + leftAddVector;
      if (cell && board.CellExists(pos)) {return true;}
    }
  }
  return false;
}

bool Shape::HasCellDown(){
  bool cell;
  Vec2<int> pos;
  for(int y = dimension - 1; y >= 0; --y){
    for(int x = dimension - 1; x >= 0; --x) {
      cell = GetShapeRotation(x, y);
      pos = boardPos + Vec2<int>{x, y} + downAddVector;
      if (cell && board.CellExists(pos)) { return true; }
    }
  }
  return false;
}

bool Shape::HasCellUp(){
  bool cell;
  Vec2<int> pos;
  for(int y = 0; y < dimension; ++y){
    for(int x = 0; x < dimension; ++x){
      cell = GetShapeRotation(x, y);
      pos = boardPos + Vec2<int>{x ,y} + upAddVector;
      if(cell && board.CellExists(pos)){ return true; }
    }
  }
  return false;
}

int Shape::GetRightestXCell(){
  for (int x = dimension - 1; x >= 0; --x){
    for (int y = dimension - 1; y >= 0; --y) {
      bool cell = GetShapeRotation(x, y);
      if (cell) { return (boardPos + Vec2<int> {x, y}).GetX(); }
    }
  }
  return 0;
}

int Shape::GetLeftestXCell(){
  for (int x = 0; x < dimension; ++x){
    for (int y = 0; y < dimension; ++y) {
      bool cell = GetShapeRotation(x, y);
      if (cell) { return (boardPos + Vec2<int> {x, y}).GetX(); }
    }
  }
  return 0;
}

int Shape::GetLowestYCell(){
  for (int y = dimension - 1; y >= 0; --y){
    for (int x = dimension - 1; x >= 0; --x){
      bool cell = GetShapeRotation(x, y);
      if (cell) { return (boardPos + Vec2<int>{x, y}).GetY(); }
    }
  }
  return 0;
}

int Shape::GetHighestYCell(){
  for (int y = 0; y < dimension; ++y){
    for (int x = 0; x < dimension; ++x){
      bool cell = GetShapeRotation(x, y);
      if (cell) { return (boardPos + Vec2<int>{x, y}).GetY(); }
    }
  }
  return 0;
}

void Shape::ResetShape(){
  ResetBoardPos();
  ResetRotation();
}

void Shape::ResetBoardPos(){ boardPos = Vec2<int>{(board.GetWidth() - dimension)/2, 0}; }

void Shape::ResetRotation(){ currentRotation = Rotation(Rotation::UP); }

void Shape::Rotate(){
  currentRotation = Rotation((int(currentRotation) + 1) % 4);
}

void Shape::RotateAntiClockWise(){
  currentRotation = Rotation((int(currentRotation) + 7) % 4);
}

I_Shape::I_Shape(const Board& board) :
  Shape(shape_matrix, dimension, color, board, index)
{
  static_assert(sizeof(shape_matrix) / sizeof(bool) == dimension * dimension);
}
O_Shape::O_Shape(const Board& board) :
  Shape(shape_matrix, dimension, color, board, index)
{
  static_assert(sizeof(shape_matrix) / sizeof(bool) == dimension * dimension);
}
T_Shape::T_Shape(const Board& board) :
  Shape(shape_matrix, dimension, color, board, index)
{
  static_assert(sizeof(shape_matrix) / sizeof(bool) == dimension * dimension);
}
L_Shape::L_Shape(const Board& board) :
  Shape(shape_matrix, dimension, color, board, index)
{
  static_assert(sizeof(shape_matrix) / sizeof(bool) == dimension * dimension);
}
J_Shape::J_Shape(const Board& board) :
  Shape(shape_matrix, dimension, color, board, index)
{
  static_assert(sizeof(shape_matrix) / sizeof(bool) == dimension * dimension);
}
S_Shape::S_Shape(const Board& board) :
  Shape(shape_matrix, dimension, color, board, index)
{
  static_assert(sizeof(shape_matrix) / sizeof(bool) == dimension * dimension);
}
Z_Shape::Z_Shape(const Board& board) :
  Shape(shape_matrix, dimension, color, board, index)
{
  static_assert(sizeof(shape_matrix) / sizeof(bool) == dimension * dimension);
}
