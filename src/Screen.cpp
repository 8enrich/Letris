#include "../include/Screen.hpp"

Screen::Screen(int previousScreen, int nextScreen) :
  previousScreen(previousScreen),
  nextScreen(nextScreen)
{};

void Screen::OpenClose() {
  shouldClose = !shouldClose;
}

bool Screen::ShouldClose(){
  return shouldClose;
}

void Screen::Draw(){}

void Screen::Tick(){}

int Screen::GetScreen(){ return screenToReturn;}
