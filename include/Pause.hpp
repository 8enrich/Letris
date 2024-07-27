#include <raylib.h>
#include "Screen.hpp"
#include "ScreenButton.hpp"
#include "ButtonManager.hpp"

class Pause : public Screen {
public:
  void Tick() override;
  Pause();
  ~Pause();
private:
  float x = (float)1/2, y = (float)1/2.5, fontSize = (float)1/20, lineDistance = (float)7/45;
  const std::vector<Button*> buttons = {
    new ScreenButton("Continue", Vec2<double>{x, y}, fontSize, GAME),
    new ScreenButton("Options", Vec2<double>{x, y + lineDistance}, fontSize, OPTIONS),
    new ScreenButton("Main Menu", Vec2<double>{x, y + 2 * lineDistance}, fontSize, MENU)
  };
  ButtonManager buttonManager = ButtonManager(buttons);

  void OptionsHandling();
  void Draw() override;
};
