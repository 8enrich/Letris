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

class Options : public Screen {
public:
  void Tick() override;
  ~Options();
private:
  void OptionsHandling();
  int currentSelected = 0;
  void Draw() override;
  int volume = settings::db["VOLUME"];
  void DrawGeneral();
  void DrawVolume();
  void DrawControls();
  int GetIndex(std::string, std::vector<std::string>);
  void OpenClose() override;
  void SetNewControl(std::string);
  void SetNewVolume(double);
  bool MouseInVolumeBar(double);
  float fontSizes[2] = {(float)1/20, (float)1/30};
  void SetNewResolution(std::string resolution); 
  std::string columns = "Rotate CW,Left,Down,Right,Instant Fall,Rotate ACW";
  std::vector<std::string> controls = {
    "W A S D SPACE Z",
    "^ < > v SPACE Z",
    "I J K L SPACE Z",
    "K H L J SPACE Z",
  };
  std::vector<std::string> screenSizes = {"800x600", "1280x720", "1366x768"};
  std::vector<std::string> screenModes = {"Window", "FullScreen"};
  std::string selectedResolution = to_string(settings::db["WINDOW_WIDTH"]) + "x" + to_string(settings::db["WINDOW_HEIGHT"]);
  std::string selectedControl = controls[settings::db["CONTROL"]];
  ScreenButton *returnButton = new ScreenButton("Return", Vec2<double>{1.0f/2, 3.0f/4}, 1.0f/20, MENU);
  OptionsButton *screenSizeButton = new OptionsButton(selectedResolution, Vec2<double>{1.0f/2, 1.0f/3},
      fontSizes[1], screenSizes);
  OptionsButton *screenModeButton = new OptionsButton("Window", Vec2<double>{1.0f/2, 1/2.3},
      fontSizes[1], screenModes);
  const std::vector<Button*> generalButtons = {
    screenModeButton,
    screenSizeButton,
  };
  const std::vector<Button*> controlButtons = {
    new OptionsButton(selectedControl, Vec2<double>{1.0f/2, 1.0f/3}, fontSizes[1], controls)
  };
  const std::vector<Button*> volumeButtons = {
    new Button("                                     ", Vec2<double>{1.0f/2, 1.0f/3}, fontSizes[1])
  };
  const std::vector<Button*> buttons = {
    new OptionsButton("General", Vec2<double>{1.0f/4, 1.0f/10}, fontSizes[0], generalButtons),
    new OptionsButton("Controls", Vec2<double>{1.0f/2, 1.0f/10}, fontSizes[0], controlButtons),
    new OptionsButton("Sound", Vec2<double>{3.0f/4, 1.0f/10}, fontSizes[0], volumeButtons),
    returnButton,
  };
  ButtonManager buttonManager = ButtonManager(buttons);
  enum buttonsNum {
    GENERAL,
    CONTROLS,
    VOLUME
  };
};

