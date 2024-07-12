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
        screens[actualScreen]->OpenClose();
        entered = true;
    }

    if (screens[actualScreen]->ShouldClose()) {
        entered = false;
        if (actualScreen == OPTIONS) actualScreen = lastScreen;
        else SetScreen(screens[actualScreen]->GetScreen());
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
    if (!entered && actualScreen == GAME){
      board->ResetBoardSettings();
      if (lastScreen == MENU || lastScreen == GAMEOVER){
        board->ResetBoardCells();
        screens[GAME] = std::make_unique<Game>(board);
      }
      SetMusicVolume(screens[GAME]->GetMusic(), (float)settings::db["VOLUME"]/100);
    }
}

