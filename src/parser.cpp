#include "parser.hpp"
#include "lexer.hpp"
#include <iostream>
#include <memory>

Inteiro::Inteiro(int valor) : valor_(valor) {}
int Inteiro::valor() const { return valor_; }

Soma::Soma(std::unique_ptr<Expressao> primeiro_operando,
           std::unique_ptr<Expressao> segundo_operando)
    : op1_(std::move(primeiro_operando)), op2_(std::move(segundo_operando)) {}
int Soma::valor() const { return op1_->valor() + op2_->valor(); }

Multiplicacao::Multiplicacao(std::unique_ptr<Expressao> primeiro_operando,
                             std::unique_ptr<Expressao> segundo_operando)
    : op1_(std::move(primeiro_operando)), op2_(std::move(segundo_operando)) {}
int Multiplicacao::valor() const { return op1_->valor() * op2_->valor(); }

std::unique_ptr<Expressao> analisar_expressao(Lexer &lexer) {
  Token token = lexer.proximo_token();
  if (token.tipo() == TipoToken::INTEIRO) {
    auto inteiro = std::make_unique<Inteiro>(stoi(token.texto()));
    return inteiro;
  }

  if (token.tipo() != TipoToken::ABRE_PARENTESE) {
    std::cout << "( Esperado" << std::endl;
    exit(2);
  }
  std::unique_ptr<Expressao> primeiro_operando = analisar_expressao(lexer);
  token = lexer.proximo_token();
  TipoToken operador = token.tipo();

  std::unique_ptr<Expressao> segundo_operando = analisar_expressao(lexer);
  token = lexer.proximo_token();

  if (token.tipo() != TipoToken::FECHA_PARENTESE) {
    std::cout << ") Esperado" << std::endl;
    exit(2);
  }

  switch (operador) {
  case TipoToken::SOMA:
    return std::make_unique<Soma>(std::move(primeiro_operando),
                                  std::move(segundo_operando));
  case TipoToken::ASTERISCO:
    return std::make_unique<Multiplicacao>(std::move(primeiro_operando),
                                           std::move(segundo_operando));
  default:
    std::cout << "Operador desconhecido: " << operador << std::endl;
    exit(2);
  }
}
std::unique_ptr<Expressao> analisar_programa(Lexer &lexer) {
  Token token = lexer.proximo_token();
  if (token.tipo() != TipoToken::PRINT) {
    std::cout << "Instrução print esperada" << std::endl;
    exit(2);
  }

  return analisar_expressao(lexer);
}