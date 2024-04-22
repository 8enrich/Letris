#pragma once
#include <string>
#include <vector>
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
    int tickCount;
    void Draw();
    void Update();

    std::vector<Vec2<int>> filling;
    Board board;
    Shape shape;
};
