#include "Button.hpp"
#include "ButtonManager.hpp"
#include "Screen.hpp"
#include "OptionsButton.hpp"
#include "ScreenButton.hpp"
#include "Settings.hpp"
#include <raylib.h>
#include <string>
#include <unordered_map>
#include <vector>

class CoopOptions : public Screen{
  public:
    CoopOptions();
    void Tick() override;
  private:
    void Draw() override;
    void CoopOptionsHandling();
    void ReadyButtonsHandling();
    void ControlButtonsHandling();
    void BgSelectorHandling();
    const float fontSize = 1.0f/30;
    const std::vector<std::string> optionsP1 = {"W A S D SPACE LSHIFT C", "S Z X C LSHIFT D F"};
    const std::vector<std::string> optionsP2 = {"^ < > v ENTER RCTRL RSHIFT", "I J K L N O P"};
    std::unordered_map<std::string, int> controlsIndexes = {
      {"W A S D SPACE LSHIFT C", 0},
      {"S Z X C LSHIFT D F", 6},
      {"^ < > v ENTER RCTRL RSHIFT", 5},
      {"I J K L N O P", 7}
    };
    const std::vector<std::string> readyStr = {"Not Ready", "Ready!"};
    const std::vector<std::string> imagesName = {"Calm river"};
    std::string selectedControlP1;
    std::string selectedControlP2;
    bool clicked[2] = {false, false};
    OptionsButton *controlP1 = nullptr;
    OptionsButton *controlP2 = nullptr;
    ScreenButton readyP1 = ScreenButton(readyStr[0], Vec2<double>{0.15, 1.0f/8}, fontSize, COOP);
    ScreenButton readyP2 = ScreenButton(readyStr[0], Vec2<double>{0.85, 1.0f/8}, fontSize, COOP);
    ScreenButton backgroundSelector = ScreenButton(Vec2<double>{0.37, 1.0f/2}, COOP,
                                                   settings::bgImagesNames[settings::coopBgImage], Vec2<double>{4, 8});
    const std::vector<Button*> readyButtons = { &readyP1, &readyP2 };
    std::vector<Button*> buttons;
    int bgImageIndex = 0;
    ButtonManager *buttonManager = nullptr;
};
