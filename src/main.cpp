#include "lexer.hpp"
#include "parser.hpp"
#include <iostream>
#include <memory>

int main() {
  std::string entrada = "print (((10 * 2)+(10 * 2)) + 1)";
  Lexer lexer = Lexer(entrada);
  std::unique_ptr<Expressao> expressao = analisar_programa(lexer);
  std::cout << expressao->valor() << std::endl;
}