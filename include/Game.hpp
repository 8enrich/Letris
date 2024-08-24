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
    Shape i, o, t, j, l, s, z;
  protected:
    int tickCount;
    void Draw() override;
    virtual void Update();
    void Update(Shape*&,int,int*,Shape*,int*);
    void UpdateBoard(Shape*,int, int*);
    void UpdateShape(Shape*&, int*, Shape*,int*);
    void UpdateShape(Shape*&,Shape*,int*);
    virtual Shape*NextShape(Shape*,int*);
    void FixShape(Shape*&);
    Shape *NewShape();
    Shape *NewShape(Shape*);
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
    void SetNextShapes(int*,Shape*);
    void MoveNextShapes(Shape*, int*);
    int score;
    void UpdateScore(int);
    void Score();
    int QuantityOfLines();
    int level;
    int speed;
    int cleanedLinesCount;
    void UpdateLevel();
    void DrawHoldShape();
    virtual void DrawNextShapes() const;
    void DrawNextShapes(const Shape*,double, const int*) const;
    virtual void DrawNext() const;
    void DrawNext(Vec2<double>) const;
    virtual void DrawHold() const;
    void DrawHold(Vec2<double>,Vec2<double>) const;
    virtual void DrawStats() const;
    void DrawStats(int) const;
    void DrawBoard();
    bool HasLost();
    int tickToFix;
    int maxTickToFix;
    Shape *shape;
    Shape shapes[7];
    ScreenButton Pause = ScreenButton("Pause", Vec2<double>{1 / 1.1, 1.0f / 25}, 1.0f / 20, PAUSE);
    std::vector<Button*> buttons = { &Pause };
    ButtonManager buttonManager = ButtonManager(buttons);
};
