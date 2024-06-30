#pragma once
#include <string>

enum token {
    bool_token,
    nat_token,
    lambda_token,
    variable_token,
    if_token,
    then_token,
    else_token,
    op_token,
    equal_token,
    eof_token,
    invalid_token   
};

struct tokenUnit {
    token tok;
    std::string lexeme;
};

class Lexer {
    const std::string &source;
    int idx;
    tokenUnit currentToken;
public:
    Lexer (const std::string &src);
    tokenUnit peekToken();
    void eatToken();
};

