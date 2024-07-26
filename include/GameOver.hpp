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
private:
  float x = (float)1/2, y = (float)1/2.5, fontSize = (float)1/20, lineDistance = (float)7/45;
  const std::vector<Button*> buttons = {
    new ScreenButton("Play Again", Vec2<double>{x, y}, fontSize, GAME),
    new ScreenButton("Options", Vec2<double>{x, y + lineDistance}, fontSize, OPTIONS),
    new ScreenButton("Back to Main Menu", Vec2<double>{x, y + 2 * lineDistance}, fontSize, MENU)
  };
  ButtonManager buttonManager = ButtonManager(buttons);
  void OptionsHandling();
  void Draw() override;
};
