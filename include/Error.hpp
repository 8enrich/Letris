#include <exception>
#include <string>

using namespace std;

class Error : public exception{
  public:
    explicit Error(const string& description) : description(description) {}
    virtual const char *what() const noexcept override {
      return description.c_str();
    }
  private:
    string description;
};
