#include "../include/Settings.hpp"
#include "raylib.h"
std::ifstream settings::f(std::string(ASSETS_PATH) + "user_settings.json"); 
json settings::db = json::parse(settings::f);
bool settings::isWindowed = settings::db["WINDOWED"];
int settings::screenWidth = settings::db["WINDOW_WIDTH"];// settings::isWindowed?settings::db["WINDOW_WIDTH"]:GetMonitorWidth(GetCurrentMonitor());
int settings::screenHeight = settings::db["WINDOW_HEIGHT"];//settings::isWindowed?settings::db["WINDOW_HEIGHT"]:GetMonitorHeight(GetCurrentMonitor());
Vec2<int> settings::boardPosition = {settings::db["BOARD_POSITION"][0], settings::db["BOARD_POSITION"][1]};
int settings::cellSize = settings::db["CELLSIZE"];
Vec2<int> settings::boardWidthHeight {settings::db["BOARD_RESOLUTION"][0], settings::db["BOARD_RESOLUTION"][1]};
int settings::volume = settings::db["VOLUME"];
void settings::UpdateWindowSize(Vec2<int> newSize) {
  screenWidth = newSize.GetX();
  screenHeight = newSize.GetY();
  db["WINDOW_WIDTH"] = screenWidth;
  db["WINDOW_HEIGHT"] = screenHeight;
  SetWindowSize(screenWidth, screenHeight);
  UpdateBoardPosition();
  if(db["WINDOWED"]){
    int display = GetCurrentMonitor();
    int centerX = (GetMonitorWidth(display) - screenWidth)/2;
    int centerY = (GetMonitorHeight(display) - screenHeight)/2;
    SetWindowPosition(centerX, centerY);
  }
}

void settings::UpdateBoardPosition(){
  boardPosition = {(int)((float)screenWidth/3.2), (int)(screenHeight/((float)60/7))};
  int y = boardPosition.GetY();
  cellSize = (int)(y * 0.33);
  db["BOARD_POSITION"] = {boardPosition.GetX(), boardPosition.GetY()};
  db["CELLSIZE"] = cellSize;
}

void settings::FullScreen(){
  int display = GetCurrentMonitor();
  screenWidth = GetMonitorWidth(display);
  screenHeight = GetMonitorHeight(display);
  db["WINDOW_WIDTH"] = screenWidth;
  db["WINDOW_HEIGHT"] = screenHeight;
  settings::UpdateWindowSize(Vec2<int>{GetMonitorWidth(display), GetMonitorHeight(display)});
  ToggleBorderlessWindowed();
}
