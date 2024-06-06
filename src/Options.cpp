#include "../include/Options.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>
#include <cstdio>

void Options::Tick(){
  if(IsMusicStreamPlaying(music)) {UpdateMusicStream(music);}
  OptionsHandling();
  do{
    BeginDrawing();
    Draw();
    EndDrawing();
  } while(move);
  speed = 0;
}

void Options::Draw(){
  ClearBackground(BLACK);
  int lastSize = 0, distance = 0, x0 = settings::screenWidth/14, y0 = settings::screenHeight/5, fontSize = 20;
  ray_functions::DrawFormatedText("Opções", Vec2<double>{(float)1/2, (float)1/20}, (float)1/fontSize, RAYWHITE);
  ray_functions::DrawFormatedText("Voltar", Vec2<double>{(float)1/2, (float)1/1.2}, (float)1/fontSize, optionsColor[1]);
  for(int i = 0; i < NUM_COLS; i++){
    if(i) distance = lastSize + MeasureText(columns[i - 1], fontSize) - MeasureText("     ", fontSize);
    lastSize = distance + x0;
    DrawText(columns[i], lastSize, y0, fontSize, RAYWHITE);
  }
  for(int i = 0; i < CONTROLS_QTD; i++){
    const char *selected = "";
    if(i == Game::control) selected = "Y";
    controls[i][6] = selected;
  }
  lastSize = 0, distance = 0;
  for (int i = 0, x; i < NUM_COLS; i++) {
    if(i) distance = lastSize + MeasureText(columns[i - 1], fontSize) - MeasureText("     ", fontSize);
    lastSize = distance + x0;
    x = lastSize + (MeasureText(columns[i], fontSize) - MeasureText(controls[controlSelected][i], fontSize))/2;
    if(!move){
      DrawText(controls[controlSelected][i], x, LINE_DISTANCE + y0, fontSize, controlsColor[controlSelected]);
      continue;
    }
    int previous = (move > 0)? GetPreviousControlSelected() : GetNextControlSelected();
    ray_functions::HorizontalSlideAnimation(controls[previous][i], controls[controlSelected][i], x, LINE_DISTANCE + y0, speed,
        fontSize, controlsColor[previous]);
    if((x - speed + settings::screenWidth < x && i == NUM_COLS - 1) ||
        x - speed - settings::screenWidth > x) move = 0;
    speed += ANIMATION_SPEED * move;
  }
}

int Options::GetNextControlSelected(){
  return (controlSelected + 1)%CONTROLS_QTD;
}

int Options::GetPreviousControlSelected(){
  return (controlSelected + (CONTROLS_QTD * 2 - 1))%CONTROLS_QTD;
}

void Options::OptionsHandling(){
  auto keypressed = GetKeyPressed();
  switch (keypressed) {
    case KEY_RIGHT:
      if(!currentSelected){
        controlSelected = GetNextControlSelected();
        move = 1;
      }
      break;
    case KEY_LEFT:
      if(!currentSelected){
        controlSelected = GetPreviousControlSelected();
        move = -1;
      }
      break;
    case KEY_UP:
      currentSelected = (currentSelected + 1)%OPT_QTD_OPTIONS;
      break;
    case KEY_DOWN:
      currentSelected = (currentSelected + (OPT_QTD_OPTIONS * 2 - 1))%OPT_QTD_OPTIONS;
      break;
  }
  for (int i = 0; i < OPT_QTD_OPTIONS; i++) optionsColor[i] = (i == currentSelected)? RAYWHITE : GRAY;
  for (int i = 0; i < CONTROLS_QTD; i++) controlsColor[i] = (i == controlSelected) ? optionsColor[0] : GRAY;
  if (IsKeyPressed(KEY_ENTER)) {
    switch(currentSelected){
      case 0:
        Game::control = controlSelected;
        break;
      case 1:
        nextScreen = MENU;
        OpenClose();
        currentSelected = 0;
        controlSelected = Game::control;
        break;
    }
  }
}
