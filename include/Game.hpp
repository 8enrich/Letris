#pragma once
#include "Board.hpp"
#include "Shape.hpp"
#include "Screen.hpp"
#include "ButtonManager.hpp"
#include "ScreenButton.hpp"
#include "Button.hpp" 

class Game : public Screen {
  public:
    Game(Board *board);
    void Tick() override;
    int GetScore();
  private:
    Shape *shape;
    Shape i, o, t, j, l, s, z;
  protected:
    int tickCount;
    void Draw() override;
    void Update();
    void UpdateBoard();
    void UpdateShape();
    Shape *NewShape();
    Shape *NextShape();
    void ClearLines();
    void DropLine(int);
    void DropLines();
    int cleanedLines[4] = {0,0,0,0};
    Board *board;
    void Hold();
    int hold;
    bool canHold;
    void SwapShapeAndHold(int);
    int nextShapes[3];
    void SetNextShapes();
    void MoveNextShapes();
    int score;
    void UpdateScore(int);
    void Score();
    int QuantityOfLines();
    int level;
    int speed;
    int cleanedLinesCount;
    void UpdateLevel();
    void DrawHoldShape();
    void DrawNextShapes();
    bool HasLost();
    int tickToFix;
    int maxTickToFix;
    Shape shapes[7];
    ScreenButton Pause = ScreenButton("Pause", Vec2<double>{1 / 1.1, 1.0f / 25}, 1.0f / 20, PAUSE);
    std::vector<Button*> buttons = { &Pause };
    ButtonManager buttonManager = ButtonManager(buttons);
};
