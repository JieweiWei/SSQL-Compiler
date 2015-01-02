#ifndef LEXER_H
#define LEXER_H

#include <map>
#include <istream>
#include <algorithm>
#include "Word.h"
#include "Number.h"

using std::map;
using std::pair;
using std::istream;

class Lexer {
public:
  Lexer(istream* _input);
  Token scan();
private:
  void reserve(Word word);
private:
  int line;
  char peek;
  istream* input;
  map<string, int> keywords;
};

#endif // LEXER_H
