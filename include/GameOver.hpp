#pragma once
#include <raylib.h>
#include <vector>
#include "Screen.hpp"
#include "ButtonManager.hpp"
#include "ScreenButton.hpp"

class GameOver : public Screen {
public:
  void Tick() override;
  GameOver();
  ~GameOver();
  void SetScore(int);
  void SetHighscores();
private:
  float fontSize = 1.0f/20;
  const std::vector<Button*> buttons = {
    new ScreenButton("Play Again", Vec2<double>{1.0f/4, 1/1.5}, fontSize, GAME),
    new ScreenButton("Options", Vec2<double>{1.0f/2, 1/1.5}, fontSize, OPTIONS),
    new ScreenButton("Main Menu", Vec2<double>{3.0f/4, 1/1.5}, fontSize, MENU)
  };
  ButtonManager buttonManager = ButtonManager(buttons);
  void OptionsHandling();
  void Draw() override;
  void DrawScores();
  bool hasNewHighscore = false;
  int score;
};
