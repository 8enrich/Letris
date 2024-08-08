#pragma once
#include "Board.hpp"
#include "Shape.hpp"
#include "Screen.hpp"
#include "ButtonManager.hpp"
#include "ScreenButton.hpp"
#include "Button.hpp"
#include "Game.hpp"

class Coop : public Game {
  public:
    Coop(Board *board);
    void Tick() override;
    int GetScore();
  private:
    //void Draw() override;
    Shape *shape;
    Shape i, o, t, j, l, s, z;
    Shape shapes2[7];
};
