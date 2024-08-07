#pragma once
#include "raylibFunctions.hpp"
#include <vector>
#include "Vec2.hpp"
class Board{
private:
  class Cell{
    public:
      Cell();
      void SetColor(Color color);
      void Remove();
      bool Exists() const;
      Color GetColor() const;
    private:
      bool doExists;
      Color c;
  };
public:
  Board(Vec2<int> screenPos, Vec2<int> widthHeight, int cellSize, int padding);
  void SetCell(Vec2<int> pos, Color c);
  void DrawCell(Vec2<int> pos) const;
  void DrawCell(Vec2<int> pos, Color color) const;
  void DrawOffCell(Vec2<int> pos, Color color) const;
  void DrawCellAnyLocal(Vec2<double> pos, Color color) const;
  void Draw() const;
  void DrawBorder() const;
  void DrawHold() const;
  void DrawNext() const;
  void DrawStats(int, int, int) const;
  bool CellExists(Vec2<int> pos) const;
  int GetWidth() const;
  int GetHeight() const; 
  void RemoveCell(Vec2<int> pos);
  Color GetCellColor(Vec2<int> pos);
  void ResetBoardCells();
  void ResetBoardSettings();
private:
  std::vector<Cell> cells;
  const int width, height, padding;
  int cellSize;
  Vec2<int> screenPos;
  const Board::Cell *GetCell(Vec2<int>) const;
  Board::Cell *GetCell(Vec2<int>);
};
