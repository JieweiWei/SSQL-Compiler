#ifndef NUMBER_H
#define NUMBER_H

#include "Token.h"

class Number : public Token {
public:
  Number(int _value);
  int getValue() const;
private:
  int value;
};

#endif // NUMBER_H
