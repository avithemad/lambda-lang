#include<iostream>
#include "Lexer.h"

int main() {
    std::string src = "\\ x = y+x";
    Lexer lexer(src);

    while(lexer.peekToken().tok != eof_token && lexer.peekToken().tok!= invalid_token)
    {
        std::cout << lexer.peekToken().tok << " "
            << lexer.peekToken().lexeme << std::endl;
        lexer.eatToken();
    }
}