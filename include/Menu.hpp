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
  ScreenButton Solo = ScreenButton("Solo", Vec2<double>{2.0f / 10, 1.0f / 1.5}, 1.5f / 15, GAME, Color{11,229,248, 255});
  ScreenButton Coop = ScreenButton("Coop", Vec2<double>{3.8f / 10, 1.0f /1.5}, 1.5f / 15, COOPOPTIONS, Color{122,207,89,255});
  ScreenButton Options = ScreenButton("Options", Vec2<double>{5.9f / 10, 1.0f / 1.5}, 1.5f / 15, OPTIONS, Color{75, 6, 218, 255});
  ScreenButton Quit = ScreenButton("Quit", Vec2<double>{8.0f / 10, 1.0f / 1.5}, 1.5f / 15, EXIT, Color{229, 50, 60, 255});
  ScreenButton Stats = ScreenButton(Vec2<double>{1.0f/1.08, 1.0f/50}, STATS, "stats.png");
  const std::vector<Button*> buttons = { &Solo, &Coop, &Options, &Quit, &Stats };
  ButtonManager buttonManager = ButtonManager(buttons);
};
