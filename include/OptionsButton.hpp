#pragma once
#include "Button.hpp"
#include "ButtonManager.hpp"
#include <memory>
#include <string>
#include <vector>

class OptionsButton : public Button {
public:
  OptionsButton(std::string buttonText, Vec2<double> buttonPosition, float fontSize, std::vector<std::string> options);
  OptionsButton(std::string buttonText, Vec2<double> buttonPosition, float fontSize, std::vector<Button*> buttons);
  void Tick() override;
  void OpenMenu();
  void CloseMenu();
  bool GetIsClicked();
  std::string GetButtonText();
  void SetButtonText(std::string);
  void SetCurrentSelectedOptionIndex(int);
  bool HasButtonSelected();
  int GetButtonSelected();
  bool GetIsMenuOpen();
private:
  void MenuHandling();
  void Update() override;
  ButtonManager* buttonOptions;
  bool isMenuOpen = false;
  std::vector<std::string> options;
  int currentSelectedOptionIndex = 0;
  int GetSelectedItemIndex();
  void DrawMenu();
  int GetLargestOptionText();
  Vec2<double> GetMenuWidthHeight();
};
