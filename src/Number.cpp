#include "Number.h"

Number::Number(int _value) : Token(NUM) {
  value = _value;
}

int Number::getValue() const {
  return value;
}
