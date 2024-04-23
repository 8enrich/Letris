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
  for (int y = 0; y < dimension; ++y){
    for (int x = 0; x < dimension; ++x) {
      bool cell = GetShapeRotation(x, y);
      if (cell) { board.DrawCell(boardPos + Vec2{x, y}, color);}
    }
  }
}

bool *Shape::GetShapeRotation(int x, int y) const{
  switch (currentRotation) {
    case Shape::Rotation::UP:
      return (bool*) shape_matrix[y * dimension + x];
    case Shape::Rotation::DOWN:
      return (bool*) shape_matrix[dimension * (dimension-1) - dimension * x + y];
    case Shape::Rotation::LEFT:
      return (bool*) shape_matrix[(dimension * dimension - 1) - dimension * y - x];
    case Shape::Rotation::RIGHT:
      return (bool*) shape_matrix[dimension-1 + dimension * x - y];
  }
  return (bool*) shape_matrix;
}

void Shape::updatePosition(Vec2<int> addVector){
  boardPos += addVector;
}

void Shape::fall(){
  moveDown();
}

void Shape::moveRight(){
  updatePosition(rightAddVector);
}

void Shape::moveLeft(){
  updatePosition(leftAddVector);
}

void Shape::moveDown(){
  updatePosition(downAddVector);
}

bool Shape::willFellOffTheBoard(){
  return getLowestYCell() + downAddVector.GetY() < board.GetHeight();
}

bool Shape::willEscapeRight(){
 return getRightestXCell() + rightAddVector.GetX() < board.GetWidth();
}

bool Shape::willEscapeLeft(){
  return getLeftestXCell() + leftAddVector.GetX() >= 0;
}

int Shape::getLowestYCell(){
  for (int y = dimension - 1; y >= 0; --y){
    for (int x = dimension - 1; x >= 0; --x) {
      bool cell = GetShapeRotation(x, y);
      if (cell) { return (boardPos + Vec2<int> {x, y}).GetY(); }
    }
  }
 return 0;
}

int Shape::getRightestXCell(){
  for (int x = dimension - 1; x >= 0; --x){
    for (int y = dimension - 1; y >= 0; --y) {
      bool cell = GetShapeRotation(x, y);
      if (cell) { return (boardPos + Vec2<int> {x, y}).GetX(); }
    }
  }
 return 0;
}

int Shape::getLeftestXCell(){
  for (int x = 0; x < dimension; ++x){
    for (int y = 0; y < dimension; ++y) {
      bool cell = GetShapeRotation(x, y);
      if (cell) { return (boardPos + Vec2<int> {x, y}).GetX(); }
    }
  }
 return 0;
}

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
