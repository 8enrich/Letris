#pragma once
#include "raylibFunctions.hpp"
#include <string>

class Screen {
public:
  Screen();
  Screen(std::string musicPath);
  ~Screen();
  Screen(const Screen& other) = delete;
	Screen& operator=(const Screen& other) = delete;
  bool ShouldClose();
  virtual void OpenClose();
  virtual void Tick();
  Screens GetScreen();
  Music GetMusic();
  void SetNextScreen(Screens);
protected:
  bool shouldClose = true;
  virtual void Draw();
  void GoToScreen(Screens screen);
  Screens nextScreen;
  Music music;
  std::string musicPath;
};
