#pragma once
#include "Vec2.hpp"
#include "raylibWrapper.hpp"
#include <raylib.h>
#include "Board.hpp"
class Shape {
public:
  enum class Rotation {
    UP,
    RIGHT,
    DOWN,
    LEFT
  };
  Shape(const bool* shape_matrix, int dimension, Color color, const Board& board);
  Shape(const Shape& other);
  void Draw() const;
  void Rotate();
  void updatePosition(Vec2<int>);
  void fall();
  void moveRight();
  void moveLeft();
  void moveDown();
private:
  Vec2<int> boardPos;
  Rotation currentRotation;
  const bool* shape_matrix;
  const int dimension;
  const Color color;
  const Board& board;
  const Vec2<int> downAddVector = {0, 1};
  const Vec2<int> rightAddVector = {1, 0};
  const Vec2<int> leftAddVector = {-1, 0};
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
};
  
class O_Shape : public Shape{
  public:
    O_Shape(const Board& board);
  private:
    static constexpr bool shape_matrix[] = {1, 1,
                                            1, 1};
    static constexpr int dimension = 2;
    static constexpr Color color = YELLOW;
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
};


