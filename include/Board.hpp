#pragma once
#include "raylibWrapper.hpp"
#include <vector>
#include "Vec2.hpp"
class Board{
private:
  class Cell{
    public:
      Cell();  
      void SetColor(Color color);
      void Remove();
      Color GetColor() const;
    private:
      bool doExists;
      Color c;
  };
public:
  Board(Vec2<int> screenPos, Vec2<int> widthHeight, int cellSize, int padding);
  void SetCell(Vec2<int> pos, Color c);
  void DrawCell(Vec2<int> pos) const;
  void Draw() const;
  void DrawBorder() const;

private:
  std::vector<Cell> cells;
  const int width, height, cellSize, padding;
  Vec2<int> screenPos;
};
