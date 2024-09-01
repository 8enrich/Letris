#include "Error.hpp"

class AllocError : public Error{
  public:
    explicit AllocError(const string &className, const string &atribute) : 
    Error("Erro na alocação de " + className + "::" + atribute) {};
};
