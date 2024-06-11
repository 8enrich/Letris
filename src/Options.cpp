#include "../include/Options.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>

void Options::Tick(){
  if(IsMusicStreamPlaying(music)) {UpdateMusicStream(music);}
  OptionsHandling();
  int hasMoviment;
  do{
    hasMoviment = move[0] || move[1];
    BeginDrawing();
    Draw();
    EndDrawing();
  } while(hasMoviment);
  speed = 0;
}

void Options::Draw(){
  ClearBackground(BLACK);
  ray_functions::DrawFormatedText("OPÇÕES", Vec2<double>{(float)1/2, (float)1/20}, fontSizes[0], RAYWHITE);
  DrawControls();
  DrawScreenSize();
  float x = (float)1/2, y = (float)1/1.4, lineDistance = (float)5/42;
  ray_functions::DrawFormatedText("Aplicar", Vec2<double>{x, y}, fontSizes[0], optionsColor[2]);
  ray_functions::DrawFormatedText("Voltar", Vec2<double>{x, y + lineDistance}, fontSizes[0], optionsColor[3]);
}

void Options::DrawControls(){
  ray_functions::DrawFormatedText("Controles", Vec2<double>{(float)1/2, (float)1/5}, fontSizes[0], RAYWHITE);
  int width = settings::screenWidth, height = settings::screenHeight, y0 = height/4.6, lineDistance = height/20;
  int totalTextWidth = 0;
  for (int i = 0; i < NUM_COLS; i++) totalTextWidth += MeasureText(columns[i], height * fontSizes[1]);
  int margin = (width - totalTextWidth) / (NUM_COLS  + 1);
  int x0 = margin, textSize;
  for (int i = 0, x = x0; i < NUM_COLS; i++) {
    textSize = MeasureText(columns[i], height * fontSizes[1]);
    DrawText(columns[i], x, lineDistance + y0, height * fontSizes[1], RAYWHITE);
    x += textSize + margin;
  }
  for (int i = 0, posX, x = x0; i < NUM_COLS; i++) {
    textSize = MeasureText(columns[i], height * fontSizes[1]);
    posX = x + (textSize - MeasureText(controls[itemSelected[CONTROL]][i], height * fontSizes[1]))/2;
    if(!move[0]){
      DrawArrows((float)73/230, optionsColor[0]);
      DrawText(controls[itemSelected[CONTROL]][i], posX, 2 * lineDistance + y0, height * fontSizes[1], optionsColor[0]);
      x += textSize + margin;
      continue;
    }
    int previous = (move[0] > 0)? GetPreviousItemSelected(CONTROLS_QTD) : GetNextItemSelected(CONTROLS_QTD);
    speed += 30 * move[0];
    bool stop = ray_functions::HorizontalSlideAnimation(controls[previous][i], controls[itemSelected[CONTROL]][i], posX,
        2 * lineDistance + y0, speed, height * fontSizes[1], GRAY);
    x += textSize + margin;
    if(stop) move[0] = 0;
  }
}

void Options::DrawScreenSize(){
  ray_functions::DrawFormatedText("Tamanho da tela", Vec2<double>{(float)1/2, (float)1/2.7}, fontSizes[0], RAYWHITE);
  int width = settings::screenWidth, height = settings::screenHeight;
  const char *text = screenSizes[itemSelected[SCREENSIZE]];
  float x = (float)1/2, y = (float)1/2.3;
  if(!move[1]){
    DrawArrows(y, optionsColor[1]);
    ray_functions::DrawFormatedText(text, Vec2<double>{x, y}, fontSizes[1], optionsColor[1]);
    return;
  }
  bool stop;
  int previous = (move[1] > 0)? GetPreviousItemSelected(SCREEN_SIZE_QTD) : GetNextItemSelected(SCREEN_SIZE_QTD);
  speed += 100 * move[1];
  stop = ray_functions::HorizontalSlideAnimation(screenSizes[previous], text, x, y,
      speed, fontSizes[1], GRAY);
  if(stop) move[1] = 0;
}

void Options::DrawArrows(float y, Color color){
  ray_functions::DrawFormatedText("<", Vec2<double>{(float)1/36, y}, fontSizes[1], color);
  ray_functions::DrawFormatedText(">", Vec2<double>{(float)1/1.03, y}, fontSizes[1], color);
}

int Options::GetNextItemSelected(int quantity){
  return (itemSelected[currentSelected] + 1)%quantity;
}

int Options::GetPreviousItemSelected(int quantity){
  return (itemSelected[currentSelected] + (quantity * 2 - 1))%quantity;
}

void Options::OptionsHandling(){
  auto keypressed = GetKeyPressed();
  switch (keypressed) {
    case KEY_RIGHT:
      if(currentSelected < 2){
        itemSelected[currentSelected] = GetNextItemSelected(itemQuantity[currentSelected]);
        move[currentSelected] = 1;
      }
      break;
    case KEY_LEFT:
      if(currentSelected < 2){
        itemSelected[currentSelected] = GetPreviousItemSelected(itemQuantity[currentSelected]);
        move[currentSelected] = -1;
      }
      break;
    case KEY_UP:
      currentSelected = (currentSelected + (OPT_QTD_OPTIONS * 2 - 1))%OPT_QTD_OPTIONS;
      break;
    case KEY_DOWN:
      currentSelected = (currentSelected + 1)%OPT_QTD_OPTIONS;
      break;
  }
  for (int i = 0; i < OPT_QTD_OPTIONS; i++) optionsColor[i] = (i == currentSelected)? RAYWHITE : GRAY;
  for (int i = 0; i < CONTROLS_QTD; i++) controlsColor[i] = (i == itemSelected[currentSelected]) ? optionsColor[0] : GRAY;
  if (IsKeyPressed(KEY_ENTER)) {
    switch(currentSelected){
      case 2:
        if(itemSelected[CONTROL] != settings::db["CONTROL"]) {
          settings::db["CONTROL"] = itemSelected[CONTROL];
        }
        if(itemSelected[SCREENSIZE] != GetScreenSizeIndex())
          settings::UpdateWindowSize(settings::screenSizes[itemSelected[SCREENSIZE]]);
        return;
      case 3:
        OpenClose();
        currentSelected = 0;
        itemSelected[CONTROL] = settings::db["CONTROL"];
        itemSelected[SCREENSIZE] = GetScreenSizeIndex();
        break;
      default:
        return;
    }
  }
}

int Options::GetScreenSizeIndex(){
  for(int i = 0; i < SCREEN_SIZE_QTD; i++){
    if(settings::screenSizes[i].GetX() == GetScreenWidth()){
      return i;
    }
  }
  return 0;
}
