#include <raylib.h>
#include "Screen.hpp"
#include "ButtonManager.hpp"
#include "ScreenButton.hpp"

class Menu : public Screen {
public:
  void Tick() override;
private:
  void OptionsHandling();
  void Draw() override;
  const std::vector<Button> buttons = {
    {ScreenButton("Play", Vec2<double>{1.0f/4, 1.0f/1.5}, 1.0f/15, GAME)},
    {ScreenButton("Options", Vec2<double>{1.0f/2, 1.0f/1.5}, 1.0f/15, OPTIONS)},
    {ScreenButton("Quit", Vec2<double>{3.0f/4, 1.0f/1.5}, 1.0f/15, EXIT)}
  };
  ButtonManager buttonManager = ButtonManager(buttons, false);

};
