#include "Ast.h"
#include "AstVisitor.h"
#include<iostream>

VariableAst::VariableAst(const std::string &var) : variable(var) {}
const std::string VariableAst::getVariable()
{
    return variable;
}
void VariableAst::accept(AstVisitor *v)
{
    v->VisitVariableAst(this);
}

NatAst::NatAst(const std::string &nat) : nat(stoi(nat)) {}
long NatAst::getNat()
{
    return nat;
}
void NatAst::accept(AstVisitor *v)
{
    v->VisitNatAst(this);
}

BoolAst::BoolAst(const std::string &val) : val(val == "true" ? true : false) {}
bool BoolAst::getVal()
{
    return val;
}
void BoolAst::accept(AstVisitor *v)
{
    v->VisitBoolAst(this);
}

BetaAst::BetaAst(std::unique_ptr<AstNode> production) : production(std::move(production)) {}
std::shared_ptr<AstNode> BetaAst::getProduction()
{
    return production;
}
void BetaAst::accept(AstVisitor *v)
{
    v->VisitBetaAst(this);
}

TermPrimeAst::TermPrimeAst(std::unique_ptr<AstNode> production) : production(std::move(production)) {}
std::shared_ptr<AstNode> TermPrimeAst::getProduction()
{
    return production;
}
void TermPrimeAst::accept(AstVisitor *v)
{
    v->VisitTermPrimeAst(this);
}

TermAst::TermAst(std::unique_ptr<BetaAst> beta, std::unique_ptr<TermPrimeAst> tprime) : beta(std::move(beta)), tprime(std::move(tprime)) {}
std::shared_ptr<AstNode> TermAst::getBeta()
{
    return beta;
}
std::shared_ptr<AstNode> TermAst::getTermPrime()
{
    return tprime;
}
void TermAst::accept(AstVisitor *v)
{
    v->VisitTermAst(this);
}

ConditionalAst::ConditionalAst(std::unique_ptr<TermAst> predicate,
                               std::unique_ptr<TermAst> true_path, std::unique_ptr<TermAst> false_path) : predicate(std::move(predicate)), true_path(std::move(true_path)), false_path(std::move(false_path))
{
}
std::shared_ptr<TermAst> ConditionalAst::getPredicate() {
    return predicate;
}
std::shared_ptr<TermAst> ConditionalAst::getTrue() {
    return true_path;
}
std::shared_ptr<TermAst> ConditionalAst::getFalse() {
    return false_path;
}
void ConditionalAst::accept(AstVisitor *v)
{
    v->VisitConditionalAst(this);
}

ConcatAst::ConcatAst(std::unique_ptr<TermAst> t, std::unique_ptr<TermPrimeAst> tp) : term(std::move(t)), termPrime(std::move(tp)) {}
std::shared_ptr<TermAst> ConcatAst::getTerm() {
    return term;
}
std::shared_ptr<TermPrimeAst> ConcatAst::getTermPrime() {
    return termPrime;
} 
void ConcatAst::accept(AstVisitor *v)
{
    v->VisitConcatAst(this);
}

SemiOpAst::SemiOpAst(const std::string &op, std::unique_ptr<TermAst> t, std::unique_ptr<TermPrimeAst> tp)
    : operation(op), term(std::move(t)), termPrime(std::move(tp))
{
}
const std::string SemiOpAst::getOperation() {
    return operation;
}
std::shared_ptr<TermAst> SemiOpAst::getTerm() {
    return term;
}
std::shared_ptr<TermPrimeAst> SemiOpAst::getTermPrime() {
    return termPrime;
}
void SemiOpAst::accept(AstVisitor* v) {
    v->VisitSemiOpAst(this);
}

LambdaAst::LambdaAst(std::unique_ptr<VariableAst> var, std::unique_ptr<TermAst> t) :
    variable(std::move(var)), body(std::move(t)) {}
void LambdaAst::accept(AstVisitor *v) {
    v->VisitLambdaAst(this);
}
std::shared_ptr<VariableAst> LambdaAst::getVariable() {
    return variable;
}
std::shared_ptr<TermAst> LambdaAst::getBody() {
    return body;
}

EpsilonAst::EpsilonAst() {

}
void EpsilonAst::accept(AstVisitor* v) {

}