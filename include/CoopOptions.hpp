#include "Button.hpp"
#include "ButtonManager.hpp"
#include "Screen.hpp"
#include "OptionsButton.hpp"
#include "ScreenButton.hpp"
#include <raylib.h>
#include <string>
#include <vector>

class CoopOptions : public Screen{
  public:
    void Tick() override;
  private:
    void Draw() override;
    void CoopOptionsHandling();
    const float fontSize = 1.0f/30;
    const std::vector<std::string> optionsP1 = {"W A S D SPACE LSHIFT C", "Test"};
    const std::vector<std::string> optionsP2 = {"^ < > v ENTER RCTRL RSHIFT", "Test"};
    std::vector<std::string> readyStr = {"Not Ready", "Ready!"};
    bool clicked[2] = {false, false};
    OptionsButton controlP1 = OptionsButton(optionsP1[0], Vec2<double>{1.0f/4, 1/1.5}, fontSize, optionsP1);
    OptionsButton controlP2 = OptionsButton(optionsP2[0], Vec2<double>{3.0f/4, 1/1.5}, fontSize, optionsP2);
    ScreenButton readyP1 = ScreenButton(readyStr[0], Vec2<double>{1.0f/4, 1.0f/8}, fontSize, COOP);
    ScreenButton readyP2 = ScreenButton(readyStr[0], Vec2<double>{3.0f/4, 1.0f/8}, fontSize, COOP);
    const std::vector<Button*> readyButtons = { &readyP1, &readyP2 };
    const std::vector<Button*> buttons = {&readyP1, &readyP2, &controlP1, &controlP2};
    ButtonManager buttonManager = ButtonManager(buttons);
    int tickCount = 0;
};
