#include "Word.h"

Word::Word(int _tag, string _lexeme) : Token(_tag) {
  lexeme = _lexeme;
}

string Word::getLexeme() const {
  return lexeme;
}
