#include "Token.h"

Token::Token(int _tag) {
  tag = _tag;
}

int Token::getTag() const {
  return tag;
}
