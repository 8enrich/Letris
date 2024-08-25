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
    Shape shapes[7];
  protected:
    struct Player{
      Shape *shape;
      Shape **shapes;
      int tickToFix;
      int hold;
      bool canHold;
      int nextShapes[3];

      Player(int tickToFix, int hold, bool canHold) :
        tickToFix(tickToFix), hold(hold), canHold(canHold) 
      {}
    };
    int tickCount;
    void CreatePlayerShapes();
    void CreatePlayerShapes(Player*, Shape*);
    void Draw() override;
    virtual void Update();
    void Update(Player*,int);
    void UpdateBoard(Player*,int);
    void UpdateShape(Player*);
    void UpdateShape(Shape*&,Shape*,int*);
    virtual Shape*NextShape(Player*);
    void FixShape(Shape*&);
    Shape *NewShape();
    Shape *NewShape(Shape*);
    void ClearLines();
    void DropLine(int);
    void DropLines();
    int cleanedLines[4] = {0,0,0,0};
    Board *board;
    void Hold();
    void SwapShapeAndHold(int);
    void SetNextShapes();
    void SetNextShapes(Player*);
    void MoveNextShapes(Player*);
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
    void DrawNextShapes(Player*,double) const;
    virtual void DrawNext() const;
    void DrawNext(Vec2<double>) const;
    virtual void DrawHold() const;
    void DrawHold(Vec2<double>,Vec2<double>) const;
    virtual void DrawStats() const;
    void DrawStats(int) const;
    void DrawBoard();
    bool HasLost();
    int maxTickToFix;
    ScreenButton Pause = ScreenButton("Pause", Vec2<double>{1 / 1.1, 1.0f / 25}, 1.0f / 20, PAUSE);
    std::vector<Button*> buttons = { &Pause };
    ButtonManager buttonManager = ButtonManager(buttons);
    Player *player;
};


