#pragma once

#include "lexer.hpp"
#include <memory>

class Expressao {
public:
  virtual int valor() const = 0;
  virtual ~Expressao() = default;
};

class Inteiro : public Expressao {
public:
  Inteiro(int valor);
  int valor() const override;

private:
  int valor_;
};

class Soma : public Expressao {
public:
  Soma(std::unique_ptr<Expressao> primeiro_operando,
       std::unique_ptr<Expressao> segundo_operando);
  int valor() const override;

private:
  std::unique_ptr<Expressao> op1_;
  std::unique_ptr<Expressao> op2_;
};

class Multiplicacao : public Expressao {
public:
  Multiplicacao(std::unique_ptr<Expressao> primeiro_operando,
                std::unique_ptr<Expressao> segundo_operando);
  int valor() const override;

private:
  std::unique_ptr<Expressao> op1_;
  std::unique_ptr<Expressao> op2_;
};

std::unique_ptr<Expressao> analisar_expressao(Lexer &lexer);
std::unique_ptr<Expressao> analisar_programa(Lexer &lexer);