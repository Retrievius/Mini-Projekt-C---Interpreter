#pragma once
#include <string>
#include <vector>

// Forward declaration Visitor
struct ASTVisitor;

// ----------------- Base Classes -----------------
struct Stmt {
    virtual ~Stmt() = default;
    virtual void accept(ASTVisitor* visitor) = 0;
};

struct Expr : Stmt {
};

// ----------------- Expressions -----------------
struct IntLiteral : Expr {
    int value;
    IntLiteral(int v) : value(v) {}
    void accept(ASTVisitor* visitor) override;
};

struct BinaryExpr : Expr {
    enum class BinaryOp {
        Add, Sub, Mul, Div, Mod,
        Eq, Neq,
        Lt, Le, Gt, Ge,
        And, Or
    };
    BinaryOp op;
    Expr* lhs;
    Expr* rhs;

    BinaryExpr(BinaryOp o, Expr* l, Expr* r) : op(o), lhs(l), rhs(r) {}
    void accept(ASTVisitor* visitor) override;
};

struct UnaryExpr : Expr {
    enum class UnaryOp { Neg, Not };
    UnaryOp op;
    Expr* expr;

    UnaryExpr(UnaryOp o, Expr* e) : op(o), expr(e) {}
    void accept(ASTVisitor* visitor) override;
};

struct CallExpr : Expr {
    std::string functionName;
    std::vector<Expr*> args;

    CallExpr(const std::string& name) : functionName(name) {}

    void accept(ASTVisitor* visitor) override;
};

struct AssignExpr : Expr {
    Expr* target;  // VarExpr oder FieldExpr
    Expr* expr;

    AssignExpr(Expr* t, Expr* e) : target(t), expr(e) {}
    void accept(ASTVisitor* visitor) override;
};


struct BoolLiteral : Expr {
    bool value;
    BoolLiteral(bool v) : value(v) {}
    void accept(ASTVisitor* visitor) override;
};

struct VarExpr : Expr {
    std::string name;
    VarExpr(const std::string& n) : name(n) {}
    void accept(ASTVisitor* visitor) override;
};

struct StringLiteral : Expr {
    std::string value;
    StringLiteral(const std::string& v) : value(v) {}
    void accept(ASTVisitor* visitor) override;
};

struct CharLiteral : Expr {
    char value;
    CharLiteral(char v) : value(v) {}
    void accept(ASTVisitor* visitor) override;
};

struct FieldExpr : Expr {
    Expr* object;
    std::string field;
    FieldExpr(Expr* obj, const std::string& f) : object(obj), field(f) {}
    void accept(ASTVisitor* visitor) override;
};

struct MethodCallExpr : Expr {
    Expr* object;
    std::string method;
    std::vector<Expr*> args;
    MethodCallExpr(Expr* obj, const std::string& m) : object(obj), method(m) {}
    void accept(ASTVisitor* visitor) override;
};


// ----------------- Statements -----------------
struct ExprStmt : Stmt {
    Expr* expr;
    ExprStmt(Expr* e) : expr(e) {}
    void accept(ASTVisitor* visitor) override;
};

struct VarDecl : Stmt {
    std::string type;
    std::string name;
    Expr* initExpr = nullptr;
    bool isRef = false;

    VarDecl(const std::string& t, const std::string& n, Expr* init)
        : type(t), name(n), initExpr(init) {}

    VarDecl(const std::string& t, const std::string& n)
        : type(t), name(n) {}

    void accept(ASTVisitor* visitor) override;
};



struct BlockStmt : Stmt {
    std::vector<Stmt*> statements;
    void accept(ASTVisitor* visitor) override;
};

struct IfStmt : Stmt {
    Expr* condition;
    BlockStmt* thenBranch;
    BlockStmt* elseBranch = nullptr;
    void accept(ASTVisitor* visitor) override;
};

struct WhileStmt : Stmt {
    Expr* condition;
    BlockStmt* body;
    void accept(ASTVisitor* visitor) override;
};

struct ReturnStmt : Stmt {
    Expr* expr = nullptr;
    void accept(ASTVisitor* visitor) override;
};

// ----------------- Functions & Classes -----------------
struct Param {
    std::string name;
    std::string type;
    bool isRef = false;
};

struct FunctionDecl : Stmt {
    std::string returnType;
    std::string name;
    std::vector<Param*> params;
    BlockStmt* body = nullptr;

    bool isVirtual = false;
    std::string ownerClass;

    void accept(ASTVisitor* visitor) override;
};


struct ClassDecl : Stmt {
    std::string name;
    std::string baseName;
    std::vector<Stmt*> members;
    void accept(ASTVisitor* visitor) override;
};

// ----------------- Program -----------------
struct Program {
    std::vector<Stmt*> statements;
    std::vector<FunctionDecl*> functions;
    std::vector<ClassDecl*> classes;
};

// ----------------- Visitor -----------------
struct ASTVisitor {
    virtual ~ASTVisitor() = default;
    virtual void visit(IntLiteral*) = 0;
    virtual void visit(BinaryExpr*) = 0;
    virtual void visit(UnaryExpr*) = 0;
    virtual void visit(CallExpr*) = 0;
    virtual void visit(AssignExpr*) = 0;
    virtual void visit(ExprStmt*) = 0;
    virtual void visit(VarDecl*) = 0;
    virtual void visit(BlockStmt*) = 0;
    virtual void visit(IfStmt*) = 0;
    virtual void visit(WhileStmt*) = 0;
    virtual void visit(ReturnStmt*) = 0;
    virtual void visit(FunctionDecl*) = 0;
    virtual void visit(ClassDecl*) = 0;
    virtual void visit(VarExpr*) = 0;
    virtual void visit(BoolLiteral*) = 0;
    virtual void visit(CharLiteral*) = 0;
    virtual void visit(StringLiteral*) = 0;
    virtual void visit(FieldExpr*) = 0;
    virtual void visit(MethodCallExpr*) = 0;

};
