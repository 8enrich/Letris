#include "../include/Options.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>
#include <string>
#include <iostream>

using namespace std;
using namespace settings;
using namespace ray_functions;

Options::Options() :
  currentSelected(0), buttonClicked(0), volume(db["VOLUME"]),
  selectedResolution(to_string(db["WINDOW_WIDTH"]) + "x" + to_string(db["WINDOW_HEIGHT"])),
  selectedScreenMode(db["WINDOWED"] ? screenModes[0] : screenModes[1]),
  selectedControl(controls[db["CONTROL"]])
{
  CreateControlButtons();
  CreateGeneralButtons();
  CreateSoundButtons();
  returnButton = new ScreenButton("<", Vec2<double>{1.0f/30, 1.0f/50}, 1.0f/20, MENU);
  buttons = { general, control, sound, returnButton };
  buttonManager = new ButtonManager(buttons);
}

void Options::CreateControlButtons(){
  for(int i = 0; i < 7; i++){
    controlButtons.push_back(new Button(keyToString[settings::controls[db["CONTROL"]][i]],
      Vec2<double>{1.0f/2, 1/(2.4 - i * 0.15)}, fontSizes[1], ButtonTypes::KEYBUTTON));
  }
  controlButton = new OptionsButton(selectedControl, Vec2<double>{1.0f / 2, 1.0f / 3}, fontSizes[1], controls);
  controlButtons.push_back(controlButton);
  control = new OptionsButton("Controls", Vec2<double>{1.0f / 2, 1.0f / 10}, fontSizes[0], controlButtons);
}

void Options::CreateGeneralButtons(){
  screenSizeButton = new OptionsButton(selectedResolution, Vec2<double>{1.0f/2, 1.0f/3}, fontSizes[1], screenSizes);
  screenModeButton = new OptionsButton(selectedScreenMode, Vec2<double>{1.0f/2, 1/2.3}, fontSizes[1], screenModes);
  generalButtons = { screenModeButton, screenSizeButton};
  general = new OptionsButton("General", Vec2<double>{1.0f / 4, 1.0f / 10}, fontSizes[0], generalButtons);
}

void Options::CreateSoundButtons(){
  masterVolumeButton = new Button("                                     ", Vec2<double>{1.0f / 2, 1.0f / 3}, fontSizes[1], ButtonTypes::VOLUME);
  volumeButtons = { masterVolumeButton };
  sound = new OptionsButton("Sound", Vec2<double>{3.0f / 4, 1.0f / 10}, fontSizes[0], volumeButtons);
}

Options::~Options(){
  deleteButtonVector(controlButtons);
  deleteButtonVector(generalButtons);
  deleteButtonVector(volumeButtons);
  deleteButtonVector(buttons);
  delete buttonManager;
}


void Options::deleteButtonVector(vector<Button*> buttons){
  for (Button* button : buttons) { delete button; }
}

void Options::Tick(){
  if(IsMusicStreamPlaying(music)) {UpdateMusicStream(music);}
  OptionsHandling();
  BeginDrawing();
  Draw();
  buttonManager->Tick();
  EndDrawing();
}

void Options::Draw() {
  ClearBackground(BLACK);
  DrawFormatedRectangle(Vec2<double>{1.0f/2, 1.0f/12}, Vec2<double>{1/1.5, 1.0f/10}, WHITE);
  switch(currentSelected){
    case GENERAL:
      DrawGeneral();
      break;
    case CONTROLS:
      DrawControls();
      break;
    case VOLUME:
      DrawVolume();
      break;
    default:
      break;
  }
}

void Options::OpenClose(){
  Screen::OpenClose();
  if(!shouldClose){
  	returnButton->SetScreen(nextScreen);
  	currentSelected = 0;
  }
}

int Options::GetIndex(string item, vector<string> vector){
  for(int i = 0, size = vector.size(); i < size; i++){
    if(item == vector[i]) return i;
  }
  return 0;
}

void Options::SetNewResolution(string resolution){
  int index = GetIndex(resolution, screenSizes), display = GetCurrentMonitor();
  if(settings::screenSizes[index].GetX() > GetMonitorWidth(display)){
    index = GetMaxResolutionIndex();
    resolution = screenSizes[index];
    screenSizeButton->SetCurrentSelectedOptionIndex(index);
  }
  UpdateWindowSize(settings::screenSizes[index]);
  selectedResolution = resolution;
}

void Options::SetNewControl(string control){
  int index = GetIndex(control, controls);
  db["CONTROL"] = index;
  selectedControl = control;
  for(int i = 0, size = controlButtons.size(); i < size - 1; i++){
    controlButtons[i]->SetButtonText(keyToString[settings::controls[index][i]]);
  }
}

void Options::SetNewScreenMode(string screenMode) {
  db["WINDOWED"] = screenMode == "Window";
  selectedScreenMode = screenMode;
  if (db["WINDOWED"]) {
    ToggleBorderlessWindowed();
    SetNewResolution(selectedResolution);
    return;
  }
  selectedResolution = screenSizes[GetMaxResolutionIndex()];
  int index = GetIndex(selectedResolution, screenSizes);
  screenSizeButton->SetCurrentSelectedOptionIndex(index);
  FullScreen();
}

int Options::GetMaxResolutionIndex(){
  int display = GetCurrentMonitor(), maxWidth = GetMonitorWidth(display), index = 0;
  for(int size = screenSizes.size(); index < size; index++){
    if(settings::screenSizes[index].GetX() > maxWidth) break;
  }
  return index - 1;
}

