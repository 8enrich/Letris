#include <raylib.h>
#include "Screen.hpp"
#include "Game.hpp"

#define CONTROLS_QTD 4
#define SCREEN_SIZE_QTD 3
#define OPT_QTD_OPTIONS 4
#define NUM_COLS 6

class Options : public Screen {
public:
  void Tick() override;
private:
  void OptionsHandling();
  int currentSelected = 0;
  int itemSelected[2] = {0, 0};
  int itemQuantity[2] = {CONTROLS_QTD, SCREEN_SIZE_QTD};
  Color optionsColor[OPT_QTD_OPTIONS] = {RAYWHITE, GRAY, GRAY};
  Color controlsColor[CONTROLS_QTD] = {RAYWHITE, GRAY, GRAY, GRAY};
  Color screenSizesColor[SCREEN_SIZE_QTD] = {RAYWHITE, GRAY, GRAY};
  void Draw() override;
  void DrawControls();
  void DrawScreenSize();
  void DrawArrows(float, Color);
  int move[2] = {0, 0};
  int speed = 0;
  int GetNextItemSelected(int);
  int GetPreviousItemSelected(int);
  int GetScreenSizeIndex();
  float fontSizes[2] = {(float)1/20, (float)1/25};
  const char *columns[NUM_COLS] = {"Rotate CW", "Left", "Down", "Right", "Instant Fall", "Rotate ACW"};
  const char *controls[CONTROLS_QTD][NUM_COLS] = {
    {"W", "A", "S", "D", "SPACE", "Z"},
    {"^", "<", ">", "v", "SPACE", "Z"},
    {"I", "J", "K", "L", "SPACE", "Z"},
    {"K", "H", "L", "J", "SPACE", "Z"},
  };
  const char *screenSizes[SCREEN_SIZE_QTD] = {"800x600", "1080x720", "1366x768"};
  enum itens {
    CONTROL,
    SCREENSIZE,
  };
};

