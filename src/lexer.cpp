#include "lexer.hpp"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>

Token::Token(TipoToken tipo, std::string texto) : tipo_(tipo), texto_(texto) {}
Token::Token(TipoToken tipo, char texto)
    : tipo_(tipo), texto_(std::string(1, texto)) {}

TipoToken Token::tipo() const { return tipo_; }
std::string Token::texto() const { return texto_; }

void Token::print() const {
  std::cout << "{Tipo: " << tipo_ << ", Símbolo: " << texto_ << "}"
            << std::endl;
}

std::ostream &operator<<(std::ostream &os, TipoToken token) {
  switch (token) {
  case TipoToken::PRINT:
    return os << "Print";
  case TipoToken::FIM:
    return os << "Fim do Arquivo";
  case TipoToken::ABRE_PARENTESE:
    return os << "Abre Parentese";
  case TipoToken::FECHA_PARENTESE:
    return os << "Fecha Parentese";
  case TipoToken::SOMA:
    return os << "Soma";
  case TipoToken::ASTERISCO:
    return os << "Asterisco";
  case TipoToken::INTEIRO:
    return os << "Inteiro";
  };

  return os << "Token Desconhecido";
}

Lexer::Lexer(std::string entrada) : entrada_(entrada), cursor_(0) {}

Token Lexer::proximo_token() {
  while (isspace(entrada_[cursor_])) {
    cursor_++;
  }

  if (cursor_ >= entrada_.length()) { // Usar arquivo ao invés de string ?
    return Token(TipoToken::FIM, EOF);
  }

  char prox = entrada_[cursor_];
  cursor_++;

  switch (prox) {
  case '(':
    return Token(TipoToken::ABRE_PARENTESE, prox);
  case ')':
    return Token(TipoToken::FECHA_PARENTESE, prox);
  case '+':
    return Token(TipoToken::SOMA, prox);
  case '*':
    return Token(TipoToken::ASTERISCO, prox);
  }

  cursor_--; // cursor_ está na primeira posição do número ou 'print'

  if (isdigit(prox)) {
    return tokenizar_numero();
  }

  return tokenizar_texto();
}

Token Lexer::tokenizar_numero() {
  int inicio = cursor_;
  char prox = entrada_[cursor_];
  while (isdigit(prox)) {
    cursor_++;
    prox = entrada_[cursor_];
  }
  int fim = cursor_ - 1;
  std::string texto = entrada_.substr(inicio, fim - inicio + 1);

  return Token(TipoToken::INTEIRO, texto);
}

Token Lexer::tokenizar_texto() {
  int inicio = cursor_;
  char prox = entrada_[cursor_];
  while (!isspace(prox)) {
    cursor_++;
    prox = entrada_[cursor_];
  }
  int fim = cursor_ - 1;
  std::string texto = entrada_.substr(inicio, fim - inicio + 1);

  if (texto != "print") {
    std::cout << "Palavra chave não reconhecida: " << texto << std::endl;
    exit(1);
  }

  return Token(TipoToken::PRINT, texto);
}