#pragma once
#include <string>
#include "Board.hpp"
#include "Shape.hpp"
class Game{
  public:
    Game(int width , int height,int fps, std::string title, Board board);
    Game(const Game& other) = delete;
	  Game& operator=(const Game& other) = delete;
    ~Game() noexcept;
    bool GameShouldClose() const;
    void Tick();
  private:
    int tickCount;
    void Draw();
    void Update();
    void UpdateShape();
    Shape *NewShape();
    Shape *NextShape();
    void ClearLines();
    void DropLine(int);
    void DropLines();
    int cleanedLines[4] = {0,0,0,0};
    Board board;
    Shape *shape;
    void Hold();
    int hold;
    bool canHold;
    int IndexOfShape();
    void SwapShapeAndHold(int);
    Shape shapes[7] = {I_Shape(board),
                       O_Shape(board),
                       T_Shape(board),
                       J_Shape(board),
                       L_Shape(board),
                       S_Shape(board),
                       Z_Shape(board)};
};
