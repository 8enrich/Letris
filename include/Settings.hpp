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
  extern std::vector<std::vector<KeyboardKey>> controls;
  extern std::unordered_map<KeyboardKey, std::string> keyToString;
  constexpr Vec2<int> screenSizes[5] = {{1024, 576}, {1280, 720}, {1366, 768}, {1600, 900}, {1920, 1080}};
  const std::vector<std::string> bgImagesNames = {"relaxing-bg.png"};
  extern Texture2D skinTexture;
  extern std::vector<Texture2D*> bgImages;
  extern int soloBgImage;
  extern int coopBgImage;
  extern int p1Control;
  extern int p2Control;
  extern Sound hoveringSound;
  struct Skin{
    Texture2D *image;
    Color recolors;

    Skin(){}

    Skin(Texture2D *image, Color color){
      this->image = image;
      this->recolors = color;
    }
  };
  const std::vector<std::string> skinNames = {"skin0.png", "skin1.png"};
  extern std::vector<Skin> skins;
  void UpdateWindowSize(Vec2<int>);
  void UpdateBoardPosition();
  void FullScreen();
  void SetCustomControls();
  void SetTextures();
  void SetSkinTextures();
  void SetBgTextures();
  void SetSounds();
}

enum Screens {
  GAME,
  COOP,
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
