#pragma once
#include <vector>

// Forward declarations für Visitor
struct IntLiteral;
struct BinaryExpr;
struct VarDecl;
struct AssignExpr;
struct BlockStmt;
struct IfStmt;
struct WhileStmt;
struct ReturnStmt;

struct Stmt {
    virtual ~Stmt() = default;
    virtual void accept(class ASTVisitor* visitor) = 0;
};

struct Expr : Stmt {
};

struct IntLiteral : Expr {
    int value;
    IntLiteral(int v) : value(v) {}
    void accept(ASTVisitor* visitor) override { visitor->visit(this); }
};

struct BinaryExpr : Expr {
    enum class BinaryOp { Add, Sub, Mul, Div } op;
    Expr* lhs;
    Expr* rhs;
    BinaryExpr(BinaryOp o, Expr* l, Expr* r) : op(o), lhs(l), rhs(r) {}
    void accept(ASTVisitor* visitor) override { visitor->visit(this); }
};

struct ExprStmt : Stmt {
    Expr* expr;
    ExprStmt(Expr* e) : expr(e) {}
    void accept(ASTVisitor* visitor) override { visitor->visit(this); }
};


struct Program {
    std::vector<Stmt*> statements;
};

