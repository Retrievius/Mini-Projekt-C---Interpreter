
// Generated from src/grammar/cpp.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "cppListener.h"


/**
 * This class provides an empty implementation of cppListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  cppBaseListener : public cppListener {
public:

  virtual void enterStart(cppParser::StartContext * /*ctx*/) override { }
  virtual void exitStart(cppParser::StartContext * /*ctx*/) override { }

  virtual void enterTopLevelDecl(cppParser::TopLevelDeclContext * /*ctx*/) override { }
  virtual void exitTopLevelDecl(cppParser::TopLevelDeclContext * /*ctx*/) override { }

  virtual void enterClassDecl(cppParser::ClassDeclContext * /*ctx*/) override { }
  virtual void exitClassDecl(cppParser::ClassDeclContext * /*ctx*/) override { }

  virtual void enterClassBody(cppParser::ClassBodyContext * /*ctx*/) override { }
  virtual void exitClassBody(cppParser::ClassBodyContext * /*ctx*/) override { }

  virtual void enterAccessSpec(cppParser::AccessSpecContext * /*ctx*/) override { }
  virtual void exitAccessSpec(cppParser::AccessSpecContext * /*ctx*/) override { }

  virtual void enterClassMember(cppParser::ClassMemberContext * /*ctx*/) override { }
  virtual void exitClassMember(cppParser::ClassMemberContext * /*ctx*/) override { }

  virtual void enterFieldDecl(cppParser::FieldDeclContext * /*ctx*/) override { }
  virtual void exitFieldDecl(cppParser::FieldDeclContext * /*ctx*/) override { }

  virtual void enterCtorDecl(cppParser::CtorDeclContext * /*ctx*/) override { }
  virtual void exitCtorDecl(cppParser::CtorDeclContext * /*ctx*/) override { }

  virtual void enterMethodDecl(cppParser::MethodDeclContext * /*ctx*/) override { }
  virtual void exitMethodDecl(cppParser::MethodDeclContext * /*ctx*/) override { }

  virtual void enterFnDecl(cppParser::FnDeclContext * /*ctx*/) override { }
  virtual void exitFnDecl(cppParser::FnDeclContext * /*ctx*/) override { }

  virtual void enterParams(cppParser::ParamsContext * /*ctx*/) override { }
  virtual void exitParams(cppParser::ParamsContext * /*ctx*/) override { }

  virtual void enterParam(cppParser::ParamContext * /*ctx*/) override { }
  virtual void exitParam(cppParser::ParamContext * /*ctx*/) override { }

  virtual void enterStmt(cppParser::StmtContext * /*ctx*/) override { }
  virtual void exitStmt(cppParser::StmtContext * /*ctx*/) override { }

  virtual void enterVardecl(cppParser::VardeclContext * /*ctx*/) override { }
  virtual void exitVardecl(cppParser::VardeclContext * /*ctx*/) override { }

  virtual void enterAssign(cppParser::AssignContext * /*ctx*/) override { }
  virtual void exitAssign(cppParser::AssignContext * /*ctx*/) override { }

  virtual void enterExprStmt(cppParser::ExprStmtContext * /*ctx*/) override { }
  virtual void exitExprStmt(cppParser::ExprStmtContext * /*ctx*/) override { }

  virtual void enterBlock(cppParser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(cppParser::BlockContext * /*ctx*/) override { }

  virtual void enterWhileStmt(cppParser::WhileStmtContext * /*ctx*/) override { }
  virtual void exitWhileStmt(cppParser::WhileStmtContext * /*ctx*/) override { }

  virtual void enterIfStmt(cppParser::IfStmtContext * /*ctx*/) override { }
  virtual void exitIfStmt(cppParser::IfStmtContext * /*ctx*/) override { }

  virtual void enterReturnStmt(cppParser::ReturnStmtContext * /*ctx*/) override { }
  virtual void exitReturnStmt(cppParser::ReturnStmtContext * /*ctx*/) override { }

  virtual void enterExpr(cppParser::ExprContext * /*ctx*/) override { }
  virtual void exitExpr(cppParser::ExprContext * /*ctx*/) override { }

  virtual void enterAssignExpr(cppParser::AssignExprContext * /*ctx*/) override { }
  virtual void exitAssignExpr(cppParser::AssignExprContext * /*ctx*/) override { }

  virtual void enterLogicalOrExpr(cppParser::LogicalOrExprContext * /*ctx*/) override { }
  virtual void exitLogicalOrExpr(cppParser::LogicalOrExprContext * /*ctx*/) override { }

  virtual void enterLogicalAndExpr(cppParser::LogicalAndExprContext * /*ctx*/) override { }
  virtual void exitLogicalAndExpr(cppParser::LogicalAndExprContext * /*ctx*/) override { }

  virtual void enterEqualityExpr(cppParser::EqualityExprContext * /*ctx*/) override { }
  virtual void exitEqualityExpr(cppParser::EqualityExprContext * /*ctx*/) override { }

  virtual void enterRelationalExpr(cppParser::RelationalExprContext * /*ctx*/) override { }
  virtual void exitRelationalExpr(cppParser::RelationalExprContext * /*ctx*/) override { }

  virtual void enterAdditiveExpr(cppParser::AdditiveExprContext * /*ctx*/) override { }
  virtual void exitAdditiveExpr(cppParser::AdditiveExprContext * /*ctx*/) override { }

  virtual void enterMultiplicativeExpr(cppParser::MultiplicativeExprContext * /*ctx*/) override { }
  virtual void exitMultiplicativeExpr(cppParser::MultiplicativeExprContext * /*ctx*/) override { }

  virtual void enterUnaryExpr(cppParser::UnaryExprContext * /*ctx*/) override { }
  virtual void exitUnaryExpr(cppParser::UnaryExprContext * /*ctx*/) override { }

  virtual void enterPostfixExpr(cppParser::PostfixExprContext * /*ctx*/) override { }
  virtual void exitPostfixExpr(cppParser::PostfixExprContext * /*ctx*/) override { }

  virtual void enterMemberAccess(cppParser::MemberAccessContext * /*ctx*/) override { }
  virtual void exitMemberAccess(cppParser::MemberAccessContext * /*ctx*/) override { }

  virtual void enterCall(cppParser::CallContext * /*ctx*/) override { }
  virtual void exitCall(cppParser::CallContext * /*ctx*/) override { }

  virtual void enterArgs(cppParser::ArgsContext * /*ctx*/) override { }
  virtual void exitArgs(cppParser::ArgsContext * /*ctx*/) override { }

  virtual void enterPrimaryExpr(cppParser::PrimaryExprContext * /*ctx*/) override { }
  virtual void exitPrimaryExpr(cppParser::PrimaryExprContext * /*ctx*/) override { }

  virtual void enterLiteral(cppParser::LiteralContext * /*ctx*/) override { }
  virtual void exitLiteral(cppParser::LiteralContext * /*ctx*/) override { }

  virtual void enterType(cppParser::TypeContext * /*ctx*/) override { }
  virtual void exitType(cppParser::TypeContext * /*ctx*/) override { }

  virtual void enterBaseType(cppParser::BaseTypeContext * /*ctx*/) override { }
  virtual void exitBaseType(cppParser::BaseTypeContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

