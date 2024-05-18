#include <raylib.h>
#include <string>
class Window {
public:
  Window(int,int,int, std::string);
  ~Window() noexcept;
};
