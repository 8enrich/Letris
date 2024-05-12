#include "../include/Board.hpp"
#include <assert.h>
#include <raylib.h>
#include <string>
#include <unordered_map>
Board::Cell::Cell() : doExists(false), c(WHITE) {}
void Board::Cell::Remove() { doExists = false; }
bool Board::Cell::Exists() const { return doExists;}
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
  if(x >= 0 && y >= 0 && x < width && y < height)
    GetCell(pos)->SetColor(c);
}
void Board::DrawCell(Vec2<int> pos) const{
  Color c = GetCell(pos)->GetColor();
  DrawCell(pos, c);
}

void Board::DrawCell(Vec2<int> pos, Color color) const {
  const int x = pos.GetX();
  const int y = pos.GetY();

  if(x >= 0 && x < width && y >= 0 && y < height){
    Vec2<int> topLeft = screenPos + padding + (pos * cellSize);
    ray_functions::DrawRectangle(topLeft, {cellSize - padding}, color);
    return;
  }
}

void Board::DrawOffCell(Vec2<int> pos, Color color) const {
  const int x = pos.GetX();
  const int y = pos.GetY();

  if(x >= 0 && x < width && y >= 0 && y < height){
    Vec2<int> topLeft = screenPos + padding + (pos * cellSize);
    ray_functions::DrawRectangleLinesEx(topLeft, {cellSize - padding}, padding, color);
    return;
  }
}

void Board::DrawCellAnyLocal(Vec2<double> pos, Color color) const {
  double doubleCellSize = (double) cellSize;
  Vec2<double> topLeft = Vec2<double>(screenPos) + padding + (pos * doubleCellSize);
  ray_functions::DrawRectangle(topLeft, Vec2<double>{doubleCellSize - padding}, color);
  return;
}

void Board::Draw() const {
  for (int iY = 0; iY < height; ++iY){
    for (int iX = 0; iX < width; ++iX){
      if(CellExists({iX, iY}))
        DrawCell({iX, iY});
    }
  }
  DrawBorder();
  DrawHold();
  DrawNext();
}

void Board::DrawBorder() const {
  ray_functions::DrawRectangleLinesEx(screenPos - (cellSize/2),
      Vec2{width*cellSize, height*cellSize} + cellSize, cellSize/2, RAYWHITE);
}

void Board::DrawHold() const{
  ray_functions::DrawText("Hold", screenPos - Vec2{cellSize*4, cellSize*2}, 20, RAYWHITE);
  ray_functions::DrawRectangleLinesEx(screenPos - Vec2{cellSize*6, cellSize/2},
      Vec2{cellSize*6, cellSize*4}, cellSize/2, RAYWHITE);
}

void Board::DrawNext() const{
  ray_functions::DrawText("Next",screenPos + Vec2{cellSize*12, -cellSize*2}, 20, RAYWHITE);
  ray_functions::DrawRectangleLinesEx(Vec2<double>(screenPos) + Vec2{cellSize*10.1, (double)(-cellSize/2)},
      Vec2{(double)cellSize*6, (double)cellSize*12}, cellSize/2, RAYWHITE);
}

void Board::DrawStats(int score, int level, int lines) const{
  std::unordered_map<std::string, int> mapa =
  {
    {"Lines", lines},
    {"Level", level},
    {"Score", score},
  };
  int i = 0;
  for(auto item = mapa.begin(); item != mapa.end(); i++, ++item){
    int y = 10 + i * 3;
    const char *numStr = TextFormat("%d", item->second);
    int textWidth = MeasureText(numStr, 20);
    double xPos = screenPos.GetX() - cellSize*3.5 + cellSize - (textWidth / 2);
    double yPos = screenPos.GetY() + (cellSize*(y + 1));
    ray_functions::DrawText((item->first).c_str(), screenPos - Vec2{cellSize*4, -(cellSize*y)}, 20, RAYWHITE);
    ray_functions::DrawText(numStr, Vec2{xPos,yPos}, 20, RAYWHITE);
  }
}


Color Board::GetCellColor(Vec2<int> pos){
  return GetCell(pos)->GetColor();
}

bool Board::CellExists(Vec2<int> pos) const {
  return GetCell(pos)->Exists();
}

void Board::RemoveCell(Vec2<int> pos){
  GetCell(pos)->Remove();
}

int Board::GetWidth() const {
  return width;
}

int Board::GetHeight() const {
  return height;
}

Board::Cell *Board::GetCell(Vec2<int> pos){
  return &cells[pos.GetY()*width + pos.GetX()];
}

const Board::Cell *Board::GetCell(Vec2<int> pos) const{
  return &cells[pos.GetY()*width + pos.GetX()];
}
