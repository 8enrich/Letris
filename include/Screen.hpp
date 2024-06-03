#pragma once
#include "raylibFunctions.hpp"

class Screen {
public:
  Screen();
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
};
