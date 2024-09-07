#include "../include/ScreenManager.hpp"
#include <unordered_map>
#include <memory>
#include <raylib.h>

ScreenManager::ScreenManager() : actualScreen(MENU), lastScreen(EXIT), entered(false) {}

void ScreenManager::AddScreen(Screens type, std::unique_ptr<Screen> screen) {
    screens[type] = std::move(screen);
}

void ScreenManager::SetScreen(Screens type) {
    lastScreen = actualScreen;
    actualScreen = type;
}

void ScreenManager::UpdateScreen() {
    if (!screens[actualScreen]) return;
    if (!entered) {
        if (actualScreen == OPTIONS || actualScreen == STATS) screens[actualScreen]->SetNextScreen(lastScreen);
        if (lastScreen == COOP || lastScreen == GAME) screens[actualScreen]->SetNextScreen(lastScreen);
        if (actualScreen == GAMEOVER) SetScoreInGameOver();
        screens[actualScreen]->OpenClose();
        entered = true;
    }

    if (screens[actualScreen]->ShouldClose()) {
        entered = false;
        SetScreen(screens[actualScreen]->GetScreen());
        return;
    }

    screens[actualScreen]->Tick();
}

bool ScreenManager::ShouldClose() {
    return WindowShouldClose() || actualScreen == EXIT;
}

Screens ScreenManager::GetActualScreen() const {
    return actualScreen;
}

void ScreenManager::ResetGameScreenIfNeeded(Board *board) {
  if (!entered){
    board->ResetBoardSettings();
    if (lastScreen == SOLOOPTIONS || lastScreen == GAMEOVER || lastScreen == COOPOPTIONS){
      switch(actualScreen){
        case GAME:
          screens[actualScreen] = std::make_unique<Game>(board);
          break;
        case COOP:
          screens[actualScreen] = std::make_unique<Coop>(board);
          break;
        default:
          return;
      }

    }
    Music music = screens[actualScreen]->GetMusic();
    if(IsMusicReady(music) && IsMusicStreamPlaying(music))
      SetMusicVolume(music, (float)settings::db["VOLUME"]/100);
  }
}

void ScreenManager::SetScoreInGameOver(){
  Screen *gameOverScreen = screens[GAMEOVER].get(), *gameScreen = screens[lastScreen].get();
  GameOver *gameOver = dynamic_cast<GameOver*>(gameOverScreen);
  Game *game = dynamic_cast<Game*>(gameScreen);
  if(gameOver && game){
    gameOver->SetScore(game->GetScore());
    gameOver->SetLevel(game->GetLevel());
    gameOver->SetHighscores();
    gameOver->SetHighslevels();
  }
}

