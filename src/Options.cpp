#include "../include/Options.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>
#include <string>

void Options::Tick(){
  if(IsMusicStreamPlaying(music)) {UpdateMusicStream(music);}
  //OptionsHandling();
  int hasMovement;
  //do{
  //  hasMovement = move[0] || move[1];
    BeginDrawing();
    Draw();
    buttonManager.Tick();
    EndDrawing();
  //} while(hasMovement);
  speed = 0;
  currentSelected = buttonManager.GetCurrentSelected(currentSelected);
  std::string resolutionString = screenSizeButton->GetText();
  if (selectedResolution != resolutionString) SetNewResolution(resolutionString);
  if(buttonManager.GetScreen() != NOTSCREEN) {
    nextScreen = buttonManager.GetScreen();
    buttonManager.ResetScreen();
    OpenClose();
  }
}

void Options::Draw() {
  ClearBackground(BLACK);
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
//  DrawHeader();
//  DrawControls();
//  DrawVolume();
//  DrawButtons();
}

void Options::OpenClose(){
  Screen::OpenClose();
  if(!shouldClose) returnButton->SetScreen(nextScreen);
}

int Options::GetResolutionIndex(std::string resolution){
  for(int i = 0; i < SCREEN_SIZE_QTD; i++){
    if(resolution == screenSizes2[i]) return i;
  }
  return 0;
}

void Options::SetNewResolution(std::string resolution){
  int index = GetResolutionIndex(resolution);
  settings::UpdateWindowSize(settings::screenSizes[index]);
  selectedResolution = resolution;
}

void Options::DrawGeneral(){
  ray_functions::DrawFormatedText("Resolution:", Vec2<double>{1.0f/3, 1.0f/3}, fontSizes[1], RAYWHITE);
  ray_functions::DrawFormatedText("Window Mode:", Vec2<double>{1.0f/3, 1/2.3}, fontSizes[1], RAYWHITE);
}

void Options::DrawHeader() {
  ray_functions::DrawFormatedText("OPTIONS", Vec2<double>{1.0f/2, 1.0f/20}, fontSizes[0], RAYWHITE);
}

void Options::DrawButtons() {
  float x = 1.0f/2, y = 1.0f/1.4, lineDistance = 5.0f/42;
  ray_functions::DrawFormatedText("Apply", Vec2<double>{x, y}, fontSizes[0], optionsColor[3]);
  ray_functions::DrawFormatedText("Back", Vec2<double>{x, y + lineDistance}, fontSizes[0], optionsColor[4]);
}
void Options::DrawControls() {
  ray_functions::DrawFormatedText("Controls:", Vec2<double>{1.0f/3.2, 1.0f/3}, fontSizes[1], RAYWHITE);
}

void Options::DrawSectionHeader(const char* text, float yPos) {
  ray_functions::DrawFormatedText(text, Vec2<double>{1.0f/2, yPos}, fontSizes[0], RAYWHITE);
}

int Options::CalculateTotalTextWidth() {
  int totalTextWidth = 0;
  int height = settings::screenHeight;
  std::string column;
  size_t columnIndex = 0;
  for (int i = 0; i < NUM_COLS; i++) {
      column = GetText(columns, columnIndex);
      totalTextWidth += MeasureText(column.c_str(), height * fontSizes[1]);
  }
  return totalTextWidth;
}

void Options::DrawColumns(int y, int margin) {
  int height = settings::screenHeight;
  std::string text;
  int x0 = margin, textSize;
  size_t textIndex = 0;
  for (int i = 0, x = x0; i < NUM_COLS; i++) {
      text = GetText(columns, textIndex);
      textSize = MeasureText(text.c_str(), height * fontSizes[1]);
      DrawText(text.c_str(), x, y, height * fontSizes[1], RAYWHITE);
      x += textSize + margin;
  }
}

std::string Options::GetText(const std::string textTotal, size_t& pos){
  std::string text;
  size_t startPos = pos;
  while (pos < textTotal.length() && textTotal[pos] != ',') pos++;
  text = textTotal.substr(startPos, pos - startPos);
  if (pos < textTotal.length()) pos++;
  return text;
}

void Options::DrawControlOptions(int y, int margin) {
  int height = settings::screenHeight;
  int x0 = margin;
  std::string column, text;
  size_t columnIndex = 0, textIndex = 0;
  for (int i = 0, posX, x = x0; i < NUM_COLS; i++) {
    column = GetText(columns, columnIndex);
    text = GetText(controls[itemSelected[CONTROL]], textIndex);
    int textSize = MeasureText(column.c_str(), height * fontSizes[1]);
    posX = x + (textSize - MeasureText(text.c_str(), height * fontSizes[1])) / 2;
    if (!move[0]) {
      DrawArrows(y, optionsColor[0]);
      DrawText(text.c_str(), posX, y, height * fontSizes[1], optionsColor[0]);
      x += textSize + margin;
      continue;
    }
    int previous = (move[0] > 0) ? GetPreviousItemSelected(CONTROLS_QTD) : GetNextItemSelected(CONTROLS_QTD);
    speed += 30 * move[0];
    size_t previousIndex = 0;
    std::string previousStr = GetText(controls[previous], previousIndex);
    bool stop = ray_functions::HorizontalSlideAnimation(previousStr.c_str(), text.c_str(), posX,
        y, speed, height * fontSizes[1], GRAY);
    x += textSize + margin;
    if (stop) move[0] = 0;
  }
}

