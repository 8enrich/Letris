#include "../include/Shape.hpp"

Shape::Shape(const bool* shape_matrix, int dimension, Color color, const Board& board) :
  shape_matrix(shape_matrix), 
  dimension(dimension), 
  color(color), 
  boardPos((board.GetWidth() - dimension)/2,0),
  board(board)
{}
Shape::Shape(const Shape &other):
  shape_matrix(other.shape_matrix), 
  dimension(other.dimension), 
  color(other.color), 
  boardPos(other.boardPos), 
  board(other.board)
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
void Shape::Draw() const {
  Color offColor = Color{color.r, color.g, color.b, 100};
  int distanceFromTheGround;
  for (int y = 0; y < dimension; ++y){
    for (int x = 0; x < dimension; ++x) {
      bool cell = GetShapeRotation(x, y);
      distanceFromTheGround = GetLowestDistanceFromTheGround();
      if (cell) {
        board.DrawCell(boardPos + Vec2{x, y}, color);
        board.DrawCell(boardPos + Vec2{x, y + distanceFromTheGround}, offColor);
      }
    }
  }
}

bool Shape::GetShapeRotation(int x, int y) const{
  switch (currentRotation) {
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

void Shape::InstantFall(){
  UpdatePosition(Vec2<int>{0, GetLowestDistanceFromTheGround()});
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
  Vec2<int> pos = {GetLeftestXCell(), GetLowestYCell()};
  int rightFirstCollision = GetFirstRightCollisionX(pos);
  int leftFirstCollision = GetFirstLeftCollisionX(pos);
  return rightFirstCollision - leftFirstCollision > dimension;
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
  while(!(board.CellExists(rightCollision)) && rightCollision.GetX() <= width);
  return rightCollision.GetX();
}

int Shape::GetDistanceFromTheGround(Vec2<int> pos) const{
  int factor = 1, height = board.GetHeight();
  Vec2<int> downCollision;
  do{ downCollision = pos + (downAddVector * factor++);}
  while(!(board.CellExists(downCollision)) && downCollision.GetY() < height);
  return ++factor;
}

int Shape::GetLowestDistanceFromTheGround() const{
  int lowest = board.GetHeight() + 1, distance;
  for(int x = 0; x < dimension; ++x){
    for(int y = 0; y < dimension; ++y){
      bool cell = GetShapeRotation(x, y);
      if(cell){
        Vec2<int> pos = boardPos + Vec2<int>{x, y};
        int distance = GetDistanceFromTheGround(pos);
        if(distance < lowest){ lowest = distance; }
      }
    }
  }
  return lowest - 3;
}

void Shape::MoveIfCollided(){
  if(WillCollideRight()){
    do{boardPos += leftAddVector;} while(WillCollideRight());
    boardPos += rightAddVector;
  }
  if(WillCollideLeft()){
    do{ boardPos += rightAddVector;} while(WillCollideLeft());
    boardPos += leftAddVector;
  }
}

bool Shape::HasCellRight(){
  bool cell;
  Vec2<int> pos;
  for(int x = dimension - 1; x >= dimension/2; --x){
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

void Shape::ResetBoardPos(){ boardPos = Vec2<int>{(board.GetWidth() - dimension)/2, 0}; }

void Shape::ResetRotation(){ currentRotation = Rotation(0); }

void Shape::Rotate(){
  currentRotation = Rotation((int(currentRotation) + 1) % 4);
}
I_Shape::I_Shape(const Board& board) : 
  Shape(shape_matrix, dimension, color, board)
{
  static_assert(sizeof(shape_matrix) / sizeof(bool) == dimension * dimension);
}
O_Shape::O_Shape(const Board& board) :
  Shape(shape_matrix, dimension, color, board)
{
  static_assert(sizeof(shape_matrix) / sizeof(bool) == dimension * dimension);
}
T_Shape::T_Shape(const Board& board) :
  Shape(shape_matrix, dimension, color, board)
{
  static_assert(sizeof(shape_matrix) / sizeof(bool) == dimension * dimension);
}
L_Shape::L_Shape(const Board& board) :
  Shape(shape_matrix, dimension, color, board)
{
  static_assert(sizeof(shape_matrix) / sizeof(bool) == dimension * dimension);
}
J_Shape::J_Shape(const Board& board) :
  Shape(shape_matrix, dimension, color, board)
{
  static_assert(sizeof(shape_matrix) / sizeof(bool) == dimension * dimension);
}
S_Shape::S_Shape(const Board& board) :
  Shape(shape_matrix, dimension, color, board)
{
  static_assert(sizeof(shape_matrix) / sizeof(bool) == dimension * dimension);
}
Z_Shape::Z_Shape(const Board& board) :
  Shape(shape_matrix, dimension, color, board)
{
  static_assert(sizeof(shape_matrix) / sizeof(bool) == dimension * dimension);
}
