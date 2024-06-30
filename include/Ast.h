#pragma once
#include <string>
#include <memory>
#include "AstVisitor.h"

class AstVisitor;

class AstNode {
public:
    virtual ~AstNode() = default;
    virtual void accept(AstVisitor* visitor) = 0; 
};

class VariableAst : public AstNode {
    const std::string variable;
public:
    VariableAst(const std::string &var);
    const std::string getVariable();
    void accept(AstVisitor* visitor);
};

class NatAst : public AstNode {
    long nat;
public:
    NatAst(const std::string &nat);
    long getNat();
    void accept(AstVisitor* visitor);
};

class BoolAst : public AstNode {
    bool val;
public:
    BoolAst(const std::string &val);
    bool getVal();
    void accept(AstVisitor* visitor);
};

class BetaAst : public AstNode {
    std::shared_ptr<AstNode> production;
public:
    BetaAst(std::unique_ptr<AstNode> production);
    std::shared_ptr<AstNode> getProduction();
    void accept(AstVisitor* visitor);
};

class TermPrimeAst : public AstNode {
    std::shared_ptr<AstNode> production;
public:
    TermPrimeAst(std::unique_ptr<AstNode> production);
    std::shared_ptr<AstNode> getProduction();
    void accept(AstVisitor* visitor);
};

class TermAst : public AstNode {
    std::shared_ptr<BetaAst> beta;
    std::shared_ptr<TermPrimeAst> tprime;
public:
    TermAst(std::unique_ptr<BetaAst> beta, std::unique_ptr<TermPrimeAst> tprime);
    std::shared_ptr<AstNode> getBeta();
    std::shared_ptr<AstNode> getTermPrime();
    void accept(AstVisitor* visitor);
};

class ConditionalAst : public AstNode {
    std::shared_ptr<TermAst> predicate;
    std::shared_ptr<TermAst> true_path;
    std::shared_ptr<TermAst> false_path;
public:
    ConditionalAst(std::unique_ptr<TermAst> predicate,
                   std::unique_ptr<TermAst> true_path,
                   std::unique_ptr<TermAst> false_path);
    std::shared_ptr<TermAst> getPredicate();
    std::shared_ptr<TermAst> getTrue();
    std::shared_ptr<TermAst> getFalse();
    void accept(AstVisitor* visitor);
};

class ConcatAst : public AstNode {
    std::shared_ptr<TermAst> term;
    std::shared_ptr<TermPrimeAst> termPrime;
public:
    ConcatAst(std::unique_ptr<TermAst> t, std::unique_ptr<TermPrimeAst> tp);
    void accept(AstVisitor* visitor);
    std::shared_ptr<TermAst> getTerm();
    std::shared_ptr<TermPrimeAst> getTermPrime();
};

class SemiOpAst : public AstNode {
    const std::string operation;
    std::shared_ptr<TermAst> term;
    std::shared_ptr<TermPrimeAst> termPrime;
public:
    SemiOpAst(const std::string &op, std::unique_ptr<TermAst> t, std::unique_ptr<TermPrimeAst> tp);
    void accept(AstVisitor* visitor);
    const std::string getOperation();
    std::shared_ptr<TermAst> getTerm();
    std::shared_ptr<TermPrimeAst> getTermPrime();
};

class EpsilonAst : public AstNode {
public:
    EpsilonAst();
    void accept(AstVisitor* visitor);
};

class LambdaAst : public AstNode {
    std::shared_ptr<VariableAst> variable;
    std::shared_ptr<TermAst> body;
public:
    LambdaAst(std::unique_ptr<VariableAst> var, std::unique_ptr<TermAst> body);
    void accept(AstVisitor *visitor);
    std::shared_ptr<VariableAst> getVariable();
    std::shared_ptr<TermAst> getBody();
};