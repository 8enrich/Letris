#include <raylib.h>
#include "Screen.hpp"

#define OPT_QTD 3

class GameOver : public Screen {
public:
  void Tick() override;
private:
  void OptionsHandling();
  int currentSelected = 0;
  Color optionsColor[OPT_QTD] = {RAYWHITE, GRAY, GRAY};
  void Draw() override;
};
