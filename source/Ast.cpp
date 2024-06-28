#include "Ast.h"

VariableAst::VariableAst(const std::string &var) : variable(var) {}
const std::string& VariableAst::getVariable() {
    return variable;
}

NatAst::NatAst(const std::string &nat) : nat(stoi(nat)) {}
long NatAst::getNat() {
    return nat;
}

BoolAst::BoolAst(const std::string &val) :
    val(val == "true" ? true : false) {}
bool BoolAst::getVal() {
    return val;
}
