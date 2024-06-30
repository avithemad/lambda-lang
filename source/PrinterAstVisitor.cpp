#include "PrinterAstVisitor.h"
#include<iostream>

PrinterAstVisitor::PrinterAstVisitor() {

}

void  PrinterAstVisitor::VisitVariableAst(VariableAst* v) {
    std::cout << v->getVariable() << " ";
}

void PrinterAstVisitor::VisitBoolAst(BoolAst* v) {
    std::cout << v->getVal() << " ";
}

void PrinterAstVisitor::VisitNatAst(NatAst* v) {
    std::cout << v->getNat() << " ";
}

void PrinterAstVisitor::VisitBetaAst(BetaAst* v) {
    v->getProduction()->accept(this);
}

void PrinterAstVisitor::VisitTermPrimeAst(TermPrimeAst *v) {
    v->getProduction()->accept(this);
}

void PrinterAstVisitor::VisitTermAst(TermAst* v) {
    v->getBeta()->accept(this);
    v->getTermPrime()->accept(this);
}

void PrinterAstVisitor::VisitConditionalAst(ConditionalAst* v) {
    std::cout << "if ";
    v->getPredicate()->accept(this);
    std::cout << "then ";
    v->getTrue()->accept(this);
    std::cout << "else ";
    v->getFalse()->accept(this);
}
void PrinterAstVisitor::VisitConcatAst(ConcatAst* v) {
    v->getTerm()->accept(this);
    v->getTermPrime()->accept(this);
}
void PrinterAstVisitor::VisitSemiOpAst(SemiOpAst* v) {
    std::cout << v->getOperation() << " "; 
    v->getTerm()->accept(this);
    v->getTermPrime()->accept(this);
}
void PrinterAstVisitor::VisitEpsilonAst(EpsilonAst* v) {

}
void PrinterAstVisitor::VisitLambdaAst(LambdaAst* v) {
    std::cout << "\\ ";
    v->getVariable()->accept(this);
    std::cout << "= ";
    v->getBody()->accept(this);
}