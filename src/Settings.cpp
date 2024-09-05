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
std::vector<int> settings::highscores = settings::db["HIGHSCORES"];
std::vector<std::vector<KeyboardKey>> settings::controls = {
  {KEY_W, KEY_A, KEY_S, KEY_D, KEY_SPACE, KEY_LEFT_SHIFT, KEY_C},
  {KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_SPACE, KEY_Z, KEY_C},
  {KEY_I, KEY_J, KEY_K, KEY_L, KEY_SPACE, KEY_Z, KEY_C},
  {KEY_K, KEY_H, KEY_J, KEY_L, KEY_SPACE, KEY_Z, KEY_C},
  {KEY_W, KEY_A, KEY_S, KEY_D, KEY_SPACE, KEY_Z, KEY_C},
  {KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_ENTER, KEY_RIGHT_CONTROL, KEY_RIGHT_SHIFT},
  {KEY_S, KEY_Z, KEY_X, KEY_C, KEY_LEFT_SHIFT, KEY_D, KEY_F},
  {KEY_I, KEY_J, KEY_K, KEY_L, KEY_N, KEY_O, KEY_P}
};

std::vector<Texture2D*> settings::bgImages;

int settings::soloBgImage = db["SOLOBGIMAGE"]; 
int settings::coopBgImage = db["COOPBGIMAGE"];
std::vector<int> settings::coopControls = db["COOPCONTROLS"];

std::vector<Texture2D*> settings::skinImages;
settings::Skin settings::skin = skins[db["SKIN"]];
std::vector<settings::Skin> settings::coopSkins = {skins[db["COOPSKINS"][0]], skins[db["COOPSKINS"][1]]};

Sound settings::hoveringSound, 
      settings::clearLineSound, 
      settings::moveShapeSound, 
      settings::gameOverSound, 
      settings::fixShapeSound;

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
  if(cellSize < 23) cellSize = 23;
  db["BOARD_POSITION"] = {boardPosition.GetX(), boardPosition.GetY()};
  db["CELLSIZE"] = cellSize;
}

void settings::FullScreen(){
  int display = GetCurrentMonitor();
  settings::UpdateWindowSize(Vec2<int>{GetMonitorWidth(display), GetMonitorHeight(display)});
  ToggleBorderlessWindowed();
}

void settings::SetSettings(){
  SetCustomControls();
  SetTextures();
  SetSounds();
}

void settings::SetCustomControls(){
  for(int i = 0; i < 7; i++) settings::controls[4][i] = settings::db["CUSTOM_CONTROLS"][i];
}

void settings::SetTextures(){
  SetSkinTextures();
  SetBgTextures();
}

void settings::SetSkinTextures(){
  SetTexturesVec(skinImageNames, &skinImages);
}

void settings::SetBgTextures(){
  SetTexturesVec(bgImagesNames, &bgImages);
}

void settings::SetTexturesVec(std::vector<std::string> names, std::vector<Texture2D*> *images){
  for(int i = 0; i < names.size(); i++){
    images->push_back(new Texture2D(LoadTexture((std::string(ASSETS_PATH) + names[i]).c_str())));
  }
}

void settings::SetSounds(){
  hoveringSound = LoadSound((std::string(ASSETS_PATH)+"button.wav").c_str());
  clearLineSound = LoadSound((std::string(ASSETS_PATH)+ "clear.wav").c_str());
  moveShapeSound = LoadSound((std::string(ASSETS_PATH)+ "move.wav").c_str());
  gameOverSound = LoadSound((std::string(ASSETS_PATH)+"gameover.wav").c_str());
  fixShapeSound = LoadSound((std::string(ASSETS_PATH)+"fix.wav").c_str());
}

