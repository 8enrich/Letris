#include "../include/Options.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>
#include <cstdio>

void Options::Tick(){
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
  ray_functions::DrawFormatedText("Opções", Vec2<double>{(float)1/2, (float)1/20}, (float)1/fontSize, RAYWHITE);
  ray_functions::DrawFormatedText("Voltar", Vec2<double>{(float)1/2, (float)1/1.2}, (float)1/fontSize, optionsColor[1]);
  int lastSize = 0, distance = 0;
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
  if(!move){
    lastSize = 0, distance = 0;
    for (int i = 0; i < NUM_COLS; i++) {
      if(i) distance = lastSize + MeasureText(columns[i - 1], fontSize) - MeasureText("     ", fontSize);
      lastSize = distance + x0;
      DrawText(controls[controlSelected][i], lastSize + (MeasureText(columns[i], fontSize) -
        MeasureText(controls[controlSelected][i], fontSize))/2 - speed, LINE_DISTANCE + y0,
          fontSize, controlsColor[controlSelected]);
    }
    return;
  }
  SlideAnimation();
}

void Options::SlideAnimation(){
  int lastSize = 0, distance = 0;
  int previous, selected = controlSelected;
  previous = (move > 0)? GetPreviousControlSelected() : GetNextControlSelected();
  for (int i = 0; i < NUM_COLS; i++) {
    if(i) distance = lastSize + MeasureText(columns[i - 1], fontSize) - MeasureText("     ", fontSize);
    lastSize = distance + x0;
    DrawText(controls[previous][i], lastSize + (MeasureText(columns[i], fontSize) -
          MeasureText(controls[previous][i], fontSize))/2 - speed, LINE_DISTANCE + y0, fontSize, controlsColor[previous]);
    if(lastSize - speed < 0 || lastSize - speed > settings::screenWidth)
      DrawText(controls[selected][i], lastSize + (move * settings::screenWidth) + (MeasureText(columns[i], fontSize) -
          MeasureText(controls[selected][i], fontSize))/2 - speed, LINE_DISTANCE + y0, fontSize, controlsColor[selected]);
    if((lastSize - speed < 0 && i == NUM_COLS - 1) ||
        x0 - speed > settings::screenWidth) move = 0;
  }
  speed += ANIMATION_SPEED * move;
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
