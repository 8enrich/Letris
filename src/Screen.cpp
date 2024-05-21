#include "../include/Screen.hpp"

Screen::Screen() {};

void Screen::OpenClose() {
  shouldClose = !shouldClose;
}

bool Screen::ShouldClose(){
  return shouldClose;
}

void Screen::Draw(){}

void Screen::Tick(){}

int Screen::GetScreen(){ return nextScreen;}
