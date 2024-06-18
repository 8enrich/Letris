#include <raylib.h>
#include <vector>
#include "Screen.hpp"
#include "ButtonManager.hpp"
#include "ScreenButton.hpp"
#define OPT_QTD 3

class GameOver : public Screen {
public:
  void Tick() override;
private:
  float x = (float)1/2, y = (float)1/2.5, fontSize = (float)1/20, lineDistance = (float)7/45;
  const std::vector<Button> buttons = {
    {ScreenButton("Play Again", Vec2<double>{x, y}, fontSize, GAME)},
    {ScreenButton("Options", Vec2<double>{x, y + lineDistance}, fontSize, OPTIONS)},
    {ScreenButton("Back to Main Menu", Vec2<double>{x, y + 2 * lineDistance}, fontSize, MENU)}
  };
  ButtonManager buttonManager = ButtonManager(buttons, true);
  void OptionsHandling();
  int currentSelected = 0;
  Color optionsColor[OPT_QTD] = {RAYWHITE, GRAY, GRAY};
  void Draw() override;
};
