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
  Options();
  ~Options();
private:
  void CreateControlButtons();
  void CreateGeneralButtons();
  void CreateSoundButtons();
  void deleteButtonVector(std::vector<Button*> buttons);
  void OptionsHandling();
  void Draw() override;
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
  void GeneralButtonsHandling();
  void ScreenModeHandling();
  void ScreenResolutionHandling();
  void ControlButtonsHandling();
  void ControlHandling();
  void CustomControlHandling();
  void CheckButtonClicked();
  void GetKeyboardInput();
  void ChangeControls(std::string, KeyboardKey);
  void SetControlsToActualControls();
  void SwapSameControls(std::string);
  void VolumeButtonsHandling();
  void SetNewResolution(std::string resolution);
  int currentSelected;
  int buttonClicked;
  int volume;
  const float fontSizes[2] = {1.0f/20, 1.0f/30};
  const std::vector<std::string> columns = {"Rotate CW","Left","Down","Right","Instant Fall","Rotate ACW", "Hold"};
  const std::vector<std::string> controls = {"Right hand", "Arrows", "Left hand", "Vim Mode", "Custom"};
  const std::vector<std::string> screenSizes = {"1024x576", "1280x720", "1366x768", "1600x900", "1920x1080"};
  const std::vector<std::string> screenModes = {"Window", "FullScreen"};
  std::string selectedResolution;
  std::string selectedScreenMode;
  std::string selectedControl;
  ScreenButton *returnButton;
  OptionsButton *screenSizeButton;
  OptionsButton *screenModeButton;
  std::vector<Button*> generalButtons;
  OptionsButton *controlButton;
  std::vector<Button*> controlButtons;
  Button *masterVolumeButton;
  std::vector<Button*> volumeButtons;
  OptionsButton *general;
  OptionsButton *control;
  OptionsButton *sound;
  std::vector<Button*> buttons;
  ButtonManager *buttonManager;
  Texture2D *bgImage = nullptr;
  enum buttonsNum {
    GENERAL,
    CONTROLS,
    VOLUME
  };
};

