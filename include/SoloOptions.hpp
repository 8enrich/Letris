#pragma once
#include "Board.hpp"
#include "Button.hpp"
#include "ButtonManager.hpp"
#include "OptionsButton.hpp"
#include "Screen.hpp"
#include "ScreenButton.hpp"
#include "Shape.hpp"

class SoloOptions : public Screen{
  public:
    SoloOptions();
    ~SoloOptions();
    void Tick() override;
  protected:
    const float fontSize = 1.0f/30;
    const std::vector<std::string> skinNames = {"Letris", "Retro", "Minimalist", "Pastel", "Tetr.io"};
    const std::vector<std::string> imagesName = {"Calm river","Night forest", "Afternoon", "Gray smell"};
  private:
    void Draw() override;
    bool SoloOptionsHandling();
    void Close(Screens screen);
    void ScreenButtonsHandling();
    void BgSelectorHandling();
    bool SkinSelectorHandling();
    void InputTextHandling();
    void InputTextSettings();
    void SetBoardPosition();
    std::string GetKeyboardInput();
    std::string selectedSkin = skinNames[settings::db["SKIN"]];
    Board board;
    Shape *shape;
    OptionsButton skinSelector;
    ScreenButton inputText;
    ScreenButton backgroundSelector;
    ScreenButton play;
    ScreenButton returnButton;
    std::vector<Button*> buttons;
    ButtonManager *buttonManager = nullptr;
    int bgImageIndex, bgImagesSize;
    bool inputTextSelected;
    std::string inputTextStr;
};
