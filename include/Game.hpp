#pragma once
#include <string>
#include "Board.hpp"
#include "Shape.hpp"
class Game{
  public:

    Game(int width , int height,int fps, std::string title, Board board, Shape* shape);	
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
    Board board;
    Shape *shape;
};
