#include "ASTBuilder.h"
#include "ast/AST.h"
#include <stdexcept>

using namespace cppParser;

Program* ASTBuilder::build(StartContext* ctx) {
    auto* prog = new Program();

    for (auto* child : ctx->children) {
        if (auto* s = dynamic_cast<StmtContext*>(child)) {
            prog->statements.push_back(visitStmt(s));
        }
        else if (auto* d = dynamic_cast<TopLevelDeclContext*>(child)) {
            // später: Klassen / Funktionen
        }
    }

    return prog;
}


// ================= Statements =================

Stmt* ASTBuilder::visitStmt(StmtContext* ctx) {

    if (ctx->vardecl()) {
        auto* decl = ctx->vardecl();
        std::string name = decl->ID()->getText();
        Expr* init = decl->expr() ? visitExpr(decl->expr()) : nullptr;

        return new VarDecl(name, init);
    }

    if (ctx->assign()) {
        auto* as = ctx->assign();
        std::string name = as->postfixExpr()->getText();
        Expr* value = visitExpr(as->expr());

        return new AssignExpr(name, value);
    }

    if (ctx->exprStmt()) {
        return new ExprStmt(visitExpr(ctx->exprStmt()->expr()));
    }

    if (ctx->block()) {
        auto* b = new BlockStmt();
        for (auto* s : ctx->block()->stmt())
            b->statements.push_back(visitStmt(s));
        return b;
    }

    if (ctx->ifStmt()) {
        auto* s = new IfStmt();
        s->condition = visitExpr(ctx->ifStmt()->expr());
        s->thenBranch = dynamic_cast<BlockStmt*>(visitStmt(ctx->ifStmt()->stmt(0)));

        if (ctx->ifStmt()->stmt().size() > 1)
            s->elseBranch = dynamic_cast<BlockStmt*>(visitStmt(ctx->ifStmt()->stmt(1)));

        return s;
    }

    if (ctx->whileStmt()) {
        auto* s = new WhileStmt();
        s->condition = visitExpr(ctx->whileStmt()->expr());
        s->body = dynamic_cast<BlockStmt*>(visitStmt(ctx->whileStmt()->stmt()));
        return s;
    }

    if (ctx->returnStmt()) {
        auto* r = new ReturnStmt();
        if (ctx->returnStmt()->expr())
            r->expr = visitExpr(ctx->returnStmt()->expr());
        return r;
    }

    throw std::runtime_error("Unknown statement");
}


// ================= Expressions =================

Expr* ASTBuilder::visitExpr(ExprContext* ctx) {
    return visitAssignExpr(ctx->assignExpr());
}

Expr* ASTBuilder::visitAssignExpr(AssignExprContext* ctx) {
    return visitLogicalOrExpr(ctx->logicalOrExpr());
}

Expr* ASTBuilder::visitLogicalOrExpr(LogicalOrExprContext* ctx) {
    Expr* left = visitLogicalAndExpr(ctx->logicalAndExpr(0));

    for (size_t i = 1; i < ctx->logicalAndExpr().size(); ++i) {
        Expr* right = visitLogicalAndExpr(ctx->logicalAndExpr(i));
        left = new BinaryExpr(BinaryExpr::BinaryOp::Or, left, right);
    }
    return left;
}

Expr* ASTBuilder::visitLogicalAndExpr(LogicalAndExprContext* ctx) {
    Expr* left = visitEqualityExpr(ctx->equalityExpr(0));

    for (size_t i = 1; i < ctx->equalityExpr().size(); ++i) {
        Expr* right = visitEqualityExpr(ctx->equalityExpr(i));
        left = new BinaryExpr(BinaryExpr::BinaryOp::And, left, right);
    }
    return left;
}

Expr* ASTBuilder::visitEqualityExpr(EqualityExprContext* ctx) {
    Expr* left = visitRelationalExpr(ctx->relationalExpr(0));

    for (size_t i = 1; i < ctx->relationalExpr().size(); ++i) {
        Expr* right = visitRelationalExpr(ctx->relationalExpr(i));
        std::string op = ctx->children[2 * i - 1]->getText();

        if (op == "==") left = new BinaryExpr(BinaryExpr::BinaryOp::Eq, left, right);
        else if (op == "!=") left = new BinaryExpr(BinaryExpr::BinaryOp::Neq, left, right);
        else throw std::runtime_error("Unknown equality operator");
    }
    return left;
}

Expr* ASTBuilder::visitRelationalExpr(RelationalExprContext* ctx) {
    Expr* left = visitAdditiveExpr(ctx->additiveExpr(0));

    for (size_t i = 1; i < ctx->additiveExpr().size(); ++i) {
        Expr* right = visitAdditiveExpr(ctx->additiveExpr(i));
        std::string op = ctx->children[2 * i - 1]->getText();

        if (op == "<") left = new BinaryExpr(BinaryExpr::BinaryOp::Lt, left, right);
        else if (op == "<=") left = new BinaryExpr(BinaryExpr::BinaryOp::Le, left, right);
        else if (op == ">") left = new BinaryExpr(BinaryExpr::BinaryOp::Gt, left, right);
        else if (op == ">=") left = new BinaryExpr(BinaryExpr::BinaryOp::Ge, left, right);
        else throw std::runtime_error("Unknown relational operator");
    }
    return left;
}

Expr* ASTBuilder::visitAdditiveExpr(AdditiveExprContext* ctx) {
    Expr* left = visitMultiplicativeExpr(ctx->multiplicativeExpr(0));

    for (size_t i = 1; i < ctx->multiplicativeExpr().size(); ++i) {
        Expr* right = visitMultiplicativeExpr(ctx->multiplicativeExpr(i));
        std::string op = ctx->children[2 * i - 1]->getText();

        BinaryExpr::BinaryOp bop = (op == "+") ? BinaryExpr::BinaryOp::Add : BinaryExpr::BinaryOp::Sub;
        left = new BinaryExpr(bop, left, right);
    }
    return left;
}

Expr* ASTBuilder::visitMultiplicativeExpr(MultiplicativeExprContext* ctx) {
    Expr* left = visitUnaryExpr(ctx->unaryExpr(0));

    for (size_t i = 1; i < ctx->unaryExpr().size(); ++i) {
        Expr* right = visitUnaryExpr(ctx->unaryExpr(i));
        std::string op = ctx->children[2 * i - 1]->getText();

        BinaryExpr::BinaryOp bop;
        if (op == "*") bop = BinaryExpr::BinaryOp::Mul;
        else if (op == "/") bop = BinaryExpr::BinaryOp::Div;
        else bop = BinaryExpr::BinaryOp::Mod;

        left = new BinaryExpr(bop, left, right);
    }
    return left;
}

Expr* ASTBuilder::visitUnaryExpr(UnaryExprContext* ctx) {
    if (ctx->postfixExpr())
        return visitPostfixExpr(ctx->postfixExpr());

    Expr* inner = visitUnaryExpr(ctx->unaryExpr());
    std::string op = ctx->children[0]->getText();

    return new UnaryExpr(op == "-") ? UnaryExpr::UnaryOp::Neg : UnaryExpr::UnaryOp::Not, inner;
}

Expr* ASTBuilder::visitPostfixExpr(PostfixExprContext* ctx) {
    return visitPrimaryExpr(ctx->primaryExpr());
}

Expr* ASTBuilder::visitPrimaryExpr(PrimaryExprContext* ctx) {
    if (ctx->NUMBER())
        return new IntLiteral(std::stoi(ctx->NUMBER()->getText()));

    if (ctx->ID())
        return new VarExpr(ctx->ID()->getText());

    return visitExpr(ctx->expr());
}