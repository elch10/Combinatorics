#include "ArihmeticError.h"
#include <string>

ArihmeticError::ArihmeticError(ErrorType err):
  err_(err)
{}

std::string ArihmeticError::what() const
{
  std::string errorMessage = "Переполнение произошло при ";
  switch (err_)
  {
    case ErrorType::ADD:
      errorMessage += "суммировании";
      break;
    case ErrorType::SUBTRACT:
      errorMessage += "вычитании";
      break;
    case ErrorType::MULTIPLY:
      errorMessage += "умножении";
      break;
    case ErrorType::ZERO_DIVISION:
      errorMessage += "делении на ноль";
      break;
    default:
      break;
  }
  return errorMessage;
}

ErrorType ArihmeticError::type() const
{
  return err_;
}
