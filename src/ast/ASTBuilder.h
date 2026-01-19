#pragma once
#include "ast/AST.h"
#include "gen/cppParser.h"

class ASTBuilder {
public:
    Program* build(cppParser::StartContext* ctx);

private:
    Stmt* visitStmt(cppParser::StmtContext* ctx);

    Expr* visitExpr(cppParser::ExprContext* ctx);
    Expr* visitAssignExpr(cppParser::AssignExprContext* ctx);

    Expr* visitLogicalOrExpr(cppParser::LogicalOrExprContext* ctx);
    Expr* visitLogicalAndExpr(cppParser::LogicalAndExprContext* ctx);
    Expr* visitEqualityExpr(cppParser::EqualityExprContext* ctx);
    Expr* visitRelationalExpr(cppParser::RelationalExprContext* ctx);

    Expr* visitAdditiveExpr(cppParser::AdditiveExprContext* ctx);
    Expr* visitMultiplicativeExpr(cppParser::MultiplicativeExprContext* ctx);
    Expr* visitUnaryExpr(cppParser::UnaryExprContext* ctx);
    Expr* visitPrimaryExpr(cppParser::PrimaryExprContext* ctx);

    Expr* visitPostfixExpr(cppParser::PostfixExprContext* ctx);

    FunctionDecl* visitFnDecl(cppParser::FnDeclContext* ctx);

    Param* visitParam(cppParser::ParamContext* ctx);
    BlockStmt* visitBlock(cppParser::BlockContext* ctx);
    ClassDecl* visitClassDecl(cppParser::ClassDeclContext* ctx);




};

