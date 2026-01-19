/* Was ist der Interpreter */

// Compilerschutz, Datei wird nur einmal eingebunden
#pragma once
#include <vector>
#include "runtime/StackFrame.h"
#include "runtime/Value.h"
#include "ast/AST.h"
#include "ReturnSignal.h"
#include <unordered_map>

// Bekommt von jedem AST-Knoten einen Visit Aufruf
class Interpreter : public ASTVisitor {
// Konstruktor, legt Scope an
public:
  Interpreter();

  // Einstiegspunkt
  void run(Program* program);

  // Führt einen Ausdruck aus und liefert einen Value
  Value evalExpr(Expr* expr);

  // Führt ein Statement aus
  void execStmt(Stmt* stmt);

  // === Visitor ===
  // Jeder Knotenpunkt bekommt eine Methode
  // Methoden enthalten Laufzeitlogik und setzen currentValue
  void visit(IntLiteral*) override;
  void visit(BinaryExpr*) override;
  void visit(UnaryExpr*) override;
  void visit(VarDecl*) override;
  void visit(AssignExpr*) override;
  void visit(BlockStmt*) override;
  void visit(IfStmt*) override;
  void visit(WhileStmt*) override;
  void visit(ReturnStmt*) override;
  void visit(FunctionDecl*) override;
  void visit(CallExpr*) override;
  void visit(ClassDecl*) override;
  void visit(ExprStmt*) override;
  void visit(VarExpr *) override;
  void visit(BoolLiteral *) override;
  void visit(CharLiteral *) override;
  void visit(StringLiteral *) override;





// CallStack: jedes Element ist ein StackFrame
private:
  std::vector<StackFrame> callStack;

  // temporärer Speicher für zuletzt ausgewertete Expression
  Value currentValue;

// Hilfsfunktion: Liefert aktuellen Scope
  StackFrame& frame();
// Sucht eine Variable und gibt Cell zurück
  Cell* resolveVariable(const std::string& name);

  std::unordered_map<std::string, FunctionDecl*> functions;

  std::unordered_map<std::string, ClassDecl*> classes;

};

