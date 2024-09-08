#pragma once
#include <raylib.h>
#include <vector>
#include "Screen.hpp"
#include "ButtonManager.hpp"
#include "ScreenButton.hpp"
#include "Settings.hpp"

class GameOver : public Screen {
public:
  void Tick() override;
  void SetScore(int);
  void SetLevel(int);
  void SetHighscores();
  void SetHighslevels();
  void OpenClose() override;
private:
  const float fontSize = 1.0f/20;
  ScreenButton PlayAgain = ScreenButton("Play Again", Vec2<double>{1.0f / 4, 1 / 1.5}, fontSize, GAME);
  ScreenButton Options = ScreenButton("Options", Vec2<double>{1.0f / 2, 1 / 1.5}, fontSize, OPTIONS);
  ScreenButton MainMenu = ScreenButton("Main Menu", Vec2<double>{3.0f / 4, 1 / 1.5}, fontSize, MENU);
  ScreenButton Stats = ScreenButton(Vec2<double>{1.0f/1.08, 1.0f/50}, STATS, settings::btnImages[0], Vec2<double>{25, 25});
  const std::vector<Button*> buttons = {&PlayAgain, &Options, &MainMenu, &Stats };
  ButtonManager buttonManager = ButtonManager(buttons);
  void OptionsHandling();
  void Draw() override;
  void DrawScores();
  bool hasNewHighscore = false;
  int score, level;
};
