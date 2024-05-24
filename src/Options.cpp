#include "../include/Options.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>

void Options::Tick(){
  OptionsHandling();
  BeginDrawing();
  Draw();
  EndDrawing();
}

void Options::Draw(){
  ClearBackground(BLACK);
  const char *columns[NUM_COLS] = {"Rotate CW", "Left", "Down", "Right", "Instant Fall", "Rotate ACW", "Selected"};
  const char *controls[OPT_QTD_OPTIONS - 1][NUM_COLS] = {
    {"W", "A", "S", "D", "SPACE", "Z", ""},
    {"^", "<", ">", "v", "SPACE", "Z", ""},
    {"I", "J", "K", "L", "SPACE", "Z", ""},
    {"K", "H", "H", "L", "SPACE", "Z", ""},
  };
  int width = settings::screenWidth/14, height = settings::screenHeight/5;
  int fontSize = 20, lastSize = 0, distance = 0;
  const char *selected = "";
  for(int j = 0; j < NUM_COLS; j++){
    if(j) distance = lastSize + MeasureText(columns[j - 1], fontSize) - MeasureText("     ", fontSize);
    lastSize = distance + width;
    DrawText(columns[j], lastSize, height, fontSize, RAYWHITE);
  }
  for (int i = 0; i < OPT_QTD_OPTIONS - 1; i++) {
    lastSize = 0, distance = 0;
    selected = "";
    if(i == controlSelected) selected = "Y";
    controls[i][6] = selected;
    for (int j = 0; j < NUM_COLS; j++) {
      if(j) distance = lastSize + MeasureText(columns[j - 1], fontSize) - MeasureText("     ", fontSize);
      lastSize = distance + width;
      DrawText(controls[i][j], lastSize + (MeasureText(columns[j], fontSize) - MeasureText(controls[i][j], fontSize))/2,
          (i + 1) * 40 + height, fontSize, optionsColor[i]);
    }
  }
  ray_functions::DrawFormatedText("Voltar", Vec2<double>{(float)1/2, (float)1/1.2}, (float)1/fontSize, optionsColor[4]);
}

void Options::OptionsHandling(){
  auto keypressed = GetKeyPressed();
  switch (keypressed) {
    case KEY_DOWN:
      currentSelected = (currentSelected + 1)%OPT_QTD_OPTIONS;
      break;
    case KEY_UP:
      currentSelected = (currentSelected + 9)%OPT_QTD_OPTIONS;
      break;
  }
  for (int i = 0; i < OPT_QTD_OPTIONS; i++) { optionsColor[i] = (i == currentSelected) ? RAYWHITE : GRAY; }
  if (IsKeyPressed(KEY_ENTER)) {
    if(currentSelected < 4){
      controlSelected = currentSelected;
      Game::control = currentSelected;
      return;
    }
    nextScreen = MENU;
    OpenClose();
    currentSelected = 0;
    }
}
