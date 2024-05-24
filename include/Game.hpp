#pragma once
#include "Board.hpp"
#include "Shape.hpp"
#include "Screen.hpp"

class Game : public Screen {
  public:
    Game(Board board);
    void Tick() override;
    static int control;
  private:
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
    Board board;
    Shape *shape;
    void Hold();
    int hold;
    bool canHold;
    int IndexOf(Shape*);
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
    Shape shapes[7] = {I_Shape(board),
                       O_Shape(board),
                       T_Shape(board),
                       J_Shape(board),
                       L_Shape(board),
                       S_Shape(board),
                       Z_Shape(board)};
};
