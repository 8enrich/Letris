#include "../include/Menu.hpp"
#include "../include/Settings.hpp"
#include <raylib.h>
#include <assert.h>
void Menu::Draw(){
  OptionsHandling();
  BeginDrawing();
  ClearBackground(BLACK);
  DrawText("LETRIS", settings::screenWidth/3, settings::screenHeight/3, settings::screenHeight/10, RED);
  DrawText("Jogar", settings::screenWidth/4, settings::screenHeight/1.5, settings::screenHeight/15, optionsColor[0]);
  DrawText("Sair", settings::screenWidth/1.75, settings::screenHeight/1.5, settings::screenHeight/15, optionsColor[1]);
  EndDrawing();
}
Menu::Menu(int width, int height, int fps, std::string title)
{
  assert(!GetWindowHandle());
  SetTargetFPS(fps);
  InitWindow(width, height, title.c_str());
  SetExitKey(KEY_Q);
}

void Menu::OptionsHandling(){
  auto keypressed = GetKeyPressed();
  bool entered = false;
  switch (keypressed) {
    case KEY_RIGHT:
      currentSelected < OPT_QTD - 1 ? ++currentSelected : currentSelected = 0;
      entered = true;
      break;
    case KEY_LEFT:
      entered = true;
      currentSelected > 0 ? currentSelected-- : currentSelected = OPT_QTD-1;
      break;
  }
  if (entered) {
    for (int i = 0; i < OPT_QTD; i++) { optionsColor[i] = i == currentSelected ? RAYWHITE : GRAY; }
  }
  if (IsKeyPressed(KEY_ENTER)) {
    switch (currentSelected) {
      case 0:
        shouldClose = true;
        break;
      case 1:
        CloseWindow();
        break;
    }
  }
}
void Menu::OpenCloseMenu() {
  shouldClose = !shouldClose;
}
Menu::~Menu() noexcept{
  assert(GetWindowHandle());
  CloseWindow();
}

bool Menu::MenuShouldClose(){
  return shouldClose;
}
