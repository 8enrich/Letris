#include <raylib.h>
#include "Screen.hpp"
#include "Game.hpp"

#define OPT_QTD_OPTIONS 5
#define NUM_COLS 7

class Options : public Screen {
public:
  void Tick() override;
private:
  void OptionsHandling();
  int currentSelected = 0;
  Color optionsColor[OPT_QTD_OPTIONS] = {RAYWHITE, GRAY, GRAY, GRAY, GRAY};
  void Draw() override;
  int controlSelected = 0;
};

