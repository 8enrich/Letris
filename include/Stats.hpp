#include <raylib.h>
#include "Screen.hpp"
#include "ScreenButton.hpp"
#include "ButtonManager.hpp"

class Stats : public Screen {
  public:
    Stats();
    ~Stats();
    void Tick() override;
    void OpenClose() override;
  private:
    void OptionsHandling();
    void Draw() override;
    const float fontSize = 1.0f/30;
    const std::vector<Button*> buttons = { &returnButton };
    ScreenButton returnButton;
    ButtonManager *buttonManager;
    Texture2D *bgImage = nullptr;
};
