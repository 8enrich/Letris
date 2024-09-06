#pragma once
#include "Board.hpp"
#include "Shape.hpp"
#include "Game.hpp"

class Coop : public Game {
  public:
    Coop(Board *board);
    Coop(Board *board, int skin);
    void Tick() override;
  private:
    void Draw() override;
    Shape i, o, t, j, l, s, z;
    void Update() override;
    Shape *NextShape(Player*) override;
    void ResetShape(int,Shape*&);
    void ResetShape(Player*) override;
    void UpdatePlayer(int);
    void DrawNext() const override;
    void DrawHold() const override;
    void DrawStats() const override;
    void DrawNextShapes() const override;
    void SetPlayers();
    void ResetShapes();
    void DrawHoldShape() const;
    Shape shapes[7];
    Player *player2;
    Player *players[2];
    const float positions[2] = {1.0f/4, 3.0f/4};
    int GetPlayerIndex(Player*);
};
