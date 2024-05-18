#include "../include/Menu.hpp"
#include "../include/Settings.hpp"
#include "../include/Window.hpp"
#include <raylib.h>
#include <assert.h>

Window::Window(int width, int height, int fps, std::string title)
{
  assert(!GetWindowHandle());
  SetTargetFPS(fps);
  InitWindow(width, height, title.c_str());
  SetExitKey(KEY_Q);
}

Window::~Window() noexcept{
  assert(GetWindowHandle());
  CloseWindow();
}
