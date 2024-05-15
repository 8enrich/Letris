#pragma once
#include "Vec2.hpp"
#include <raylib.h>
#include "Board.hpp"
class Shape {
public:
  enum class Rotation {
    UP,
    DOWN,
    LEFT,
    RIGHT
  };
  enum indexes{
    I_Shape,
    O_Shape,
    T_Shape,
    J_Shape,
    L_Shape,
    S_Shape,
    Z_Shape
  };
  Shape(const bool* shape_matrix, int dimension, Color color, const Board& board, const int index);
  Shape(const Shape& other);
	Shape& operator=(const Shape &other){return *this = Shape(other);}
  void Draw() const;
  void DrawOutOfBoard(Vec2<double>);
  void Rotate();
  void UpdatePosition(Vec2<int>);
  void Fall();
  void MoveRight();
  void MoveLeft();
  void MoveDown();
  int InstantFall();
  Vec2<int> GetBoardPos();
  int GetDimension();
  Color GetColor();
  int GetIndex();
  bool WillCollideDown();
  bool WillCollideRight();
  bool WillCollideLeft();
  bool GetShapeRotation(int,int) const;
  bool GetShapeRotation(int, int, Rotation) const;
  bool WillEscapeRight();
  bool WillEscapeLeft();
  bool WillEscapeDown();
  void ResetBoardPos();
  void ResetRotation();
  void MoveIfCollided();
  bool HasSpaceToRotate();
  void ResetShape();
  private:
  Vec2<int> boardPos;
  Rotation currentRotation;
  const bool* shape_matrix;
  const int dimension;
  const Color color;
  const Board& board;
  const int index;
  const Vec2<int> downAddVector = {0, 1};
  const Vec2<int> upAddVector = {0, -1};
  const Vec2<int> rightAddVector = {1, 0};
  const Vec2<int> leftAddVector = {-1, 0};
  int GetRightestXCell();
  int GetLeftestXCell();
  int GetLowestYCell();
  int GetHighestYCell();
  bool HasCellRight();
  bool HasCellLeft();
  bool HasCellDown();
  int GetFirstLeftCollisionX(Vec2<int>);
  int GetFirstRightCollisionX(Vec2<int>);
  int GetDistanceFromTheGround(Vec2<int>) const;
  int GetShortestDistanceFromTheGround() const;
  void Move(int, int);
  bool HasCollided(Vec2<int>);
};

class I_Shape : public Shape{
  public:
    I_Shape(const Board& board);
  private:
    static constexpr bool shape_matrix[] = {0, 0, 0, 0,
                                            1, 1, 1, 1,
                                            0, 0, 0, 0,
                                            0, 0, 0, 0};
    static constexpr int dimension = 4;
    static constexpr Color color = SKYBLUE;
    static constexpr int index = indexes::I_Shape;
};
  
class O_Shape : public Shape{
  public:
    O_Shape(const Board& board);
  private:
    static constexpr bool shape_matrix[] = {1, 1,
                                            1, 1};
    static constexpr int dimension = 2;
    static constexpr Color color = YELLOW;
    static constexpr int index = indexes::O_Shape;
};

class T_Shape : public Shape{
  public:
    T_Shape(const Board& board);
  private:
    static constexpr bool shape_matrix[] = {0, 1, 0, 
                                            1, 1, 1,
                                            0, 0, 0};
    static constexpr int dimension = 3;
    static constexpr Color color = MAGENTA;
    static constexpr int index = indexes::T_Shape;
};

class J_Shape : public Shape{
  public:
    J_Shape(const Board& board);
  private:
    static constexpr bool shape_matrix[] = {1, 0, 0, 
                                            1, 1, 1,
                                            0, 0, 0};
    static constexpr int dimension = 3;
    static constexpr Color color = DARKBLUE;
    static constexpr int index = indexes::J_Shape;
};

class L_Shape : public Shape{
  public:
    L_Shape(const Board& board);
  private:
    static constexpr bool shape_matrix[] = {0, 0, 1, 
                                            1, 1, 1,
                                            0, 0, 0};
    static constexpr int dimension = 3;
    static constexpr Color color = ORANGE;
    static constexpr int index = indexes::L_Shape;
};
class S_Shape : public Shape{
  public:
    S_Shape(const Board& board);
  private:
    static constexpr bool shape_matrix[] = {0, 1, 1, 
                                            1, 1, 0,
                                            0, 0, 0};
    static constexpr int dimension = 3;
    static constexpr Color color = GREEN;
    static constexpr int index = indexes::S_Shape;
};

class Z_Shape : public Shape {
  public:
    Z_Shape(const Board& board);
  private:
    static constexpr bool shape_matrix[] = {1, 1, 0, 
                                            0, 1, 1,
                                            0, 0, 0};
    static constexpr int dimension = 3;
    static constexpr Color color = RED;
    static constexpr int index = indexes::Z_Shape;
};
