#include "ast/AST.h"
#include <iostream>

struct ASTPrinter : public ASTVisitor {
    int indent = 0;

    void printIndent() {
        for (int i = 0; i < indent; ++i) std::cout << "  ";
    }

    void visit(IntLiteral* lit) override {
        printIndent();
        std::cout << "IntLiteral: " << lit->value << "\n";
    }

    void visit(BoolLiteral* lit) override {
        printIndent();
        std::cout << "BoolLiteral: " << (lit->value ? "true" : "false") << "\n";
    }

    void visit(VarExpr* expr) override {
        printIndent();
        std::cout << "VarExpr: " << expr->name << "\n";
    }

    void visit(BinaryExpr* expr) override {
        printIndent();
        std::cout << "BinaryExpr: " << static_cast<int>(expr->op) << "\n";
        indent++;
        expr->lhs->accept(this);
        expr->rhs->accept(this);
        indent--;
    }

    void visit(UnaryExpr* expr) override {
        printIndent();
        std::cout << "UnaryExpr: " << static_cast<int>(expr->op) << "\n";
        indent++;
        expr->expr->accept(this);
        indent--;
    }

    void visit(CallExpr* expr) override {
        printIndent();
        std::cout << "CallExpr: " << expr->functionName << "\n";
        indent++;
        for (auto* arg : expr->args)
            arg->accept(this);
        indent--;
    }

    void visit(AssignExpr* expr) override {
        printIndent();
        std::cout << "AssignExpr\n";
        indent++;
        printIndent(); std::cout << "Target:\n";
        indent++; expr->target->accept(this); indent--;
        printIndent(); std::cout << "Value:\n";
        indent++; expr->expr->accept(this); indent--;
        indent--;
    }

    void visit(VarDecl* stmt) override {
        printIndent();
        std::cout << "VarDecl: " << stmt->name << "\n";
        if (stmt->initExpr) {
            indent++;
            stmt->initExpr->accept(this);
            indent--;
        }
    }

    void visit(ExprStmt* stmt) override {
        printIndent();
        std::cout << "ExprStmt\n";
        indent++;
        stmt->expr->accept(this);
        indent--;
    }

    void visit(BlockStmt* stmt) override {
        printIndent();
        std::cout << "BlockStmt\n";
        indent++;
        for (auto* s : stmt->statements)
            s->accept(this);
        indent--;
    }

    void visit(IfStmt* stmt) override {
        printIndent();
        std::cout << "IfStmt\n";
        indent++;
        printIndent(); std::cout << "Condition:\n";
        indent++; stmt->condition->accept(this); indent--;
        printIndent(); std::cout << "Then:\n";
        indent++; stmt->thenBranch->accept(this); indent--;
        if (stmt->elseBranch) {
            printIndent(); std::cout << "Else:\n";
            indent++; stmt->elseBranch->accept(this); indent--;
        }
        indent--;
    }

    void visit(WhileStmt* stmt) override {
        printIndent();
        std::cout << "WhileStmt\n";
        indent++;
        printIndent(); std::cout << "Condition:\n";
        indent++; stmt->condition->accept(this); indent--;
        printIndent(); std::cout << "Body:\n";
        indent++; stmt->body->accept(this); indent--;
        indent--;
    }

    void visit(ReturnStmt* stmt) override {
        printIndent();
        std::cout << "ReturnStmt\n";
        if (stmt->expr) {
            indent++;
            stmt->expr->accept(this);
            indent--;
        }
    }

    void visit(FunctionDecl* stmt) override {
        printIndent();
        std::cout << "FunctionDecl: " << stmt->name << "\n";
        indent++;
        for (auto* param : stmt->params) {
            printIndent();
            std::cout << "Param: " << param->name << "\n";
        }
        stmt->body->accept(this);
        indent--;
    }

    void visit(ClassDecl* stmt) override {
        printIndent();
        std::cout << "ClassDecl: " << stmt->name << "\n";
        indent++;
        for (auto* member : stmt->members)
            member->accept(this);
        indent--;
    }

    void visit(CharLiteral* lit) override {
        printIndent();
        std::cout << "CharLiteral: '" << lit->value << "'\n";
    }

    void visit(StringLiteral* lit) override {
        printIndent();
        std::cout << "StringLiteral: \"" << lit->value << "\"\n";
    }

    void visit(FieldExpr* e) override {
        printIndent();
        std::cout << "FieldExpr: ." << e->field << "\n";
        indent++;
        e->object->accept(this);
        indent--;
    }

    void visit(MethodCallExpr* e) override {
        printIndent();
        std::cout << "MethodCallExpr: " << e->method << "\n";
        indent++;
        printIndent(); std::cout << "Object:\n";
        indent++; e->object->accept(this); indent--;
        for (auto* a : e->args) a->accept(this);
        indent--;
    }


};
