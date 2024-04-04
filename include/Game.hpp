#pragma once
#include <string>
class Game{
  public:
    Game(int width , int height, std::string title);
    ~Game() noexcept;
    bool GameShouldClose() const;
    void Tick();
  private:
    void Draw();
    void Update();
};
