#pragma once
#include "Ast.h"
class VariableAst;
class NatAst;
class BoolAst;
class BetaAst;
class TermPrimeAst;
class TermAst;
class ConditionalAst;
class ConcatAst;
class SemiOpAst;
class EpsilonAst;
class LambdaAst;
class AstVisitor {
public:
    ~AstVisitor() = default;
    virtual void VisitVariableAst(VariableAst* v) = 0;
    virtual void VisitNatAst(NatAst* v) = 0;
    virtual void VisitBoolAst(BoolAst* v) = 0;
    virtual void VisitBetaAst(BetaAst* v) = 0;
    virtual void VisitTermPrimeAst(TermPrimeAst* v) = 0;
    virtual void VisitTermAst(TermAst* v) = 0;
    virtual void VisitConditionalAst(ConditionalAst* v) = 0;
    virtual void VisitConcatAst(ConcatAst* v) = 0;
    virtual void VisitSemiOpAst(SemiOpAst* v) = 0;
    virtual void VisitEpsilonAst(EpsilonAst* v) = 0;
    virtual void VisitLambdaAst(LambdaAst* v) = 0;
};