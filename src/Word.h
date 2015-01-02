#ifndef WORD_H
#define WORD_H

#include <string>
#include "Token.h"

using std::string;

class Word : public Token {
public:
  Word(int _tag, string _lexeme);
  string getLexeme() const;
private:
  string lexeme;
};

#endif // WORD_H
