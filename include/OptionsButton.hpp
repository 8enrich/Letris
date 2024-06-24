#include "Button.hpp"
#include "ButtonManager.hpp"
#include <memory>
#include <string>
#include <vector>

class OptionsButton : public Button {
public:
  OptionsButton(std::string buttonText, Vec2<double> buttonPosition, float fontSize, std::vector<std::string> options, std::string optionInSettings);
  void Move(int);
  void Tick() override;
  void OpenMenu();
  void CloseMenu();
  std::string GetButtonText();
private:
  void MenuHandling();
  void Update();
  ButtonManager* buttonOptions;
  bool isMenuOpen = false;
  std::vector<std::string> options;
  std::string optionInSettings;
  int currentSelectedOptionIndex = 0;
  int GetSelectedItemIndex();
  void DrawMenu();
};
