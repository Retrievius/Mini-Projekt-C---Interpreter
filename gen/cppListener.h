
// Generated from src/grammar/cpp.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "cppParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by cppParser.
 */
class  cppListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterStart(cppParser::StartContext *ctx) = 0;
  virtual void exitStart(cppParser::StartContext *ctx) = 0;

  virtual void enterTopLevelDecl(cppParser::TopLevelDeclContext *ctx) = 0;
  virtual void exitTopLevelDecl(cppParser::TopLevelDeclContext *ctx) = 0;

  virtual void enterClassDecl(cppParser::ClassDeclContext *ctx) = 0;
  virtual void exitClassDecl(cppParser::ClassDeclContext *ctx) = 0;

  virtual void enterClassBody(cppParser::ClassBodyContext *ctx) = 0;
  virtual void exitClassBody(cppParser::ClassBodyContext *ctx) = 0;

  virtual void enterAccessSpec(cppParser::AccessSpecContext *ctx) = 0;
  virtual void exitAccessSpec(cppParser::AccessSpecContext *ctx) = 0;

  virtual void enterClassMember(cppParser::ClassMemberContext *ctx) = 0;
  virtual void exitClassMember(cppParser::ClassMemberContext *ctx) = 0;

  virtual void enterFieldDecl(cppParser::FieldDeclContext *ctx) = 0;
  virtual void exitFieldDecl(cppParser::FieldDeclContext *ctx) = 0;

  virtual void enterCtorDecl(cppParser::CtorDeclContext *ctx) = 0;
  virtual void exitCtorDecl(cppParser::CtorDeclContext *ctx) = 0;

  virtual void enterMethodDecl(cppParser::MethodDeclContext *ctx) = 0;
  virtual void exitMethodDecl(cppParser::MethodDeclContext *ctx) = 0;

  virtual void enterFnDecl(cppParser::FnDeclContext *ctx) = 0;
  virtual void exitFnDecl(cppParser::FnDeclContext *ctx) = 0;

  virtual void enterParams(cppParser::ParamsContext *ctx) = 0;
  virtual void exitParams(cppParser::ParamsContext *ctx) = 0;

  virtual void enterParam(cppParser::ParamContext *ctx) = 0;
  virtual void exitParam(cppParser::ParamContext *ctx) = 0;

  virtual void enterStmt(cppParser::StmtContext *ctx) = 0;
  virtual void exitStmt(cppParser::StmtContext *ctx) = 0;

  virtual void enterVardecl(cppParser::VardeclContext *ctx) = 0;
  virtual void exitVardecl(cppParser::VardeclContext *ctx) = 0;

  virtual void enterAssign(cppParser::AssignContext *ctx) = 0;
  virtual void exitAssign(cppParser::AssignContext *ctx) = 0;

  virtual void enterExprStmt(cppParser::ExprStmtContext *ctx) = 0;
  virtual void exitExprStmt(cppParser::ExprStmtContext *ctx) = 0;

  virtual void enterBlock(cppParser::BlockContext *ctx) = 0;
  virtual void exitBlock(cppParser::BlockContext *ctx) = 0;

  virtual void enterWhileStmt(cppParser::WhileStmtContext *ctx) = 0;
  virtual void exitWhileStmt(cppParser::WhileStmtContext *ctx) = 0;

  virtual void enterIfStmt(cppParser::IfStmtContext *ctx) = 0;
  virtual void exitIfStmt(cppParser::IfStmtContext *ctx) = 0;

  virtual void enterReturnStmt(cppParser::ReturnStmtContext *ctx) = 0;
  virtual void exitReturnStmt(cppParser::ReturnStmtContext *ctx) = 0;

  virtual void enterExpr(cppParser::ExprContext *ctx) = 0;
  virtual void exitExpr(cppParser::ExprContext *ctx) = 0;

  virtual void enterAssignExpr(cppParser::AssignExprContext *ctx) = 0;
  virtual void exitAssignExpr(cppParser::AssignExprContext *ctx) = 0;

  virtual void enterLogicalOrExpr(cppParser::LogicalOrExprContext *ctx) = 0;
  virtual void exitLogicalOrExpr(cppParser::LogicalOrExprContext *ctx) = 0;

  virtual void enterLogicalAndExpr(cppParser::LogicalAndExprContext *ctx) = 0;
  virtual void exitLogicalAndExpr(cppParser::LogicalAndExprContext *ctx) = 0;

  virtual void enterEqualityExpr(cppParser::EqualityExprContext *ctx) = 0;
  virtual void exitEqualityExpr(cppParser::EqualityExprContext *ctx) = 0;

  virtual void enterRelationalExpr(cppParser::RelationalExprContext *ctx) = 0;
  virtual void exitRelationalExpr(cppParser::RelationalExprContext *ctx) = 0;

  virtual void enterAdditiveExpr(cppParser::AdditiveExprContext *ctx) = 0;
  virtual void exitAdditiveExpr(cppParser::AdditiveExprContext *ctx) = 0;

  virtual void enterMultiplicativeExpr(cppParser::MultiplicativeExprContext *ctx) = 0;
  virtual void exitMultiplicativeExpr(cppParser::MultiplicativeExprContext *ctx) = 0;

  virtual void enterUnaryExpr(cppParser::UnaryExprContext *ctx) = 0;
  virtual void exitUnaryExpr(cppParser::UnaryExprContext *ctx) = 0;

  virtual void enterPostfixExpr(cppParser::PostfixExprContext *ctx) = 0;
  virtual void exitPostfixExpr(cppParser::PostfixExprContext *ctx) = 0;

  virtual void enterMemberAccess(cppParser::MemberAccessContext *ctx) = 0;
  virtual void exitMemberAccess(cppParser::MemberAccessContext *ctx) = 0;

  virtual void enterCall(cppParser::CallContext *ctx) = 0;
  virtual void exitCall(cppParser::CallContext *ctx) = 0;

  virtual void enterArgs(cppParser::ArgsContext *ctx) = 0;
  virtual void exitArgs(cppParser::ArgsContext *ctx) = 0;

  virtual void enterPrimaryExpr(cppParser::PrimaryExprContext *ctx) = 0;
  virtual void exitPrimaryExpr(cppParser::PrimaryExprContext *ctx) = 0;

  virtual void enterLiteral(cppParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(cppParser::LiteralContext *ctx) = 0;

  virtual void enterType(cppParser::TypeContext *ctx) = 0;
  virtual void exitType(cppParser::TypeContext *ctx) = 0;

  virtual void enterBaseType(cppParser::BaseTypeContext *ctx) = 0;
  virtual void exitBaseType(cppParser::BaseTypeContext *ctx) = 0;


};

