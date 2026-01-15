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

        auto opToken = ctx->children[2 * i - 1]->getText();

        BinaryExpr::BinaryOp op;
        if (opToken == "+") op = BinaryExpr::BinaryOp::Add;
        else if (opToken == "-") op = BinaryExpr::BinaryOp::Sub;
        else throw std::runtime_error("Unknown additive operator: " + opToken);

        left = new BinaryExpr(op, left, right);
    }

    return left;
}


Expr* ASTBuilder::visitMultiplicativeExpr(cppParser::MultiplicativeExprContext* ctx) {
    Expr* left = visitUnaryExpr(ctx->unaryExpr(0));

    for (size_t i = 1; i < ctx->unaryExpr().size(); ++i) {
        Expr* right = visitUnaryExpr(ctx->unaryExpr(i));

        auto opToken = ctx->children[2 * i - 1]->getText();

        BinaryExpr::BinaryOp op;
        if (opToken == "*") op = BinaryExpr::BinaryOp::Mul;
        else if (opToken == "/") op = BinaryExpr::BinaryOp::Div;
        else if (opToken == "%") {
            throw std::runtime_error("% not supported yet");
        } else {
            throw std::runtime_error("Unknown multiplicative operator: " + opToken);
        }

        left = new BinaryExpr(op, left, right);
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
