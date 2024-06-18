#include <raylib.h>
#include "Screen.hpp"
#include "ScreenButton.hpp"
#include "ButtonManager.hpp"
#define OPT_QTD_PAUSE 3

class Pause : public Screen {
public:
  void Tick() override;
private:
  float x = (float)1/2, y = (float)1/2.5, fontSize = (float)1/20, lineDistance = (float)7/45;
  const std::vector<Button> buttons = {
    {ScreenButton("Continue", Vec2<double>{x, y}, fontSize, GAME)},
    {ScreenButton("Options", Vec2<double>{x, y + lineDistance}, fontSize, OPTIONS)},
    {ScreenButton("Back to Main Menu", Vec2<double>{x, y + 2 * lineDistance}, fontSize, MENU)}
  };
  ButtonManager buttonManager = ButtonManager(buttons, true);

  void OptionsHandling();
  int currentSelected = 0;
  Color optionsColor[OPT_QTD_PAUSE] = {RAYWHITE, GRAY, GRAY};
  void Draw() override;
};
