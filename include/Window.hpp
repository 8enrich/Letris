#include <string>
#include <raylib.h>
class Window {
public:
  Window(int,int,int, std::string);
  ~Window() noexcept;
  Music music;
};
