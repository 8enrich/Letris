#include "../include/Window.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>
#include <assert.h>

Window::Window(int width, int height, int fps, std::string title)
{
  assert(!GetWindowHandle());
  SetTargetFPS(fps);
  InitWindow(width, height, title.c_str());
  Image wicon = LoadImage((std::string(ASSETS_PATH) + "letris.png").c_str());
  SetWindowIcon(wicon);
  UnloadImage(wicon);
  SetExitKey(KEY_NULL);
}

Window::~Window() noexcept{
  assert(GetWindowHandle());
  CloseWindow();
}
