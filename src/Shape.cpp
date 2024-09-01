#include "../include/Shape.hpp"
#include "raylib.h"
#include <new>

Shape::Shape(const bool* shape_matrix, int dimension, Color color, const Board& board, int index) :
  shape_matrix(shape_matrix),
  dimension(dimension),
  color(color),
  boardPos((board.GetWidth() - dimension)/2,0),
  board(board),
  index(index),
  currentRotation(Rotation::UP)
{
}

Shape::~Shape(){}

Shape::Shape(const Shape &other):
  shape_matrix(other.shape_matrix),
  dimension(other.dimension),
  color(other.color),
  boardPos(other.boardPos),
  board(other.board),
  index(other.index),
  currentRotation(other.currentRotation)
{}

Vec2<int> Shape::GetBoardPos() const{
  return boardPos;
}

Color Shape::GetColor() const{
  return color;
}

int Shape::GetDimension() const{
  return dimension;
}

int Shape::GetIndex() const{
  return index;
}

void Shape::Draw() const {
  Color offColor = Color{color.r, color.g, color.b, 90};
  int distanceFromTheGround;
  for (int y = 0; y < dimension; ++y){
    for (int x = 0; x < dimension; ++x) {
      bool cell = GetShapeRotation(x, y);
      if (cell) {
        distanceFromTheGround = GetDistanceUntilCollision(downAddVector);
        board.DrawCell(boardPos + Vec2<int>{x, y}, color);
        board.DrawOffCell(boardPos + Vec2<int>{x, y + distanceFromTheGround}, offColor);
      }
    }
  }
}


void Shape::DrawOutOfBoard(Vec2<double> pos) const{
  DrawOutOfBoard(pos, color);
}

void Shape::DrawOutOfBoard(Vec2<double> pos, Color c) const{
  for(int y = 0; y < dimension; ++y){
    for(int x = 0; x < dimension; ++x){
      bool cell = GetShapeRotation(x, y, Rotation::UP);
      if(cell) board.DrawCellAnyLocal(Vec2<double>(Vec2<int>{x, y}) - pos, c);
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
  int distance = GetDistanceUntilCollision(downAddVector);
  UpdatePosition(Vec2<int>{0, distance});
  return distance;
}

bool Shape::CheckCollision(Vec2<int> addVector) const{
  bool cell;
  Vec2<int> pos;
  for(int x = 0; x < dimension; x++){
    for(int y = 0; y < dimension; y++){
      cell = GetShapeRotation(x, y);
      if(cell){
        pos = Vec2<int>{x, y} + addVector;
        if(CheckCollisionCell(pos)) return true;
      }
    }
  }
  return false;
}

bool Shape::EscapeBoard(Vec2<int> pos) const{
  int posX = pos.GetX(), posY = pos.GetY();
  return posX < 0 || posX >= board.GetWidth() || posY >= board.GetHeight();
}

bool Shape::CheckCollisionCell(Vec2<int> pos) const{
  Vec2<int> finalPos = boardPos + pos;
  return board.CellExists(finalPos) || EscapeBoard(finalPos);
}

bool Shape::WillCollideRight() const{
  return CheckCollision(rightAddVector);
}

bool Shape::WillCollideLeft() const{
  return CheckCollision(leftAddVector);
}

bool Shape::WillCollideDown() const{
  return CheckCollision(downAddVector);
}

bool Shape::HasCollision() const{
  return CheckCollision({0, 0});
}

bool Shape::HasSpaceToRotate() const{
  Vec2<int> highestCell = GetHighestCell();
  return GetCollidedCellX(rightAddVector, highestCell) - GetCollidedCellX(leftAddVector, highestCell) > dimension;
}

int Shape::GetDistanceUntilCollision() const{
  return GetDistanceUntilCollision(downAddVector);
}

int Shape::GetDistanceUntilCollision(Vec2<int> addVector) const{
  int factor = 1;
  Vec2<int> pos;
  do{ pos = addVector * factor++;}
  while(!CheckCollision(pos));
  return factor - 2;
}

int Shape::GetCollidedCellX(Vec2<int> addVector, Vec2<int> cellPos) const{
  int factor = 1;
  Vec2<int> pos;
  do{ pos = cellPos + (addVector * factor++);}
  while(!CheckCollisionCell(pos));
  return pos.GetX();
}

void Shape::MoveIfCollided(){
  const Vec2<int> addVectors[3] = {upAddVector, rightAddVector, leftAddVector};
  int count = 0, height = board.GetHeight();
  while(HasCollision()){
    for(int i = 0; i < 3; i++){
      for(int j = 1; j <= 2; j++){
        if(!CheckCollision(addVectors[i] * j)){
          UpdatePosition(addVectors[i] * j);
          return;
        }
      }
    }
    UpdatePosition(upAddVector);
    if(count == height) break;
    count++;
  }
}

Vec2<int> Shape::GetHighestCell() const{
  for (int y = 0; y < dimension; y++){
    for (int x = 0; x < dimension; x++){
      bool cell = GetShapeRotation(x, y);
      if (cell) return Vec2<int>{x, y};
    }
  }
  return Vec2<int>{0, 0};
}

void Shape::ResetShape(float value){
  SetBoardPos(value);
  ResetRotation();
}

void Shape::ResetShape(){ ResetShape(1.0f/2); }

void Shape::SetBoardPos(float value){
  boardPos = Vec2<int>{(int)((board.GetWidth() - dimension) * value), 0};
}

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
