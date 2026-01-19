#pragma once
#include <string>
#include <vector>

struct ASTVisitor;

struct Node {
    virtual void accept(ASTVisitor* v) = 0;
    virtual ~Node() = default;
};

struct Expr : Node {};
struct Stmt : Node {};

struct Program : Node {
    std::vector<Stmt*> statements;
    void accept(ASTVisitor* v) override;
};

// -------- Expressions --------

struct IntLiteral : Expr {
    int value;
    IntLiteral(int v) : value(v) {}
    void accept(ASTVisitor* v) override;
};

struct BoolLiteral : Expr {
    bool value;
    BoolLiteral(bool v) : value(v) {}
    void accept(ASTVisitor* v) override;
};

struct VarExpr : Expr {
    std::string name;
    VarExpr(std::string n) : name(std::move(n)) {}
    void accept(ASTVisitor* v) override;
};

struct UnaryExpr : Expr {
    enum class UnaryOp { Neg, Not };
    UnaryOp op;
    Expr* expr;
    UnaryExpr(UnaryOp o, Expr* e) : op(o), expr(e) {}
    void accept(ASTVisitor* v) override;
};

struct BinaryExpr : Expr {
    enum class BinaryOp {
        Add, Sub, Mul, Div, Mod,
        Eq, Neq, Lt, Le, Gt, Ge,
        And, Or
    };

    BinaryOp op;
    Expr* lhs;
    Expr* rhs;

    BinaryExpr(BinaryOp o, Expr* l, Expr* r) : op(o), lhs(l), rhs(r) {}
    void accept(ASTVisitor* v) override;
};

struct CallExpr : Expr {
    std::string functionName;
    std::vector<Expr*> args;
    void accept(ASTVisitor* v) override;
};

struct AssignExpr : Expr {
    Expr* target;
    Expr* expr;
    AssignExpr(Expr* t, Expr* e) : target(t), expr(e) {}
    void accept(ASTVisitor* v) override;
};

// -------- Statements --------

struct ExprStmt : Stmt {
    Expr* expr;
    ExprStmt(Expr* e) : expr(e) {}
    void accept(ASTVisitor* v) override;
};

struct VarDecl : Stmt {
    std::string name;
    Expr* initExpr;
    VarDecl(std::string n, Expr* e) : name(std::move(n)), initExpr(e) {}
    void accept(ASTVisitor* v) override;
};

struct BlockStmt : Stmt {
    std::vector<Stmt*> statements;
    void accept(ASTVisitor* v) override;
};

struct IfStmt : Stmt {
    Expr* condition;
    Stmt* thenBranch;
    Stmt* elseBranch = nullptr;
    void accept(ASTVisitor* v) override;
};

struct WhileStmt : Stmt {
    Expr* condition;
    Stmt* body;
    void accept(ASTVisitor* v) override;
};

struct ReturnStmt : Stmt {
    Expr* expr = nullptr;
    void accept(ASTVisitor* v) override;
};

struct FunctionParam {
    std::string name;
};

struct FunctionDecl : Stmt {
    std::string name;
    std::vector<FunctionParam*> params;
    BlockStmt* body;
    void accept(ASTVisitor* v) override;
};

struct ClassDecl : Stmt {
    std::string name;
    void accept(ASTVisitor* v) override;
};