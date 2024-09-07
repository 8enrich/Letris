#include "Board.hpp"
#include "Button.hpp"
#include "ButtonManager.hpp"
#include "Screen.hpp"
#include "OptionsButton.hpp"
#include "ScreenButton.hpp"
#include "Settings.hpp"
#include "Shape.hpp"
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
    bool CoopOptionsHandling();
    void ReadyButtonsHandling();
    bool SkinSelectorHandling();
    void ControlButtonsHandling();
    void BgSelectorHandling();
    void Close(Screens screen);
    void SetBoardsPosition();
    const float fontSize = 1.0f/30;
    const std::vector<std::string> 
      controlOptions[2] = {
        {"W A S D SPACE LSHIFT C", "S Z X C LSHIFT D F"}, 
        {"^ < > v ENTER RCTRL RSHIFT", "I J K L N O P"}
      },
      readyStr = {"Not Ready", "Ready!"},
      imagesName = {
        "Calm river","Night forest", "Afternoon", "Gray smell"
      },
      skinNames = {"Letris", "Retro", "Minimalist", "Pastel"};
    std::unordered_map<std::string, int> controlsIndexes = {
      {"W A S D SPACE LSHIFT C", 0},
      {"S Z X C LSHIFT D F", 6},
      {"^ < > v ENTER RCTRL RSHIFT", 5},
      {"I J K L N O P", 7}
    };
    std::string selectedControls[2];
    std::string selectedSkin[2] = {skinNames[settings::db["COOPSKINS"][0]], skinNames[settings::db["COOPSKINS"][1]]};
    bool clicked[2] = {false, false};
    OptionsButton 
      *controlButtons[2] = {nullptr, nullptr},
      skinSelector[2] = {
        OptionsButton(selectedSkin[0], Vec2<double>{0.15, 0.20 + (float)(5.55 * settings::cellSize)/settings::screenHeight}, fontSize, skinNames),
        OptionsButton(selectedSkin[1], Vec2<double>{0.85, 0.20 + (float)(5.55 * settings::cellSize)/settings::screenHeight}, fontSize, skinNames)
      };
    ScreenButton 
      readyButtons[2] = {
        ScreenButton(readyStr[0], Vec2<double>{0.15, 0.85}, fontSize, COOP, RED), 
        ScreenButton(readyStr[0], Vec2<double>{0.85, 0.85}, fontSize, COOP, RED)
      },
      backgroundSelector = ScreenButton(Vec2<double>{0.37, 1.0f/2}, COOP, settings::bgImagesNames[settings::coopBgImage], 
        Vec2<double>{4, 8});
    std::vector<Button*> buttons;
    ButtonManager *buttonManager = nullptr;
    int bgImageIndex = settings::coopBgImage, bgImagesSize = settings::bgImagesNames.size();
    Board boards[2] = {
      Board{{(int)(settings::screenWidth * 0.15) - 2 * settings::cellSize, (int)(settings::screenHeight * 0.20)}, {4, 5}, settings::cellSize, settings::padding}, 
      Board{{(int)(settings::screenWidth * 0.85) - 2 * settings::cellSize, (int)(settings::screenHeight * 0.20)}, {4, 5}, settings::cellSize, settings::padding}
    };
    Shape *shapes[2] = {nullptr, nullptr};
    ScreenButton returnButton;
};
