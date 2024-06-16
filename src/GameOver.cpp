#include "../include/GameOver.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>

void GameOver::Tick(){
  if(IsMusicStreamPlaying(music)) {UpdateMusicStream(music);}
  OptionsHandling();
  BeginDrawing();
  Draw();
  EndDrawing();
}

void GameOver::Draw(){
  ClearBackground(BLACK);
  ray_functions::DrawFormatedText("GAME OVER", Vec2<double>{(float)1/2, (float)1/5}, (float) 1/13, RAYWHITE);
  float x = (float)1/2, y = (float)1/2.5, fontSize = (float)1/20, lineDistance = (float)7/45;
  ray_functions::DrawFormatedText("Play Again", Vec2<double>{x, y}, fontSize, optionsColor[0]);
  ray_functions::DrawFormatedText("Options", Vec2<double>{x, y + lineDistance}, fontSize, optionsColor[1]);
  ray_functions::DrawFormatedText("Back to Main Menu", Vec2<double>{x, y + 2 * lineDistance}, fontSize, optionsColor[2]);
}

void GameOver::OptionsHandling(){
  auto keypressed = GetKeyPressed();
  switch (keypressed) {
    case KEY_DOWN:
      currentSelected = (currentSelected + 1)%OPT_QTD;
      break;
    case KEY_UP:
      currentSelected = (currentSelected + (OPT_QTD * 2 - 1))%OPT_QTD;
      break;
  }
  for (int i = 0; i < OPT_QTD; i++) { optionsColor[i] = (i == currentSelected) ? RAYWHITE : GRAY; }
  if (IsKeyPressed(KEY_ENTER)) {
    switch (currentSelected) {
      case 0:
        nextScreen = GAME;
        break;
      case 1:
        nextScreen = OPTIONS;
        break;
      case 2:
        nextScreen = MENU;
        break;
    }
    OpenClose();
    currentSelected = 0;
  }
}
