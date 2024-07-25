#include <raylib.h>
#include <set>
#include <string>
#include <vector>
#include "ButtonManager.hpp"
#include "Screen.hpp"
#include "Game.hpp"
#include "OptionsButton.hpp"
#include "ScreenButton.hpp"
#include "Settings.hpp"
#define CONTROLS_QTD 4
#define SCREEN_SIZE_QTD 3
#define OPT_QTD_OPTIONS 5
#define NUM_COLS 6

class Options : public Screen {
public:
  void Tick() override;
  ~Options();
private:
  void OptionsHandling();
  int currentSelected = 0;
  int itemSelected[2] = {settings::db["CONTROL"], GetScreenSizeIndex()};
  int itemQuantity[2] = {CONTROLS_QTD, SCREEN_SIZE_QTD};
  Color optionsColor[OPT_QTD_OPTIONS] = {RAYWHITE, GRAY, GRAY, GRAY};
  Color controlsColor[CONTROLS_QTD] = {RAYWHITE, GRAY, GRAY, GRAY};
  Color screenSizesColor[SCREEN_SIZE_QTD] = {RAYWHITE, GRAY, GRAY};

  void Draw() override;
  float y0 = (float)1/8;
  float lineDistance = (float)1/17;
  int factor = 1;
  void DrawHeader();
  void DrawButtons();
  void DrawControls();
  void DrawSectionHeader(const char *, float);
  int CalculateTotalTextWidth();
  void DrawColumns(int, int);
  void DrawControlOptions(int, int);
  void DrawScreenSize();
  void DrawArrows(double, Color);
  void DrawArrows(int, Color);
  void DrawVolume();
  int move[2] = {0, 0};
  int speed = 0;
  int volume = settings::db["VOLUME"];
  int GetNextItemSelected(int);
  int GetPreviousItemSelected(int);
  int GetScreenSizeIndex();
  void HandleEnterKey();
  void UpdateColors();
  void DrawGeneral();
  void HandleArrowKey(int);
  float fontSizes[2] = {(float)1/20, (float)1/30};
  void SetNewResolution(std::string resolution); 
  std::string GetText(const std::string textTotal, size_t& pos);
  std::string columns = "Rotate CW,Left,Down,Right,Instant Fall,Rotate ACW";
  std::vector<std::string> controls = {
    "W A S D SPACE Z",
    "^ < > v SPACE Z",
    "I J K L SPACE Z",
    "K H L J SPACE Z",
  };
  const char *screenSizes[SCREEN_SIZE_QTD] = {"800x600", "1080x720", "1366x768"};
  std::vector<std::string> screenSizes2 = {"800x600", "1280x720", "1366x768"};
  std::vector<std::string> screenMode = {"Window", "FullScreen"};
  std::string selectedResolution = to_string(settings::db["WINDOW_WIDTH"]) + "x" + to_string(settings::db["WINDOW_HEIGHT"]);
  std::string selectedControl = controls[settings::db["CONTROL"]];
  float x = (float)1/2, y = y0 + 2 * lineDistance;
  ScreenButton *returnButton = new ScreenButton("Return", Vec2<double>{1.0f/2, 3.0f/4}, 1.0f/20, MENU);
  OptionsButton *screenSizeButton = new OptionsButton(selectedResolution, Vec2<double>{1.0f/2, 1.0f/3},
      fontSizes[1], screenSizes2, selectedResolution);
  OptionsButton *screenModeButton = new OptionsButton("Window", Vec2<double>{1.0f/2, 1/2.3},
      fontSizes[1], screenMode, "Window");
  const std::vector<Button*> generalButtons = {
    screenModeButton,
    screenSizeButton,
  };
  const std::vector<Button*> controlButtons = {
    new OptionsButton(selectedControl, Vec2<double>{1.0f/2, 1.0f/3}, fontSizes[1], controls, selectedControl),
  };
  const std::vector<Button*> volumeButtons = {
    new Button("                                     ", Vec2<double>{1.0f/2, 1.0f/3}, fontSizes[1])
  };
  const std::vector<Button*> buttons = {
    new OptionsButton("General", Vec2<double>{1.0f/4, 1.0f/10}, fontSizes[0], generalButtons),
    new OptionsButton("Controls", Vec2<double>{1.0f/2, 1.0f/10}, fontSizes[0], controlButtons),
    new OptionsButton("Volume", Vec2<double>{3.0f/4, 1.0f/10}, fontSizes[0], volumeButtons),
    returnButton,
  };
  ButtonManager buttonManager = ButtonManager(buttons, true);
  enum itens {
    CONTROL,
    SCREENSIZE,
  };
  enum buttonsNum {
    GENERAL,
    CONTROLS,
    VOLUME
  };
  int GetIndex(std::string, std::vector<std::string>);
  void OpenClose() override;
  void SetNewControl(std::string);
  void SetNewVolume(double);
  bool MouseInVolumeBar(double);
};

