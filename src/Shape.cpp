#include "../include/Shape.hpp"

Shape::Shape(const bool* shape_matrix, int dimension, Color color, const Board& board) :
  shape_matrix(shape_matrix), 
  dimension(dimension), 
  color(color), 
  boardPos((board.GetWidth() - dimension)/2,0),
  board(board)
{}
Shape::Shape(const Shape& other):shape_matrix(other.shape_matrix), dimension(other.dimension), color(other.color), boardPos(other.boardPos), board(other.board){

}
void Shape::Draw() const {
  for (int y = 0; y < dimension; ++y){
    for (int x = 0; x < dimension; ++x) {
      bool cell = shape_matrix[y * dimension + x];
      switch (currentRotation) {
        case Shape::Rotation::UP:
          cell = shape_matrix[y * dimension + x];
          break;
        case Shape::Rotation::DOWN:
          cell = shape_matrix[dimension * (dimension-1) - dimension * x + y];
          break;
        case Shape::Rotation::LEFT:
          cell = shape_matrix[(dimension * dimension - 1) - dimension * y - x];
          break;
        case Shape::Rotation::RIGHT:
          cell = shape_matrix[dimension-1 + dimension * x - y];
          break;
      }
      if (cell) {
        board.DrawCell(boardPos + Vec2{x, y}, color);
      }
    }
  }
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
