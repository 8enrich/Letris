#pragma once
#include <string>
#include "Board.hpp"
class Game{
  public:
    Board board;
    Game(int width , int height,int fps, std::string title);	
    Game(const Game& other) = delete;
	  Game& operator=(const Game& other) = delete;
    ~Game() noexcept;
    bool GameShouldClose() const;
    void Tick();
  private:
    void Draw();
    void Update();
};
