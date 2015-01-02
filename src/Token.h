#ifndef TOKEN_H
#define TOKEN_H

#include "define.h"

class Token {
public:
  Token(int _tag);
  int getTag() const;
private:
  int tag;
};

#endif // TOKEN_H
