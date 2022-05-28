#include "lexer.hpp"
#include <iostream>

int main() {
  Lexer lexer = Lexer("print (300 * 20) + 2");

  for (Token prox = lexer.proximo_token();
       prox.tipo() != TipoToken::FIM_ARQUIVO; prox = lexer.proximo_token())
    prox.print();
}