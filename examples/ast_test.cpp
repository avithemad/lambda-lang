#include<iostream>

#include "Ast.h"

int main() {
    BoolAst b("true");
    std::cout << b.getVal();

    return 0;
}