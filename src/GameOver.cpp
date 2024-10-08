#include "../include/GameOver.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>

void GameOver::Tick(){
  if(IsMusicStreamPlaying(music)) {UpdateMusicStream(music);}
  OptionsHandling();
  BeginDrawing();
  Draw();
  buttonManager.Tick();
  EndDrawing();
}

void GameOver::Draw(){
  ClearBackground(BLACK);
  ray_functions::DrawImage(bgImage);
  ray_functions::DrawFormatedText("GAME OVER", Vec2<double>{1.0f/2, 1.0f/5}, 1.0f/13, RAYWHITE);
  DrawScores();
}

void GameOver::DrawScores(){
  ray_functions::DrawFormatedText("Score:", Vec2<double>{1.0f/4, 1/3.2}, fontSize, RAYWHITE);
  ray_functions::DrawFormatedText(TextFormat("%d", score), Vec2<double>{1.0f/4, 1/2.6}, fontSize, RAYWHITE);
  if(hasNewHighscore) ray_functions::DrawFormatedText("New HighScore!", Vec2<double>{1.0f/2, 1/1.8}, fontSize, RAYWHITE);
  ray_functions::DrawFormatedText("Level:", Vec2<double>{3.0f/4, 1/3.2}, fontSize, RAYWHITE);
  ray_functions::DrawFormatedText(TextFormat("%d", level), Vec2<double>{3.0f/4, 1/2.6}, fontSize, RAYWHITE);
}

void GameOver::OptionsHandling(){
  if (buttonManager.GetScreen() != NOTSCREEN) {
    nextScreen = buttonManager.GetScreen();
    buttonManager.ResetScreen();
    OpenClose();
    if(nextScreen == GAME || nextScreen == COOP){
      hasNewHighscore = false;
    }
  }
}

void GameOver::SetScore(int newScore){
  score = newScore;
}

void GameOver::SetHighscores(){
  for(int i = 0; i < 5; i++){ 
    if(score > settings::highscores[i]){
      for(int j = 4; j > i; j--){
        settings::highscores[j] = settings::highscores[j - 1];
        settings::highlevels[j] = settings::highlevels[j - 1];
        settings::db["HIGHSCORES"][j] = settings::highscores[j];
        settings::db["HIGHLEVELS"][j] = settings::highlevels[j];
      }
      settings::highscores[i] = score;
      settings::highlevels[i] = level;
      hasNewHighscore = true;
      settings::db["HIGHSCORES"][i] = settings::highscores[i]; 
      settings::db["HIGHLEVELS"][i] = settings::highlevels[i];
      break;
    }
  }
}

void GameOver::OpenClose(){
  Screen::OpenClose();
  if(nextScreen == GAME || nextScreen == COOP) PlayAgain.SetScreen(nextScreen);
}

void GameOver::SetLevel(int level){
  this->level = level;
}
