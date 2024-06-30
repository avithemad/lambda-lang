#include "Parser.h"
#include <iostream>
#include "PrinterAstVisitor.h"

int main() {
    std::string source = "\\y = \\x = if \\x = 2+3-false then x else y+x-2";
    Parser parser(source);
    auto t = parser.parseTerm();
    if (t) {
        std::cout << "Parse success\n";
        PrinterAstVisitor p;
        p.VisitTermAst(t.get());
        std::cout << std::endl;
    } else {
        std::cout << "Syntax error\n";
    }



    return 0;
}