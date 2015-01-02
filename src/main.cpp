#include <iostream>
#include <fstream>
#include "Lexer.h"

using namespace std;

void outputTokens(istream* is) {
  do {
    Lexer lexer(is);
    Token token = lexer.scan();
    //cout << token.getTag() << endl;
  } while(!is->eof());
}

int main(int argc,char **argv) {
  istream* is = NULL;
  if (argc == 1) {
    outputTokens(&cin);
  } else {
    fstream fs(argv[1], std::ios::in);
    outputTokens(&fs);
  }
  return 0;
}
