#include <raylib.h>
#include "Screen.hpp"
#include "ButtonManager.hpp"
#include "ScreenButton.hpp"

class Menu : public Screen {
public:
  void Tick() override;
  Menu();
  ~Menu();
private:
  void OptionsHandling();
  void Draw() override;
  Texture2D *logoTexture = nullptr;
  ScreenButton Solo = ScreenButton("Solo", Vec2<double>{1.0f / 8, 1.0f / 1.5}, 1.0f / 15, GAME, BLUE);
  ScreenButton Coop = ScreenButton("Coop", Vec2<double>{3.0f / 8, 1.0f /1.5}, 1.0f / 15, COOPOPTIONS, DARKGREEN);
  ScreenButton Options = ScreenButton("Options", Vec2<double>{5.0f / 8, 1.0f / 1.5}, 1.0f / 15, OPTIONS, DARKPURPLE);
  ScreenButton Quit = ScreenButton("Quit", Vec2<double>{7.0f / 8, 1.0f / 1.5}, 1.0f / 15, EXIT, RED);
  const std::vector<Button*> buttons = { &Solo, &Coop, &Options, &Quit };
  ButtonManager buttonManager = ButtonManager(buttons);
};
