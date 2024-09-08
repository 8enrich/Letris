#pragma once
#include "Vec2.hpp"
#include <raylib.h>
#include <fstream>
#include <unordered_map>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#ifndef ASSETS_PATH
#define ASSETS_PATH "./assets/"
#endif

namespace settings {
  extern std::ifstream f; 
  extern json db; 
  extern int screenWidth;
  extern int screenHeight;
  extern bool isWindowed;
  constexpr int fps = 30;
  extern int cellSize;
  constexpr int padding = 2;
  extern Vec2<int> boardPosition;
  extern Vec2<int> boardWidthHeight;
  extern int volume;
  extern std::vector<int> highscores;
  extern std::vector<int> highlevels;
  extern std::vector<std::vector<KeyboardKey>> controls;
  extern std::unordered_map<KeyboardKey, std::string> keyToString;
  constexpr Vec2<int> screenSizes[5] = {{1024, 576}, {1280, 720}, {1366, 768}, {1600, 900}, {1920, 1080}};
  const std::vector<std::string> bgImagesNames = {
    "bg0.png", "bg1.png", "bg2.png","bg3.png", 
  };
  extern std::vector<Texture2D*> bgImages;
  extern int soloBgImage;
  extern int coopBgImage;
  extern std::vector<int> coopControls;
  extern Sound hoveringSound, clearLineSound, moveShapeSound, gameOverSound, fixShapeSound;
  const std::vector<std::string> skinImageNames = {"skin0.png", "skin1.png", "skin2.png", "skin3.png"};
  extern std::vector<Texture2D*> skinImages;
  const std::vector<Color> recolors[7] = {
    {SKYBLUE, YELLOW, MAGENTA, DARKBLUE, ORANGE, GREEN, RED}, 
    {WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE},
    {Color{235, 151, 202, 255}, Color{199, 155, 235, 255}, Color{155, 188, 235, 255}, Color{150, 235, 228, 255}, Color{235, 235, 156, 255}, Color{200, 150, 230, 255}, Color{235, 199, 151, 255}},
    {Color{98,184,145,255}, Color{185,165,79,255}, Color{157,79,155,255}, Color{82,73,156,255}, Color{180,113,71,255}, Color{142,176,79,255}, Color{170,69,69,255}},
  };
  struct Skin{
    int image;
    int recolor;

    Skin(int image, int color){
      this->image = image;
      this->recolor = color;
    }
  };
  const std::vector<Skin> skins = {Skin(0, 0), Skin(1, 1), Skin(2, 0), Skin(2, 2), Skin(3, 3)};
  extern Skin skin;
  extern std::vector<Skin> coopSkins;
  extern int level;
  void UpdateWindowSize(Vec2<int>);
  void UpdateBoardPosition();
  void FullScreen();
  void SetSettings();
  void SetCustomControls();
  void SetTextures();
  void SetSkinTextures();
  void SetBgTextures();
  void SetSounds();
  void SetTexturesVec(std::vector<std::string> names, std::vector<Texture2D*> *images);
}

enum Screens {
  GAME,
  COOP,
  SOLOOPTIONS,
  COOPOPTIONS,
  OPTIONS,
  EXIT,
  MENU,
  PAUSE,
  GAMEOVER,
  STATS,
  NOTSCREEN,
};

enum Keys{
  ROTATECW = -7,
  LEFT,
  DOWN,
  RIGHT,
  INSTANTFALL,
  ROTATEACW,
  HOLD,
};
