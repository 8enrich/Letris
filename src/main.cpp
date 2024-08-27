#include "../include/Window.hpp"
#include "../include/Settings.hpp"
#include "../include/Menu.hpp"
#include "../include/Options.hpp"
#include "../include/Game.hpp"
#include "../include/Pause.hpp"
#include "../include/GameOver.hpp"
#include "../include/Coop.hpp"
#include "../include/ScreenManager.hpp"
#include "../include/CoopOptions.hpp"
#include <raylib.h>
#include <memory>
#include <iostream>
#include <exception>

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#endif

int main() {
    InitAudioDevice();
    Window window{settings::screenWidth, settings::screenHeight, settings::fps, "Letris"};
    try{
      Board board{settings::boardPosition, settings::boardWidthHeight,
                                          settings::cellSize, settings::padding};
      settings::SetCustomControls();
      ScreenManager screenManager;
      screenManager.AddScreen(GAME, nullptr);
      screenManager.AddScreen(COOP, nullptr);
      screenManager.AddScreen(COOPOPTIONS, std::make_unique<CoopOptions>());
      screenManager.AddScreen(OPTIONS, std::make_unique<Options>());
      screenManager.AddScreen(EXIT, nullptr);
      screenManager.AddScreen(MENU, std::make_unique<Menu>());
      screenManager.AddScreen(PAUSE, std::make_unique<Pause>());
      screenManager.AddScreen(GAMEOVER, std::make_unique<GameOver>());
      while(!IsWindowReady()){}
      if (!settings::db["WINDOWED"]) settings::FullScreen();
      while (!screenManager.ShouldClose()) {
          screenManager.ResetGameScreenIfNeeded(&board);
          screenManager.UpdateScreen();
      }
    }
    catch(std::exception& e){
      settings::db["LOG"] = e.what();
    }
    std::ofstream o(std::string(ASSETS_PATH)+ "user_settings.json");
    o << std::setw(4) << settings::db << std::endl;

    CloseAudioDevice();
    return 0;
}

