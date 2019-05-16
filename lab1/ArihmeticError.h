#ifndef ARIHMETIC_ERROR_H
#define ARIHMETIC_ERROR_H

#include <string>

enum class ErrorType
{
  ADD, SUBTRACT, MULTIPLY, ZERO_DIVISION
};

class ArihmeticError
{
public:
  ArihmeticError(ErrorType err);
  std::string what() const;
  ErrorType type() const;
private:
  ErrorType err_;
  static const char * const errorNames_[static_cast<int>(ErrorType::ZERO_DIVISION)+1];
};

#endif //ARIHMETIC_ERROR_H
