#include "../include/Settings.hpp"

int settings::screenWidth = 800;
int settings::screenHeight = 600;
Vec2<int> settings::boardPosition = {250, 70};
int settings::cellSize = 23;

void settings::UpdateWindowSize(Vec2<int> newSize) {
  screenWidth = newSize.GetX();
  screenHeight = newSize.GetY();
  int centerX = GetMonitorWidth(0) / 2 - screenWidth / 2;
  int centerY = GetMonitorHeight(0) / 2 - screenHeight / 2;
  SetWindowSize(screenWidth, screenHeight);
  SetWindowPosition(centerX, centerY);
  UpdateBoardPosition();
}

void settings::UpdateBoardPosition(){
  boardPosition = {(int)((float)screenWidth/3.2), (int)(screenHeight/((float)60/7))};
  int x = boardPosition.GetX()/10, y = boardPosition.GetY();
  cellSize = (int)(y * 0.33);
}
