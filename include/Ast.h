#pragma once
#include <string>
#include <memory>

class AstNode {
public:
    virtual ~AstNode() = default;
};

class VariableAst : public AstNode {
    const std::string &variable;
public:
    VariableAst(const std::string &var);
    const std::string& getVariable();
};

class NatAst : public AstNode {
    long nat;
public:
    NatAst(const std::string &nat);
    long getNat();
};

class BoolAst : public AstNode {
    bool val;
public:
    BoolAst(const std::string &val);
    bool getVal();
};


