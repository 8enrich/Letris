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
  void OpenClose();
  virtual void Tick();
  int GetScreen();
protected:
  bool shouldClose = true;
  virtual void Draw();
  int nextScreen;
  Music music;
  std::string musicPath;
};
