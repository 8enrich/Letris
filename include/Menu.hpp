#include <raylib.h>
#include "Screen.hpp"

#define OPT_QTD_MENU 3

class Menu : public Screen {
public:
  void Tick() override;
private:
  void OptionsHandling();
  int currentSelected = 0;
  Color optionsColor[OPT_QTD_MENU] = {RAYWHITE, GRAY, GRAY};
  void Draw() override;
};
