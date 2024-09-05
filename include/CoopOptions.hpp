#include "Board.hpp"
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
    ~CoopOptions();
    void Tick() override;
  private:
    void Draw() override;
    void CoopOptionsHandling();
    void ReadyButtonsHandling();
    void ControlButtonsHandling();
    void BgSelectorHandling();
    void Close(Screens screen);
    const float fontSize = 1.0f/30;
    const std::vector<std::string> 
      controlOptions[2] = {
        {"W A S D SPACE LSHIFT C", "S Z X C LSHIFT D F"}, 
        {"^ < > v ENTER RCTRL RSHIFT", "I J K L N O P"}
      },
      readyStr = {"Not Ready", "Ready!"},
      imagesName = {
        "Calm river","Night forest", "Afternoon", "Gray smell"
      };
    std::unordered_map<std::string, int> controlsIndexes = {
      {"W A S D SPACE LSHIFT C", 0},
      {"S Z X C LSHIFT D F", 6},
      {"^ < > v ENTER RCTRL RSHIFT", 5},
      {"I J K L N O P", 7}
    };
    std::string selectedControls[2];
    bool clicked[2] = {false, false};
    OptionsButton *controlButtons[2] = {nullptr, nullptr};
    ScreenButton 
      readyButtons[2] = {
        ScreenButton(readyStr[0], Vec2<double>{0.15, 1.0f/8}, fontSize, COOP), 
        ScreenButton(readyStr[0], Vec2<double>{0.85, 1.0f/8}, fontSize, COOP)
      },
      backgroundSelector = ScreenButton(Vec2<double>{0.37, 1.0f/2}, COOP, settings::bgImagesNames[settings::coopBgImage], 
        Vec2<double>{4, 8});
    std::vector<Button*> buttons;
    ButtonManager *buttonManager = nullptr;
    int bgImageIndex = settings::coopBgImage, bgImagesSize = settings::bgImagesNames.size();
};
