#pragma once
#include<memory>
#include "Ast.h"
#include "Lexer.h"

class Parser {
private:
   std::unique_ptr<Lexer> lexer;
public:
    Parser(const std::string &source);
    std::unique_ptr<TermAst> parseTerm();
    std::unique_ptr<BetaAst> parseBeta();
    std::unique_ptr<VariableAst> parseVariable();
    std::unique_ptr<BoolAst> parseBool();
    std::unique_ptr<NatAst> parseNat();
    std::unique_ptr<ConditionalAst> parseConditional();
    std::unique_ptr<LambdaAst> parseLambda();
    std::unique_ptr<TermPrimeAst> parseTermPrime();
};