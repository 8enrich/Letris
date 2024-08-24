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
  private:
    void Draw() override;
    Shape *shape2;
    Shape i, o, t, j, l, s, z;
    Shape shapes2[7];
    Shape **playersShapes[2];
    void SetPlayersShapes();
    void ResetShapes();
    void Update() override;
    int tickToFix2;
    Shape *NextShape(Shape*) override;
    void ResetShape(int,Shape*&);
    void UpdatePlayer(int);
    void DrawNext(int,Vec2<int>,int) const override;
    void DrawHold(int,Vec2<int>,int) const override;
};
