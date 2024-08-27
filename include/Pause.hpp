#include <raylib.h>
#include "Screen.hpp"
#include "ScreenButton.hpp"
#include "ButtonManager.hpp"

class Pause : public Screen {
public:
  void Tick() override;
  void OpenClose() override;
private:
  float x = (float)1/2, y = (float)1/2.5, fontSize = (float)1/20, lineDistance = (float)7/45;
  ScreenButton Continue = ScreenButton("Continue", Vec2<double>{x, y}, fontSize, GAME);
  ScreenButton Options = ScreenButton("Options", Vec2<double>{x, y + lineDistance}, fontSize, OPTIONS);
  ScreenButton MainMenu = ScreenButton("Main Menu", Vec2<double>{x, y + 2 * lineDistance}, fontSize, MENU);
  const std::vector<Button*> buttons = { &Continue, &Options, &MainMenu };
  ButtonManager buttonManager = ButtonManager(buttons);

  void OptionsHandling();
  void Draw() override;
};
