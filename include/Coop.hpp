#pragma once
#include "Board.hpp"
#include "Shape.hpp"
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
    int nextShapes2[3];
    Shape *NextShape(Shape*, int*) override;
    void ResetShape(int,Shape*&);
    void UpdatePlayer(int);
    void DrawNext() const override;
    void DrawHold() const override;
    void DrawStats() const override;
    void DrawNextShapes() const override;
};
