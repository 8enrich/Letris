#pragma once
#include <string>
#include "Board.hpp"
#include "Shape.hpp"
class Game{
  public:

    Game(int width , int height,int fps, std::string title);	
    Game(const Game& other) = delete;
	  Game& operator=(const Game& other) = delete;
    ~Game() noexcept;
    bool GameShouldClose() const;
    void Tick();
  private:
    int tick;
    void Draw();
    void Update();

    Board board;
    J_Shape shape;
};
