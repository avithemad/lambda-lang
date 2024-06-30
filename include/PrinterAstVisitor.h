#pragma once
#include "AstVisitor.h"

class PrinterAstVisitor : public AstVisitor {
public:
    PrinterAstVisitor();
    void VisitVariableAst(VariableAst* v);
    void VisitNatAst(NatAst* v);
    void VisitBoolAst(BoolAst* v);
    void VisitBetaAst(BetaAst* v);
    void VisitTermPrimeAst(TermPrimeAst* v);
    void VisitTermAst(TermAst* v);
    void VisitConditionalAst(ConditionalAst* v);
    void VisitConcatAst(ConcatAst* v);
    void VisitSemiOpAst(SemiOpAst* v);
    void VisitEpsilonAst(EpsilonAst* v);
    void VisitLambdaAst(LambdaAst* v);
};