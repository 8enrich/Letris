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
    }

    if (screens[actualScreen]) screens[actualScreen]->Tick();
}

bool ScreenManager::ShouldClose() {
    return WindowShouldClose() || actualScreen == EXIT;
}

Screens ScreenManager::GetActualScreen() const {
    return actualScreen;
}

void ScreenManager::ResetGameScreenIfNeeded(std::unique_ptr<Board>& board) {
    if (actualScreen == GAME && (lastScreen == MENU || lastScreen == GAMEOVER)) {
        board = std::make_unique<Board>(settings::boardPosition, settings::boardWidthHeight,
                                        settings::cellSize, settings::padding);
        screens[GAME] = std::make_unique<Game>(*board);
    }
}

