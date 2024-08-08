#include "../include/ScreenManager.hpp"
#include <iostream>
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
        if (actualScreen == OPTIONS) screens[actualScreen]->SetNextScreen(lastScreen);
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
    switch(actualScreen){
      case GAME:
        gameScreenIndex = GAME;
        break;
      case COOP:
        gameScreenIndex = COOP;
        break;
      default:
        return;
    }
    board->ResetBoardSettings();
    if (lastScreen == MENU || lastScreen == GAMEOVER) screens[gameScreenIndex] = std::make_unique<Game>(board);
    SetMusicVolume(screens[gameScreenIndex]->GetMusic(), (float)settings::db["VOLUME"]/100);
  }
}

void ScreenManager::SetScoreInGameOver(){
  Screen *gameOverScreen = screens[GAMEOVER].get(), *gameScreen = screens[gameScreenIndex].get();
  GameOver *gameOver = dynamic_cast<GameOver*>(gameOverScreen);
  Game *game = dynamic_cast<Game*>(gameScreen);
  if(gameOver && game){
    gameOver->SetScore(game->GetScore());
    gameOver->SetHighscores();
  }
}

