#include<iostream>

#include "Ast.h"
#include "PrinterAstVisitor.h"

int main() {
    std::unique_ptr<BoolAst>  b = std::make_unique<BoolAst>("true");
    PrinterAstVisitor p;
    p.VisitBoolAst(b.get());
    BetaAst beta(std::move(b));
    std::shared_ptr<AstNode> n = beta.getProduction();

    return 0;
}