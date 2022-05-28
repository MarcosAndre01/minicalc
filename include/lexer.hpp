#pragma once

#include <iostream>

enum class TipoToken {
  PRINT,
  FIM_ARQUIVO,
  ABRE_PARENTESE,
  FECHA_PARENTESE,
  SOMA,
  ASTERISCO,
  INTEIRO
};

std::ostream &operator<<(std::ostream &os, TipoToken token);

class Token {
public:
  Token(TipoToken tipo, std::string texto);
  Token(TipoToken tipo, char texto);
  TipoToken tipo() const;
  void print() const;

private:
  TipoToken tipo_;
  std::string texto_;
};

class Lexer {
public:
  Lexer(std::string entrada);
  Token proximo_token();

private:
  std::string entrada_;
  int cursor_;
  Token tokenizar_numero();
  Token tokenizar_texto();
};