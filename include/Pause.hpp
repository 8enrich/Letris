#include <raylib.h>
#include "Screen.hpp"

#define OPT_QTD_PAUSE 3

class Pause : public Screen {
public:
  void Tick() override;
private:
  void OptionsHandling();
  int currentSelected = 0;
  Color optionsColor[OPT_QTD_PAUSE] = {RAYWHITE, GRAY, GRAY};
  void Draw() override;
};
