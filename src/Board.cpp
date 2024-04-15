#include "../include/Board.hpp"
#include <assert.h>
#include <raylib.h>
Board::Cell::Cell() : doExists(false), c(WHITE) {}

void Board::Cell::SetColor(Color color) {
  c = color;
  doExists = true;
}

Color Board::Cell::GetColor() const{
  return c;
}
Board::Board (Vec2<int> screenPos, Vec2<int> widthHeight, int cellSize, int padding) : 
    screenPos(screenPos), width(widthHeight.GetX()), height(widthHeight.GetY()), cellSize(cellSize), padding(padding) 
  {
    assert(width > 0 && height > 0);
    assert(cellSize > 0);
    cells.resize(width*height);
  }
  
void Board::SetCell(Vec2<int> pos, Color c){
  const int x = pos.GetX(); 
  const int y = pos.GetY();
  assert (x >= 0 && y >= 0 && x < width && y < height);
  cells[width*y + x].SetColor(c);
}
void Board::DrawCell(Vec2<int> pos) const{
  const int x = pos.GetX();
  const int y = pos.GetY();
  assert(x >= 0 && x < width && y >= 0 && y < height);
  Color c = cells[y * width + x].GetColor();
  Vec2<int> topLeft = screenPos + padding + (pos * cellSize);
  ray_wrapper::DrawRectangle(topLeft, {cellSize - padding}, c);
}

void Board::Draw() const {
  for (int iY = 0; iY < height; ++iY){
    for (int iX = 0; iX < width; ++iX){
      DrawCell({iX, iY});
    }
  }
  DrawBorder();

}

void Board::DrawBorder() const {
  ray_wrapper::DrawRectangleLinesEx(screenPos - (cellSize/2), 
      Vec2{width*cellSize, height*cellSize} + cellSize, cellSize/2, RAYWHITE);
}
