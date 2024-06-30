#include "Lexer.h"

Lexer::Lexer(const std::string &src) : source(src), idx(0)
{
    eatToken();
}

tokenUnit Lexer::peekToken()
{
    return currentToken;
}

void Lexer::eatToken()
{
    token tokenValue;
    std::string lexeme;
    if (idx == source.size())
    {
        tokenValue = eof_token;
        currentToken = {tokenValue, lexeme};
        return;
    }
    while (isspace(source[idx]))
    {
        if (idx == source.size())
        {
            tokenValue = eof_token;
            currentToken = {tokenValue, lexeme};
            return;
        }
        idx++;
    };

    if (source[idx] == '\\')
    {
        tokenValue = lambda_token;
        lexeme += source[idx++];
    }
    else if (source[idx] == '=')
    {
        tokenValue = equal_token;
        lexeme += source[idx++];
    }
    else if (source[idx] == '+' ||
        source[idx] == '-' ||
        source[idx] == '/' ||
        source[idx] == '*' ||
        source[idx] == '&' ||
        source[idx] == '|')
    {
        tokenValue = op_token;
        lexeme += source[idx++];
    }
    else if (isalpha(source[idx]))
    {
        lexeme += source[idx];
        while (isalnum(source[++idx]) && idx < source.size())
            lexeme += source[idx];

        if (lexeme == "if")
            tokenValue = if_token;
        else if (lexeme == "then")
            tokenValue = then_token;
        else if (lexeme == "else")
            tokenValue = else_token;
        else if (lexeme == "true" || lexeme == "false")
            tokenValue = bool_token;
        else
            tokenValue = variable_token;
    }
    else if (isdigit(source[idx]))
    {
        lexeme += source[idx];
        while (isalnum(source[++idx]) && idx < source.size())
        {
            if (!isdigit(source[idx]))
            {
                currentToken.tok = invalid_token;
                return;
            }
            lexeme += source[idx++];
        }
        tokenValue = nat_token;
    } else {
        currentToken.tok = invalid_token;
        return;
    }
    currentToken.lexeme = lexeme;
    currentToken.tok = tokenValue;
    return;
}