#include <raylib.h>
#include "Screen.hpp"
#include "Game.hpp"

#define CONTROLS_QTD 4
#define OPT_QTD_OPTIONS 2
#define NUM_COLS 7
#define LINE_DISTANCE 40
#define ANIMATION_SPEED 25

class Options : public Screen {
public:
  void Tick() override;
private:
  void OptionsHandling();
  int currentSelected = 0;
  int controlSelected = 0;
  Color optionsColor[OPT_QTD_OPTIONS] = {RAYWHITE, GRAY};
  Color controlsColor[CONTROLS_QTD] = {RAYWHITE, GRAY, GRAY, GRAY};
  void Draw() override;
  int move = 0;
  int speed = 0;
  const char *columns[NUM_COLS] = {"Rotate CW", "Left", "Down", "Right", "Instant Fall", "Rotate ACW", "Selected"};
  const char *controls[CONTROLS_QTD][NUM_COLS] = {
    {"W", "A", "S", "D", "SPACE", "Z", ""},
    {"^", "<", ">", "v", "SPACE", "Z", ""},
    {"I", "J", "K", "L", "SPACE", "Z", ""},
    {"K", "H", "L", "J", "SPACE", "Z", ""},
  };
  int GetNextControlSelected();
  int GetPreviousControlSelected();
};

