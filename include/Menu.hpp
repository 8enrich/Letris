#include <raylib.h>
#include <string>
#define OPT_QTD 2
class Menu {
public:
  Menu(int width , int height,int fps, std::string title);
  Menu(const Menu& other) = delete;
	Menu& operator=(const Menu& other) = delete;
  ~Menu() noexcept; 
  void Draw();
  bool MenuShouldClose();
  void OpenCloseMenu();
private:
  bool shouldClose = false;
  void OptionsHandling();
  int currentSelected = 0;
  Color optionsColor[OPT_QTD] = {RAYWHITE, GRAY};
};
