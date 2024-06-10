#include "../include/Window.hpp"
#include "../include/Settings.hpp"
#include "../include/Menu.hpp"
#include "../include/Options.hpp"
#include "../include/Game.hpp"
#include "../include/Pause.hpp"
#include "../include/GameOver.hpp"
#include "../include/ScreenManager.hpp"
#include <raylib.h>
#include <memory>

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#endif

int main() {
    InitAudioDevice();
    Window window{settings::screenWidth, settings::screenHeight, settings::fps, "Letris"};

    std::unique_ptr<Board> board = nullptr;
    ScreenManager screenManager;
    screenManager.AddScreen(GAME, nullptr);
    screenManager.AddScreen(OPTIONS, std::make_unique<Options>());
    screenManager.AddScreen(EXIT, nullptr);
    screenManager.AddScreen(MENU, std::make_unique<Menu>());
    screenManager.AddScreen(PAUSE, std::make_unique<Pause>());
    screenManager.AddScreen(GAMEOVER, std::make_unique<GameOver>());
    
    while (!screenManager.ShouldClose()) {
        screenManager.ResetGameScreenIfNeeded(board);
        screenManager.UpdateScreen();
    }

    CloseAudioDevice();
    return 0;
}

