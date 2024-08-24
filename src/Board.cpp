#include "../include/Board.hpp"
#include <assert.h>
#include <raylib.h>
#include <string>
#include <unordered_map>
#include <iostream>
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
    try {
        cells.resize(static_cast<size_t>(width) * static_cast<size_t>(height)); // Tenta redimensionar o vetor cells
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Erro ao redimensionar o vetor cells: " << e.what() << std::endl;
    }
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

void Board::DrawCell(Vec2<int> pos, Color color) const{
  const int x = pos.GetX();
  const int y = pos.GetY();

  if(x >= 0 && x < width && y >= 0 && y < height){
    Vec2<int> topLeft = screenPos + padding + (pos * cellSize);
    ray_functions::DrawRectangle(topLeft, {cellSize - padding}, color);
    return;
  }
}

void Board::DrawOffCell(Vec2<int> pos, Color color) const{
  const int x = pos.GetX();
  const int y = pos.GetY();

  if(x >= 0 && x < width && y >= 0 && y < height){
    Vec2<int> topLeft = screenPos + padding + (pos * cellSize);
    ray_functions::DrawRectangleLinesEx(topLeft, {cellSize - padding}, padding, color);
    return;
  }
}

void Board::DrawCellAnyLocal(Vec2<double> pos, Color color) const{
  double doubleCellSize = (double) cellSize;
  Vec2<double> topLeft = Vec2<double>(screenPos) + padding + (pos * doubleCellSize);
  ray_functions::DrawRectangle(topLeft, Vec2<double>{doubleCellSize - padding}, color);
  return;
}

void Board::Draw() const{
  DrawBorder();
  for (int iY = 0; iY < height; ++iY){
    for (int iX = 0; iX < width; ++iX){
      if(CellExists({iX, iY}))
        DrawCell({iX, iY});
    }
  }
}

void Board::DrawBorder() const{
  ray_functions::DrawRectangle(screenPos - (cellSize/2),
      Vec2<int>{width*cellSize, height*cellSize} + cellSize, BLACK);
  ray_functions::DrawRectangleLinesEx(screenPos - (cellSize/2),
      Vec2<int>{width*cellSize, height*cellSize} + cellSize, cellSize/2, RAYWHITE);
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

void Board::ResetBoardSettings(){
  cellSize = settings::cellSize;
  screenPos = settings::boardPosition;
}

void Board::ResetBoardCells(){
  for (int y = 0; y < height; y++){
    for (int x = 0; x < width; x++){
      if(CellExists({x, y})) RemoveCell({x, y});
    }
  }
}

Vec2<int> Board::GetScreenPos(){
  return screenPos;
}

int Board::GetCellsize(){
  return cellSize;
}