void Options::DrawScreenSize() {
  DrawSectionHeader("Screen Resolution", y0);
//  const char* text = screenSizes[itemSelected[SCREENSIZE]];
//  float x = (float)1/2, y = y0 + factor++ * lineDistance;
//  if (!move[1]) {
//      DrawArrows(y, optionsColor[1]);
//      ray_functions::DrawFormatedText(text, Vec2<double>{x, y}, fontSizes[1], optionsColor[1]);
//      return;
//  }
//  bool stop;
//  int previous = (move[1] > 0) ? GetPreviousItemSelected(SCREEN_SIZE_QTD) : GetNextItemSelected(SCREEN_SIZE_QTD);
//  speed += 100 * move[1];
//  stop = ray_functions::HorizontalSlideAnimation(screenSizes[previous], text, x, y,
//      speed, fontSizes[1], GRAY);
//  if (stop) move[1] = 0;
}

void Options::DrawVolume(){
  DrawSectionHeader("Volume", y0 + factor++ * lineDistance);

  int width = settings::screenWidth, height = settings::screenHeight;
  float xBegin = (float)width/2 - (float)width/8, xEnd = (float)width/2 + (float)width/8,
        y = y0 + factor++ * lineDistance, y1 = y + (float)1/50;
  DrawArrows(y, optionsColor[2]);
  DrawLineEx((Vector2){xBegin, height * y1}, (Vector2){xEnd, height * y1}, (float)height/200, optionsColor[2]);
  DrawCircleV({(xEnd - xBegin) * (float)volume/100 + xBegin, height * y1},
      (float)height/100, optionsColor[2]);
  ray_functions::DrawFormatedText(TextFormat("%d% %", volume), Vec2<double>{1.0f/2 + 1.0f/6, y},
      fontSizes[1], optionsColor[2]);
}

void Options::DrawArrows(double y, Color color) {
  ray_functions::DrawFormatedText("<", Vec2<double>{1.0f/36, y}, fontSizes[1], color);
  ray_functions::DrawFormatedText(">", Vec2<double>{1.0f/1.03, y}, fontSizes[1], color);
}

void Options::DrawArrows(int y, Color color){
  int width = settings::screenWidth, height = settings::screenHeight;
  int xLeft = width/36, xRight = width/1.03;
  DrawText("<", xLeft, y, height * fontSizes[1], color);
  DrawText(">", xRight, y, height * fontSizes[1], color);
}

int Options::GetNextItemSelected(int quantity) {
  return (itemSelected[currentSelected] + 1) % quantity;
}

int Options::GetPreviousItemSelected(int quantity) {
  return (itemSelected[currentSelected] + quantity - 1) % quantity;
}

void Options::OptionsHandling() {
  auto keypressed = GetKeyPressed();
  switch (keypressed) {
  case KEY_RIGHT:
    HandleArrowKey(1);
    break;
  case KEY_LEFT:
    HandleArrowKey(-1);
    break;
  case KEY_UP:
    currentSelected = (currentSelected + OPT_QTD_OPTIONS - 1) % OPT_QTD_OPTIONS;
    break;
  case KEY_DOWN:
    currentSelected = (currentSelected + 1) % OPT_QTD_OPTIONS;
    break;
  }
  if(currentSelected == 2){
    if(IsKeyDown(KEY_RIGHT) && volume < 100) volume += 1;
    if(IsKeyDown(KEY_LEFT) && volume > 0) volume -= 1;
  }
  UpdateColors();
  HandleEnterKey();
}

void Options::HandleArrowKey(int direction) {
  if (currentSelected < 2) {
    itemSelected[currentSelected] = (direction > 0) ? GetNextItemSelected(itemQuantity[currentSelected]) : GetPreviousItemSelected(itemQuantity[currentSelected]);
    move[currentSelected] = direction;
  }
}

void Options::UpdateColors() {
  for (int i = 0; i < OPT_QTD_OPTIONS; i++) optionsColor[i] = (i == currentSelected) ? RAYWHITE : GRAY;
  for (int i = 0; i < CONTROLS_QTD; i++) controlsColor[i] = (i == itemSelected[currentSelected]) ? optionsColor[0] : GRAY;
}

void Options::HandleEnterKey() {
  if (IsKeyPressed(KEY_ENTER)) {
    switch (currentSelected) {
      case 2:
        if(volume != 0){
          volume = 0;
          break;
        }
        volume = settings::db["VOLUME"];
        break;
      case 3:
        if (itemSelected[CONTROL] != settings::db["CONTROL"]) settings::db["CONTROL"] = itemSelected[CONTROL];
        if (itemSelected[SCREENSIZE] != GetScreenSizeIndex())
          settings::UpdateWindowSize(settings::screenSizes[itemSelected[SCREENSIZE]]);
        if(volume != settings::db["VOLUME"]) settings::db["VOLUME"] = volume;
        return;
      case 4:
        OpenClose();
        currentSelected = 0;
        itemSelected[CONTROL] = settings::db["CONTROL"];
        itemSelected[SCREENSIZE] = GetScreenSizeIndex();
        volume = settings::db["VOLUME"];
        break;
      default:
        return;
    }
  }
}

int Options::GetScreenSizeIndex() {
  for (int i = 0; i < SCREEN_SIZE_QTD; i++){
    if(settings::screenSizes[i].GetX() == GetScreenWidth()) return i;
  }
  return 0;
}
