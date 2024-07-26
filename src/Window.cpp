#include "../include/Window.hpp"
#include <raylib.h>
#include <assert.h>

Window::Window(int width, int height, int fps, std::string title)
{
  assert(!GetWindowHandle());
  SetTargetFPS(fps);
  InitWindow(width, height, title.c_str());
  //SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE); // Para o futuro. :D
  SetExitKey(KEY_Q);
}

Window::~Window() noexcept{
  assert(GetWindowHandle());
  CloseWindow();
}
