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
  void SetNewScreenMode(std::string);
  bool MouseInVolumeBar(double);
  int GetMaxResolutionIndex();
  float fontSizes[2] = {(float)1/20, (float)1/30};
  void SetNewResolution(std::string resolution); 
  std::vector<std::string> columns = {"Rotate CW","Left","Down","Right","Instant Fall","Rotate ACW", "Hold"};
  std::vector<std::string> controls = {
    "W A S D SPACE Z C",
    "^ < > v SPACE Z C",
    "I J K L SPACE Z C",
    "K H L J SPACE Z C",
    "Custom"
  };
  std::vector<std::string> screenSizes = {"800x600", "1280x720", "1366x768", "1600x900", "1920x1080"};
  std::vector<std::string> screenModes = {"Window", "FullScreen"};
  std::string selectedResolution = to_string(settings::db["WINDOW_WIDTH"]) + "x" + to_string(settings::db["WINDOW_HEIGHT"]);
  std::string selectedScreenMode = settings::db["WINDOWED"] ? screenModes[0] : screenModes[1];
  std::string selectedControl = controls[settings::db["CONTROL"]];
  ScreenButton returnButton = ScreenButton("Return", Vec2<double>{1.0f/2, 3.0f/4}, 1.0f/20, MENU);
  OptionsButton screenSizeButton = OptionsButton(selectedResolution, Vec2<double>{1.0f/2, 1.0f/3},
      fontSizes[1], screenSizes);
  OptionsButton screenModeButton = OptionsButton(selectedScreenMode, Vec2<double>{1.0f/2, 1/2.3},
      fontSizes[1], screenModes);
  const std::vector<Button*> generalButtons = { &screenModeButton, &screenSizeButton};
  OptionsButton FirstControlButton = OptionsButton(selectedControl, Vec2<double>{1.0f / 2, 1.0f / 3}, fontSizes[1], controls);
  Button RotateControl = Button(settings::keyToString[settings::db["CUSTOM_CONTROLS"][0]],
      Vec2<double>{1.0f/2, 1/2.4}, fontSizes[1]);
  Button LeftControl = Button(settings::keyToString[settings::db["CUSTOM_CONTROLS"][1]],
      Vec2<double>{1.0f/2, 1/2.25}, fontSizes[1]);
  Button DownControl = Button(settings::keyToString[settings::db["CUSTOM_CONTROLS"][2]],
      Vec2<double>{1.0f/2, 1/2.1}, fontSizes[1]);
  Button RightControl = Button(settings::keyToString[settings::db["CUSTOM_CONTROLS"][3]],
      Vec2<double>{1.0f/2, 1/1.95}, fontSizes[1]);
  Button FallControl = Button(settings::keyToString[settings::db["CUSTOM_CONTROLS"][4]],
      Vec2<double>{1.0f/2, 1/1.8}, fontSizes[1]);
  Button ARotateControl = Button(settings::keyToString[settings::db["CUSTOM_CONTROLS"][5]],
      Vec2<double>{1.0f/2, 1/1.65}, fontSizes[1]);
  Button HoldControl = Button(settings::keyToString[settings::db["CUSTOM_CONTROLS"][6]],
      Vec2<double>{1.0f/2, 1/1.5}, fontSizes[1]);
  int buttonClicked = 0;
  const std::vector<Button*> controlButtons = { &RotateControl, &LeftControl,
    &DownControl, &RightControl, &FallControl, &ARotateControl, &HoldControl, &FirstControlButton };
  Button MasterVolumeButton = Button("                                     ", Vec2<double>{1.0f / 2, 1.0f / 3}, fontSizes[1]);
  const std::vector<Button*> volumeButtons = { &MasterVolumeButton };
  OptionsButton General = OptionsButton("General", Vec2<double>{1.0f / 4, 1.0f / 10}, fontSizes[0], generalButtons);
  OptionsButton Controls = OptionsButton("Controls", Vec2<double>{1.0f / 2, 1.0f / 10}, fontSizes[0], controlButtons);
  OptionsButton Sound = OptionsButton("Sound", Vec2<double>{3.0f / 4, 1.0f / 10}, fontSizes[0], volumeButtons);
  const std::vector<Button*> buttons = { &General, &Controls, &Sound, &returnButton };
  ButtonManager buttonManager = ButtonManager(buttons);
  enum buttonsNum {
    GENERAL,
    CONTROLS,
    VOLUME
  };
};

