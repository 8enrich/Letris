#include "Button.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class OptionsButton : Button {
public:
  OptionsButton(std::string buttonText, float fontSize, Vec2<double> buttonPosition, std::unordered_map<std::string, std::vector<std::string>> optionsMap);
//  void Move(int) override;
private:
  std::unordered_map<std::string, std::vector<std::string>> optionsMap;
  int GetItemIndex(std::string);
};
