#include "ASTBuilder.h"
#include "ast/AST.h"
#include <stdexcept>
#include "external/antlr4-runtime/runtime/src/antlr4-runtime.h"

Program* ASTBuilder::build(cppParser::StartContext* ctx) {
    auto* prog = new Program();

    for (auto* stmtCtx : ctx->stmt()) {
        prog->statements.push_back(visitStmt(stmtCtx));
    }

    for (auto* declCtx : ctx->topLevelDecl()) {
        // TODO: Klassen und Funktionen hier behandeln
        // prog->statements.push_back(...);
    }

    return prog;
}

// Statements
Stmt* ASTBuilder::visitStmt(cppParser::StmtContext* ctx) {
    if (ctx->vardecl()) {
        auto* expr = ctx->vardecl()->expr() ? visitExpr(ctx->vardecl()->expr()) : nullptr;
        return new VarDecl(/* TODO: Name */ "", expr);
    } else if (ctx->assign()) {
        auto* expr = visitExpr(ctx->assign()->expr());
        return new AssignExpr(/* TODO: Name */ "", expr);
    } else if (ctx->exprStmt()) {
        auto* expr = visitExpr(ctx->exprStmt()->expr());
        return new ExprStmt(expr);
    } else if (ctx->block()) {
        BlockStmt* block = new BlockStmt();
        for (auto* s : ctx->block()->stmt())
            block->statements.push_back(visitStmt(s));
        return block;
    } else if (ctx->ifStmt()) {
        // TODO: IfStmt
    } else if (ctx->whileStmt()) {
        // TODO: WhileStmt
    } else if (ctx->returnStmt()) {
        // TODO: ReturnStmt
    }

    throw std::runtime_error("Unknown statement type");
}

// Expressions
Expr* ASTBuilder::visitExpr(cppParser::ExprContext* ctx) {
    return visitAssignExpr(ctx->assignExpr());
}

Expr* ASTBuilder::visitAssignExpr(cppParser::AssignExprContext* ctx) {
    // Hier nur AdditiveExpr als Beispiel
    return visitAdditiveExpr(ctx->logicalOrExpr()->logicalAndExpr(0)->equalityExpr(0)->relationalExpr(0)->additiveExpr(0));
}

Expr* ASTBuilder::visitAdditiveExpr(cppParser::AdditiveExprContext* ctx) {
    Expr* left = visitMultiplicativeExpr(ctx->multiplicativeExpr(0));
    for (size_t i = 1; i < ctx->multiplicativeExpr().size(); ++i) {
        Expr* right = visitMultiplicativeExpr(ctx->multiplicativeExpr(i));
        // Annahme: nur + Operator für Demo
        left = new BinaryExpr(BinaryExpr::BinaryOp::Add, left, right);
    }
    return left;
}

Expr* ASTBuilder::visitMultiplicativeExpr(cppParser::MultiplicativeExprContext* ctx) {
    Expr* left = visitUnaryExpr(ctx->unaryExpr(0));
    for (size_t i = 1; i < ctx->unaryExpr().size(); ++i) {
        Expr* right = visitUnaryExpr(ctx->unaryExpr(i));
        // Annahme: nur * Operator für Demo
        left = new BinaryExpr(BinaryExpr::BinaryOp::Mul, left, right);
    }
    return left;
}

Expr* ASTBuilder::visitUnaryExpr(cppParser::UnaryExprContext* ctx) {
    if (ctx->postfixExpr()) {
        return visitPrimaryExpr(ctx->postfixExpr()->primaryExpr());
    } else if (ctx->unaryExpr()) {
        Expr* inner = visitUnaryExpr(ctx->unaryExpr());
        // TODO: Unary-Operator abbilden
        return inner;
    }
    throw std::runtime_error("Unknown unary expression");
}

Expr* ASTBuilder::visitPrimaryExpr(cppParser::PrimaryExprContext* ctx) {
    if (ctx->literal()) {
        auto* lit = ctx->literal();
        if (lit->NUMBER()) {
            return new IntLiteral(std::stoi(lit->NUMBER()->getText()));
        }
        // TODO: Strings, Char, Bool
    } else if (ctx->ID()) {
        // TODO: VariableReferenz
    } else if (ctx->expr()) {
        return visitExpr(ctx->expr());
    }
    throw std::runtime_error("Unknown primary expression");
}
