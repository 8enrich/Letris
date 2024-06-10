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
    if (actualScreen != EXIT) {
        lastScreen = actualScreen;
        actualScreen = type;
        entered = false; // Ensure that the new screen gets properly opened
    }
}

void ScreenManager::UpdateScreen() {
    if (!entered) {
        screens[actualScreen]->OpenClose();
        entered = true;
    }

    if (screens[actualScreen]->ShouldClose()) {
        screens[actualScreen]->OpenClose(); // Close current screen

        if (actualScreen == OPTIONS) {
            actualScreen = lastScreen;
        } else {
            lastScreen = actualScreen;
            actualScreen = screens[actualScreen]->GetScreen();
        }
    }

    if(screens[actualScreen]) screens[actualScreen]->Tick();
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

