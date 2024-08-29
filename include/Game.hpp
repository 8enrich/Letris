#pragma once
#include "Board.hpp"
#include "Shape.hpp"
#include "Screen.hpp"
#include "ButtonManager.hpp"
#include "ScreenButton.hpp"
#include "Button.hpp"
#include "raylib.h"

class Game : public Screen {
  public:
    Game(Board *board);
    ~Game();
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
      bool canHold;
      int nextShapes[3];

      Player(int tickToFix, bool canHold, Shape *shapes) :
        tickToFix(tickToFix), canHold(canHold) 
      {
        this->shapes = new Shape*[7];
        for (int i = 0; i < 7; ++i) this->shapes[i] = &shapes[i];
      }
    };
    Texture2D *backgroundTexture = nullptr;
    int tickCount;
    int hold;
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
    void Hold(Player*);
    void SwapShapeAndHold(int,Player*);
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
    void DrawHoldShape() const;
    void DrawHoldShape(Vec2<double>,bool) const;
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
    virtual void ResetShape(Player*);
    void MoveIfKeyPressed(Player*,int);
    void MoveIfKeyDown(Player*,int);
};