void Options::SetNewVolume(double mousePosition){
  int width = screenWidth;
  float xBegin = width/2.0f - width/9.0f, xEnd = width/2.0f + width/9.0f, y1 = 1/2.85;
  double doubleVolume = 100 * (mousePosition - xBegin)/(xEnd - xBegin);
  volume = (doubleVolume - (int) doubleVolume >= 0.5)? (int) doubleVolume + 1: (int) doubleVolume;
  db["VOLUME"] = volume;
}

bool Options::MouseInVolumeBar(double mousePosition){
  int width = screenWidth;
  return mousePosition >= width/2.0f - width/9.0f && mousePosition <= width/2.0f + width/9.0f;
}

void Options::DrawGeneral(){
  DrawFormatedText("Resolution:", Vec2<double>{1.0f/3, 1.0f/3}, fontSizes[1], RAYWHITE);
  DrawFormatedText("Window Mode:", Vec2<double>{1.0f/3, 1/2.3}, fontSizes[1], RAYWHITE);
}

void Options::DrawControls() {
  DrawFormatedText("Controls:", Vec2<double>{1.0f/3.4, 1.0f/3}, fontSizes[1], RAYWHITE);
  for(int i = 0; i < 7; i++){
    DrawFormatedText(TextFormat("%s:", columns[i].c_str()), Vec2<double>{1.0f/3.4, 1.0f/(2.4 - i * 0.15)},
        fontSizes[1], RAYWHITE);
  }
}

void Options::DrawVolume(){
  DrawFormatedText("Volume:", Vec2<double>{1.0f/3, 1.0f/3}, fontSizes[1], RAYWHITE);
  int width = screenWidth, height = screenHeight;
  float xBegin = width/2.0f - width/9.0f, xEnd = width/2.0f + width/9.0f, y1 = 1/2.85;
  DrawLineEx(Vector2{xBegin, height * y1}, Vector2{xEnd, height * y1}, (float)height/200, WHITE);
  DrawCircleV({(xEnd - xBegin) * (float)volume/100 + xBegin, height * y1}, (float)height/100, WHITE);
  DrawFormatedText(TextFormat("%d% %", volume), Vec2<double>{1.0f/2 + 1.0f/6, 1.0f/3},
      fontSizes[1], WHITE);
}

void Options::OptionsHandling() {
  currentSelected = buttonManager->GetCurrentSelected(currentSelected);
  GeneralButtonsHandling();
  ControlButtonsHandling();
  VolumeButtonsHandling();
  if(buttonManager->GetScreen() != NOTSCREEN) {
    nextScreen = buttonManager->GetScreen();
    buttonManager->ResetScreen();
    OpenClose();
  }
  if(GetKeyPressed() == KEY_ESCAPE) OpenClose();
}

void Options::GeneralButtonsHandling(){
  ScreenModeHandling();
  ScreenResolutionHandling();
}

void Options::ScreenModeHandling(){
  string screenModeString = screenModeButton->GetText();
  if (selectedScreenMode != screenModeString) SetNewScreenMode(screenModeString);
}

void Options::ScreenResolutionHandling(){
  string resolutionString = screenSizeButton->GetText();
  if (selectedResolution != resolutionString && db["WINDOWED"]) SetNewResolution(resolutionString);
}

void Options::ControlButtonsHandling(){
  ControlHandling();
  CustomControlHandling();
}

void Options::ControlHandling(){
  string controlString = controlButtons[controlButtons.size() - 1]->GetText();
  if (selectedControl != controlString) SetNewControl(controlString);
}

void Options::CustomControlHandling(){
  CheckButtonClicked();
  if(buttonClicked) GetKeyboardInput();
}

void Options::CheckButtonClicked(){
  for(int i = 0, size = controlButtons.size(); i < size - 1; i++){
    if(controlButtons[i]->isButtonClicked()) buttonClicked = i + 1;
  }
}

void Options::GetKeyboardInput(){
  KeyboardKey key = static_cast<KeyboardKey>(GetKeyPressed());
  string stringKey = keyToString[key];
  if(key || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    if(stringKey != "") ChangeControls(stringKey, key);
    buttonClicked = 0;
  }
}

void Options::ChangeControls(string stringKey, KeyboardKey key){
  SetControlsToActualControls();
  SwapSameControls(stringKey);
  controlButtons[buttonClicked - 1]->SetButtonText(stringKey);
  db["CUSTOM_CONTROLS"][buttonClicked - 1] = key;
  controlButton->SetCurrentSelectedOptionIndex(4);
  SetCustomControls();
}

void Options::SetControlsToActualControls(){
  for(int i = 0, size = controlButtons.size(); i < size - 1; i++){
    db["CUSTOM_CONTROLS"][i] = settings::controls[db["CONTROL"]][i];
  }
}

void Options::SwapSameControls(string stringKey){
  for(int i = 0, size = controlButtons.size(); i < size - 1; i++){
    if(controlButtons[i]->GetText() == stringKey){
      db["CUSTOM_CONTROLS"][i] = settings::controls[db["CONTROL"]][buttonClicked - 1];
      controlButtons[i]->SetButtonText(controlButtons[buttonClicked - 1]->GetText());
    }
  }
}

void Options::VolumeButtonsHandling(){
  double mousePosition = volumeButtons[0]->GetMousePositionX();
  if (MouseInVolumeBar(mousePosition)) SetNewVolume(mousePosition);
}
