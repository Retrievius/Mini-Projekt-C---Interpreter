#pragma once

struct IntLiteral;
struct BinaryExpr;
struct VarDecl;
struct AssignExpr;
struct BlockStmt;
struct IfStmt;
struct WhileStmt;
struct ReturnStmt;

struct ASTVisitor {
    virtual void visit(IntLiteral*) {}
    virtual void visit(BinaryExpr*) {}
    virtual void visit(VarDecl*) {}
    virtual void visit(AssignExpr*) {}
    virtual void visit(BlockStmt*) {}
    virtual void visit(IfStmt*) {}
    virtual void visit(WhileStmt*) {}
    virtual void visit(ReturnStmt*) {}
    virtual ~ASTVisitor() = default;
};
