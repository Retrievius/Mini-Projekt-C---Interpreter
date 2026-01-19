#pragma once
#include <stdexcept>
#include <string>
#include <vector>

#include "ast/AST.h"
#include "SymbolTable.h"
#include "Type.h"

class SemanticChecker : public ASTVisitor {
public:
    SymbolTable symbols;

    // Ergebnis der letzten Expression
    Type lastType = Type::Void();
    bool lastIsLValue = false;

    // Function-Kontext + Return-Path
    bool inFunction = false;
    Type currentReturnType = Type::Void();
    bool currentAlwaysReturns = false;

    // --- Expressions ---
    void visit(IntLiteral*) override;
    void visit(BoolLiteral*) override;
    void visit(VarExpr*) override;
    void visit(UnaryExpr*) override;
    void visit(BinaryExpr*) override;
    void visit(CallExpr*) override;
    void visit(AssignExpr*) override;

    // --- Statements ---
    void visit(ExprStmt*) override;
    void visit(VarDecl*) override;
    void visit(BlockStmt*) override;
    void visit(IfStmt*) override;
    void visit(WhileStmt*) override;
    void visit(ReturnStmt*) override;

    // --- Top Level ---
    void visit(FunctionDecl*) override;
    void visit(ClassDecl*) override;

private:
    [[noreturn]] void error(const std::string& msg) {
        throw std::runtime_error("Semantic error: " + msg);
    }

    void require(bool cond, const std::string& msg) {
        if (!cond) error(msg);
    }

    Type evalExpr(Expr* e) {
        e->accept(this);
        return lastType;
    }

    Type evalExprRequireLValue(Expr* e) {
        e->accept(this);
        require(lastIsLValue, "Expected LValue");
        return lastType;
    }
};
