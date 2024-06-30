#include "Parser.h"

Parser::Parser(const std::string &source) : lexer(std::make_unique<Lexer>(source)) {
}

std::unique_ptr<VariableAst> Parser::parseVariable() {
    tokenUnit next = lexer->peekToken();
    if (next.tok == variable_token){
        lexer->eatToken();
        return std::make_unique<VariableAst>(next.lexeme);
    } 
    else return nullptr;
}
std::unique_ptr<BoolAst> Parser::parseBool() {
    tokenUnit next = lexer->peekToken();
    if (next.tok == bool_token) {
        lexer->eatToken();
        return std::make_unique<BoolAst>(next.lexeme);
    }
    else return nullptr;
}
std::unique_ptr<NatAst> Parser::parseNat() {
    tokenUnit next = lexer->peekToken();
    if (next.tok == nat_token) {
        lexer->eatToken();
        return std::make_unique<NatAst>(next.lexeme);
    }
    else return nullptr;
}
std::unique_ptr<TermAst> Parser::parseTerm() {
    auto beta = parseBeta();
    if (beta == nullptr) return nullptr;
    auto tp = parseTermPrime();
    if (tp == nullptr) return nullptr;
    return std::make_unique<TermAst>(std::move(beta), std::move(tp));
}
std::unique_ptr<TermPrimeAst> Parser::parseTermPrime() {
    tokenUnit next = lexer->peekToken();
    if (next.tok == op_token) {
        lexer->eatToken();
        auto term = parseTerm();
        if (term == nullptr) return nullptr;

        auto termPrime = parseTermPrime();
        if (term == nullptr) return nullptr;

        auto semiOp = std::make_unique<SemiOpAst>(next.lexeme, std::move(term), std::move(termPrime));
        return std::make_unique<TermPrimeAst>(std::move(semiOp));
    } else if (next.tok == eof_token) {
        return std::make_unique<TermPrimeAst>(std::move(std::make_unique<EpsilonAst>())); // this should be epsilong prod
    } else if (next.tok == invalid_token) {
        return nullptr;
    }else {
        auto term = parseTerm();
        if (term == nullptr) return std::make_unique<TermPrimeAst>(std::move(std::make_unique<EpsilonAst>())); // this should be epsilon prod

        auto termPrime = parseTermPrime();
        if (term == nullptr) return nullptr;

        auto concatOp = std::make_unique<ConcatAst>(std::move(term), std::move(termPrime));
        return std::make_unique<TermPrimeAst>(std::move(concatOp));
    }
}
std::unique_ptr<LambdaAst> Parser::parseLambda() {
    tokenUnit next = lexer->peekToken();
    if (next.tok == lambda_token) {
        lexer->eatToken();
        auto var = parseVariable();
        if (var == nullptr) return nullptr;
        if (lexer->peekToken().tok != equal_token) return nullptr;
        lexer->eatToken();
        auto body = parseTerm();
        if (body == nullptr) return nullptr;
        return std::make_unique<LambdaAst>(std::move(var), std::move(body));
    }
    return nullptr;
}
std::unique_ptr<ConditionalAst> Parser::parseConditional() {
    tokenUnit next = lexer->peekToken();
    if (next.tok == if_token) {
        lexer->eatToken();
        auto predicate = parseTerm();
        if (predicate == nullptr) return nullptr;

        if (lexer->peekToken().tok != then_token) return nullptr;
        lexer->eatToken();
        auto tp = parseTerm();
        if (tp == nullptr) return nullptr;

        if (lexer->peekToken().tok != else_token) return nullptr;
        lexer->eatToken();
        auto fp = parseTerm();
        if (fp == nullptr) return nullptr;

        return std::make_unique<ConditionalAst>(std::move(predicate), std::move(tp), std::move(fp));
    }
    return nullptr;
}
std::unique_ptr<BetaAst> Parser::parseBeta() {
    std::unique_ptr<AstNode> prod;
    switch (lexer->peekToken().tok)
    {
    case variable_token:
        prod = parseVariable();
        break;
    case bool_token:
        prod = parseBool();
        break;
    case nat_token:
        prod = parseNat();
        break;
    case lambda_token:
        prod = parseLambda();
        break;
    case if_token:
        prod = parseConditional();
        break;
    default:
        return nullptr;
    }
    if (prod == nullptr) return nullptr;
    return std::make_unique<BetaAst>(std::move(prod));
}