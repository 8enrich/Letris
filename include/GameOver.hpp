#include <raylib.h>
#include "Screen.hpp"

#define OPT_QTD 2

class GameOver : public Screen {
public:
  GameOver();
  void Tick() override;
private:
  void OptionsHandling();
  int currentSelected = 0;
  Color optionsColor[OPT_QTD] = {RAYWHITE, GRAY};
  void Draw() override;
};