std::unordered_map<KeyboardKey, std::string> settings::keyToString = {
  { KEY_APOSTROPHE, "'" },
  { KEY_COMMA, "," },
  { KEY_MINUS, "-" },
  { KEY_PERIOD, "." },
  { KEY_SLASH, "/" },
  { KEY_ZERO, "0" },
  { KEY_ONE, "1" },
  { KEY_TWO, "2" },
  { KEY_THREE, "3" },
  { KEY_FOUR, "4" },
  { KEY_FIVE, "5" },
  { KEY_SIX, "6" },
  { KEY_SEVEN, "7" },
  { KEY_EIGHT, "8" },
  { KEY_NINE, "9" },
  { KEY_SEMICOLON, ";" },
  { KEY_EQUAL, "=" },
  { KEY_A, "A" },
  { KEY_B, "B" },
  { KEY_C, "C" },
  { KEY_D, "D" },
  { KEY_E, "E" },
  { KEY_F, "F" },
  { KEY_G, "G" },
  { KEY_H, "H" },
  { KEY_I, "I" },
  { KEY_J, "J" },
  { KEY_K, "K" },
  { KEY_L, "L" },
  { KEY_M, "M" },
  { KEY_N, "N" },
  { KEY_O, "O" },
  { KEY_P, "P" },
  { KEY_Q, "Q" },
  { KEY_R, "R" },
  { KEY_S, "S" },
  { KEY_T, "T" },
  { KEY_U, "U" },
  { KEY_V, "V" },
  { KEY_W, "W" },
  { KEY_X, "X" },
  { KEY_Y, "Y" },
  { KEY_Z, "Z" },
  { KEY_LEFT_BRACKET, "]" },
  { KEY_BACKSLASH, "\\" },
  { KEY_RIGHT_BRACKET, "[" },
  { KEY_GRAVE, "`" },
  { KEY_SPACE, "Space" },
  { KEY_ENTER, "Enter" },
  { KEY_TAB, "Tab" },
  { KEY_BACKSPACE, "Backspace" },
  { KEY_INSERT, "Insert" },
  { KEY_DELETE, "Delete" },
  { KEY_RIGHT, "Right" },
  { KEY_LEFT, "Left" },
  { KEY_DOWN, "Down" },
  { KEY_UP, "Up" },
  { KEY_PAGE_UP, "Page Up" },
  { KEY_PAGE_DOWN, "Page Down" },
  { KEY_HOME, "Home" },
  { KEY_END, "End" },
  { KEY_CAPS_LOCK, "Caps Lock" },
  { KEY_SCROLL_LOCK, "Scroll Lock" },
  { KEY_NUM_LOCK, "Num Lock" },
  { KEY_PRINT_SCREEN, "Print Screen" },
  { KEY_PAUSE, "Pause" },
  { KEY_F1, "F1" },
  { KEY_F2, "F2" },
  { KEY_F3, "F3" },
  { KEY_F4, "F4" },
  { KEY_F5, "F5" },
  { KEY_F6, "F6" },
  { KEY_F7, "F7" },
  { KEY_F8, "F8" },
  { KEY_F9, "F9" },
  { KEY_F10, "F10" },
  { KEY_F12, "F12" },
  { KEY_KP_0, "KP 0" },
  { KEY_KP_1, "KP 1" },
  { KEY_KP_2, "KP 2" },
  { KEY_KP_3, "KP 3" },
  { KEY_KP_4, "KP 4" },
  { KEY_KP_5, "KP 5" },
  { KEY_KP_6, "KP 6" },
  { KEY_KP_7, "KP 7" },
  { KEY_KP_8, "KP 8" },
  { KEY_KP_9, "KP 9" },
  { KEY_KP_DECIMAL, "KP Decimal" },
  { KEY_KP_DIVIDE, "KP /" },
  { KEY_KP_MULTIPLY, "KP *" },
  { KEY_KP_SUBTRACT, "KP -" },
  { KEY_KP_ADD, "KP +" },
  { KEY_KP_ENTER, "KP Enter" },
  { KEY_KP_EQUAL, "KP =" },
  { KEY_LEFT_SHIFT, "LShift" },
  { KEY_RIGHT_SHIFT, "RShift" },
  { KEY_LEFT_ALT, "LAlt" },
  { KEY_RIGHT_ALT, "RAlt" },
  { KEY_LEFT_CONTROL, "LCtrl" },
  { KEY_RIGHT_CONTROL, "RCtrl" }
};
