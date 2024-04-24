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
    Shape *newShape();
    Shape *nextShape();
    Board board;
    Shape *shape = newShape();
    Shape shapes[7] = {I_Shape(board),
                       O_Shape(board),
                       T_Shape(board),
                       J_Shape(board),
                       L_Shape(board),
                       S_Shape(board),
                       Z_Shape(board)};
};
