#include "../include/Options.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>
#include <string>

Options::~Options(){
  for (auto button : buttons) delete button;
  for (auto button : generalButtons) delete button;
  for (auto button : controlButtons) delete button;
  for (auto button : volumeButtons) delete button;
}

void Options::Tick(){
  if(IsMusicStreamPlaying(music)) {UpdateMusicStream(music);}
  OptionsHandling();
  BeginDrawing();
  Draw();
  buttonManager.Tick();
  EndDrawing();
}

void Options::Draw() {
  ClearBackground(BLACK);
  ray_functions::DrawFormatedRectangle(Vec2<double>{1.0f/2, 1.0f/12}, Vec2<double>{1/1.5, 1.0f/10}, WHITE);
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

int Options::GetIndex(std::string item, std::vector<std::string> vector){
  for(int i = 0, size = vector.size(); i < size; i++){
    if(item == vector[i]) return i;
  }
  return 0;
}

void Options::SetNewResolution(std::string resolution){
  int index = GetIndex(resolution, screenSizes);
  settings::UpdateWindowSize(settings::screenSizes[index]);
  selectedResolution = resolution;
}

void Options::SetNewControl(std::string control){
  int index = GetIndex(control, controls);
  settings::db["CONTROL"] = index;
  selectedControl = control;
}

void Options::SetNewVolume(double mousePosition){
  int width = settings::screenWidth;
  float xBegin = width/2.0f - width/9.0f, xEnd = width/2.0f + width/9.0f, y1 = 1/2.85;
  double doubleVolume = 100 * (mousePosition - xBegin)/(xEnd - xBegin);
  volume = (doubleVolume - (int) doubleVolume >= 0.5)? (int) doubleVolume + 1: (int) doubleVolume;
  settings::db["VOLUME"] = volume;
}

bool Options::MouseInVolumeBar(double mousePosition){
  int width = settings::screenWidth;
  return mousePosition >= width/2.0f - width/9.0f && mousePosition <= width/2.0f + width/9.0f;
}

void Options::DrawGeneral(){
  ray_functions::DrawFormatedText("Resolution:", Vec2<double>{1.0f/3, 1.0f/3}, fontSizes[1], RAYWHITE);
  ray_functions::DrawFormatedText("Window Mode:", Vec2<double>{1.0f/3, 1/2.3}, fontSizes[1], RAYWHITE);
}

void Options::DrawControls() {
  ray_functions::DrawFormatedText("Controls:", Vec2<double>{1.0f/3.2, 1.0f/3}, fontSizes[1], RAYWHITE);
}

void Options::DrawVolume(){
  ray_functions::DrawFormatedText("Volume:", Vec2<double>{1.0f/3, 1.0f/3}, fontSizes[1], RAYWHITE);
  int width = settings::screenWidth, height = settings::screenHeight;
  float xBegin = width/2.0f - width/9.0f, xEnd = width/2.0f + width/9.0f, y1 = 1/2.85;
  DrawLineEx((Vector2){xBegin, height * y1}, (Vector2){xEnd, height * y1}, (float)height/200, WHITE);
  DrawCircleV({(xEnd - xBegin) * (float)volume/100 + xBegin, height * y1}, (float)height/100, WHITE);
  ray_functions::DrawFormatedText(TextFormat("%d% %", volume), Vec2<double>{1.0f/2 + 1.0f/6, 1.0f/3},
      fontSizes[1], WHITE);
}

void Options::OptionsHandling() {
  currentSelected = buttonManager.GetCurrentSelected(currentSelected);
  std::string resolutionString = screenSizeButton->GetText();
  std::string controlString = controlButtons[0]->GetText();
  double mousePosition = volumeButtons[0]->GetMousePositionX();
  if (selectedResolution != resolutionString) SetNewResolution(resolutionString);
  if (selectedControl != controlString) SetNewControl(controlString);
  if (MouseInVolumeBar(mousePosition)) SetNewVolume(mousePosition);
  if(buttonManager.GetScreen() != NOTSCREEN) {
    nextScreen = buttonManager.GetScreen();
    buttonManager.ResetScreen();
    OpenClose();
  }
}
