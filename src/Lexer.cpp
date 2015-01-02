#include "Lexer.h"

// for test
/*#include <iostream>
#include <cstdio>
using namespace std;*/

Lexer::Lexer(istream* _input) {
  line = 1;
  peek = '\0';
  input = _input;

  reserve(Word(CREATE, string("create")));
  reserve(Word(TABLE, string("table")));
  reserve(Word(INT, string("int")));
  reserve(Word(DEFAULT, string("default")));
  reserve(Word(PRIMARY, string("primary")));
  reserve(Word(KEY, string("key")));
  reserve(Word(INSERT, string("insert")));
  reserve(Word(INTO, string("into")));
  reserve(Word(VALUES, string("values")));
  reserve(Word(DELETE, string("delete")));
  reserve(Word(FROM, string("from")));
  reserve(Word(WHERE, string("where")));
  reserve(Word(SELECT, string("select")));
}

Token Lexer::scan() {
  /* Ignore whitespace. */
  while (true) {
    input->get(peek);
    if (peek == ' ' || peek == '\t') {
      continue;
    } else if (peek == '\n') {
      line += 1;
    } else {
      break;
    }
  }

  /* Handler identifies or keywords. */
  if (isalpha(peek) || peek == '_') {
    string lexeme;
    do {
      lexeme.push_back(peek);
      input->get(peek);
    } while (isalpha(peek) || isdigit(peek) || peek == '_');
    input->putback(peek);
    string lowerLexeme = lexeme;
    transform(lexeme.begin(), lexeme.end(), lowerLexeme.begin(), ::tolower);
    map<string, int>::iterator it = keywords.find(lowerLexeme);

    Word w = it == keywords.end() ? Word(ID, lexeme) : Word(it->second, it->first);
    //cout << "(" << w.getLexeme() << ", " << w.getTag() << ")" << endl;

    return it == keywords.end() ? Word(ID, lexeme) : Word(it->second, it->first);
  }

  /* Handler numbers. */
  if (isdigit(peek)) {
    int value = 0;
    do {
      value = 10 * value + (peek - '0');
      input->get(peek);
    } while(isdigit(peek));
    input->putback(peek);

    Number n(value);
    //cout << "(" << n.getValue() << ", " << n.getTag() << ")" << endl;

    return Number(value);
  }

  /* Handler relational operators. */
  if (peek == '<' || peek == '>' || peek == '=') {
    if (peek == '<' && input->peek() == '=') {
      input->get(peek);


      //cout << "(" << "<=, " << LE << ")" << endl;

      return Token(LE);
    }
    if (peek == '<' && input->peek() == '>') {
      input->get(peek);

      //cout << "(" << "<>, " << NE << ")" << endl;

      return Token(NE);
    }
    if (peek == '>' && input->peek() == '=') {
      input->get(peek);

      //cout << "(" << ">=, " << GE << ")" << endl;

      return Token(GE);
    }
    if (peek == '=' && input->peek() == '=') {
      input->get(peek);

      //cout << "(" << "==, " << EQ << ")" << endl;

      return Token(EQ);
    }
  }

  /* Handler logical operators. */
  if (peek == '&' || peek == '|') {
    if (peek == '&' && input->peek() == '&') {

      //cout << "(" << "&&, " << AND << ")" << endl;

      return Token(AND);
    }
    if (peek == '|' && input->peek() == '|') {

      //cout << "(" << "||, " << OR << ")" << endl;

      return Token(OR);
    }
  }

  Token t(peek);
  //cout << "(" << peek << ", " << t.getTag() << ")" << endl;
  return Token(peek);
}

void Lexer::reserve(Word word) {
  keywords.insert(pair<string, int>(word.getLexeme(), word.getTag()));
}
