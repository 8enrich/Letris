#include "../include/Stats.hpp"
#include "raylib.h"

Stats::Stats():
  returnButton(ScreenButton("<", Vec2<double>{1.0f/30, 1.0f/50}, 1.0f/20, MENU)),
  buttonManager(new ButtonManager(buttons))
{}

Stats::~Stats(){
  for(Button *button : buttons) delete button;
  delete buttonManager;
}

void Stats::Tick(){
  OptionsHandling();
  BeginDrawing();
  Draw();
  buttonManager->Tick();
  EndDrawing();
}

void Stats::Draw(){
  ClearBackground(BLACK);
  ray_functions::DrawFormatedText("HIGHSCORES", Vec2<double>{1.0f/2, 1.0f/5}, 1.0f/13, RAYWHITE);
  ray_functions::DrawFormatedText("Scores:", Vec2<double>{1.0f/4, 1.0f/3.5}, 1.0f/20, RAYWHITE);
  ray_functions::DrawFormatedText("Levels:", Vec2<double>{3.0f/4, 1.0f/3.5}, 1.0f/20, RAYWHITE);
  for(int i = 0; i < 5; i++){
    ray_functions::DrawFormatedText(TextFormat("%d", settings::highscores[i]), Vec2<double>{1.0f/4, (1 + 0.17 *(i + 1))/3.2},
        1.0f/20, RAYWHITE);
    ray_functions::DrawFormatedText(TextFormat("%d", settings::highlevels[i]), Vec2<double>{3.0f/4, (1 + 0.17 *(i + 1))/3.2},
        1.0f/20, RAYWHITE);

  }
}

void Stats::OptionsHandling(){
  Screens screen = buttonManager->GetScreen();
  if(screen != NOTSCREEN){
    buttonManager->ResetScreen();
    nextScreen = screen;
    OpenClose();
  }
  if(GetKeyPressed() == KEY_ESCAPE) OpenClose();
}

void Stats::OpenClose(){
  Screen::OpenClose();
  if(!shouldClose){
  	returnButton.SetScreen(nextScreen);
  }
}
