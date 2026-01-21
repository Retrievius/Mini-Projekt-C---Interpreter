#pragma once
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>

#include "ast/AST.h"
#include "SymbolTable.h"
#include "Type.h"




class SemanticChecker : public ASTVisitor {
public:
    SymbolTable symbols;

    bool builtinsDeclared = false;

    // --- last expression result ---
    Type lastType = Type::Void();
    bool lastIsLValue = false;

    // --- function context ---
    bool inFunction = false;
    Type currentReturnType = Type::Void();
    bool currentAlwaysReturns = false;

    // ---------- Expressions ----------
    void visit(IntLiteral*) override;
    void visit(BoolLiteral*) override;
    void visit(CharLiteral*) override;
    void visit(StringLiteral*) override;

    void visit(VarExpr*) override;
    void visit(UnaryExpr*) override;
    void visit(BinaryExpr*) override;
    void visit(AssignExpr*) override;
    void visit(CallExpr*) override;

    void visit(FieldExpr*) override;
    void visit(MethodCallExpr*) override;

    // ---------- Statements ----------
    void visit(ExprStmt*) override;
    void visit(VarDecl*) override;
    void visit(BlockStmt*) override;
    void visit(IfStmt*) override;
    void visit(WhileStmt*) override;
    void visit(ReturnStmt*) override;

    // ---------- Top level ----------
    void visit(FunctionDecl*) override;
    void visit(ClassDecl*) override;

    // entry helper
    void checkProgram(Program* p);

private:
    // ===== class info table =====
    struct MethodSig {
        std::string name;
        std::vector<Type> params;
        Type ret;
        bool isVirtual = false;
        std::string ownerClass;
    };

    struct ClassInfo {
        std::string name;
        std::string base;
        std::unordered_map<std::string, Type> fields;
        // overloads by name
        std::unordered_map<std::string, std::vector<MethodSig>> methods;
        // constructors: name == class name
        std::vector<MethodSig> ctors;
    };

    std::unordered_map<std::string, ClassInfo> classTable;

    // ----- helpers -----
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

    void evalExprWithLValue(Expr* e) {
        e->accept(this);
        require(lastIsLValue, "Expected LValue");
    }

    static Type parseTypeString(const std::string& t, bool isRefFlag = false);

    // class lookup helpers (inheritance aware)
    const ClassInfo* getClass(const std::string& name) const;
    Type lookupFieldType(const std::string& cls, const std::string& field) const;
    const MethodSig* lookupMethod(const std::string& cls, const std::string& name,
                              const std::vector<Type>& args,
                              const std::vector<bool>& argIsLValue) const;

    const MethodSig* lookupCtor(const std::string& cls,
                                const std::vector<Type>& args) const;


    void buildClassTable(Program* p);
    void declareBuiltins();
};
