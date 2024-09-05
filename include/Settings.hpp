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
  extern std::vector<Texture2D*> bgImages;
  extern int soloBgImage;
  extern int coopBgImage;
  extern std::vector<int> coopControls;
  extern Sound hoveringSound, clearLineSound, moveShapeSound, gameOverSound, fixShapeSound;
  const std::vector<std::string> skinImageNames = {"skin0.png", "skin1.png"};
  extern std::vector<Texture2D*> skinImages;
  const std::vector<Color> recolors[7] = {{WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE}};
  struct Skin{
    int image;
    int recolor;

    Skin(){}

    Skin(int image, int color){
      this->image = image;
      this->recolor = color;
    }
  };
  const std::vector<Skin> skins = {Skin(0, 0), Skin(1, 0)};
  extern Skin skin;
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
