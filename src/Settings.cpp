#include "../include/Settings.hpp"

std::ifstream settings::f(std::string(ASSETS_PATH) + "user_settings.json"); 
json settings::db = json::parse(settings::f);
int settings::screenWidth = settings::db["WINDOW_WIDTH"];
int settings::screenHeight = settings::db["WINDOW_HEIGHT"];
Vec2<int> settings::boardPosition = {settings::db["BOARD_POSITION"][0], settings::db["BOARD_POSITION"][1]};
int settings::cellSize = settings::db["CELLSIZE"];
Vec2<int> settings::boardWidthHeight {settings::db["BOARD_RESOLUTION"][0], settings::db["BOARD_RESOLUTION"][1]};
int settings::volume = settings::db["VOLUME"];
std::vector<int> settings::highscores = settings::db["HIGHSCORES"];
void settings::UpdateWindowSize(Vec2<int> newSize) {
  screenWidth = newSize.GetX();
  screenHeight = newSize.GetY();
  db["WINDOW_WIDTH"] = screenWidth;
  db["WINDOW_HEIGHT"] = screenHeight;
  int centerX = GetMonitorWidth(0) / 2 - screenWidth / 2;
  int centerY = GetMonitorHeight(0) / 2 - screenHeight / 2;
  SetWindowPosition(centerX, centerY);
  SetWindowSize(screenWidth, screenHeight);
  UpdateBoardPosition();
}

void settings::UpdateBoardPosition(){
  boardPosition = {(int)((float)screenWidth/3.2), (int)(screenHeight/((float)60/7))};
  int y = boardPosition.GetY();
  cellSize = (int)(y * 0.33);
  db["BOARD_POSITION"] = {boardPosition.GetX(), boardPosition.GetY()};
  db["CELLSIZE"] = cellSize;
}
