#include "AST.h"

void Program::accept(ASTVisitor* v) { v->visit(this); }

// Expressions
void IntLiteral::accept(ASTVisitor* v) { v->visit(this); }
void UnaryExpr::accept(ASTVisitor* v) { v->visit(this); }
void BinaryExpr::accept(ASTVisitor* v) { v->visit(this); }
void CallExpr::accept(ASTVisitor* v) { v->visit(this); }
void AssignExpr::accept(ASTVisitor* v) { v->visit(this); }
void BoolLiteral::accept(ASTVisitor* v) { v->visit(this); }
void VarExpr::accept(ASTVisitor* v) { v->visit(this); }
void CharLiteral::accept(ASTVisitor* v) { v->visit(this); }
void StringLiteral::accept(ASTVisitor* v) { v->visit(this); }
void FieldExpr::accept(ASTVisitor* v) { v->visit(this); }
void MethodCallExpr::accept(ASTVisitor* v) { v->visit(this); }

// Statements
void ExprStmt::accept(ASTVisitor* v) { v->visit(this); }
void VarDecl::accept(ASTVisitor* v) { v->visit(this); }
void BlockStmt::accept(ASTVisitor* v) { v->visit(this); }
void IfStmt::accept(ASTVisitor* v) { v->visit(this); }
void WhileStmt::accept(ASTVisitor* v) { v->visit(this); }
void ReturnStmt::accept(ASTVisitor* v) { v->visit(this); }

// Functions & Classes
void FunctionDecl::accept(ASTVisitor* v) { v->visit(this); }
void ClassDecl::accept(ASTVisitor* v) { v->visit(this); }


