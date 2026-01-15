#pragma once
#include "ast/AST.h"
#include "gen/cppParser.h"
#include "external/antlr4-runtime/runtime/src/antlr4-runtime.h"

class ASTBuilder {
public:
    Program* build(cppParser::StartContext* ctx);

private:
    Stmt* visitStmt(cppParser::StmtContext* ctx);
    Expr* visitExpr(cppParser::ExprContext* ctx);
    Expr* visitAssignExpr(cppParser::AssignExprContext* ctx);
    Expr* visitAdditiveExpr(cppParser::AdditiveExprContext* ctx);
    Expr* visitMultiplicativeExpr(cppParser::MultiplicativeExprContext* ctx);
    Expr* visitUnaryExpr(cppParser::UnaryExprContext* ctx);
    Expr* visitPrimaryExpr(cppParser::PrimaryExprContext* ctx);
};
