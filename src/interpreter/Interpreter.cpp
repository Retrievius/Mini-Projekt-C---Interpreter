/* Wie arbeitet der Interpreter */

#include "Interpreter.h"
#include <stdexcept>

// Konstruktor: Beim Start wird ein StackFrame erzeugt
Interpreter::Interpreter() {
  callStack.emplace_back(); // global / session frame
}

// Aktueller Frame: Gibt immer denn obersten StackFrame (aktuell gültigen Scope) zurück
StackFrame& Interpreter::frame() {
  return callStack.back();
}

// Programmausführung
void Interpreter::run(Program* program) {
  for (auto* stmt : program->statements) {
    execStmt(stmt);
  }
}

// --------------------
// Expressions: liefern Value
// --------------------

// evalExpr: gibt currentValue
Value Interpreter::evalExpr(Expr* expr) {
  expr->accept(this);
  return currentValue;
}

// Integer-Literal: erzeugt Value und speichert in currentValue
void Interpreter::visit(IntLiteral* lit) {
  currentValue = Value::makeInt(lit->value);
}

// Binärer Ausdruck: Rekursive Auswertung links dann rechts
void Interpreter::visit(BinaryExpr* e) {
  Value lhs = evalExpr(e->lhs);
  Value rhs = evalExpr(e->rhs);

  // Berechnet lhs +, -, *, / rhs und speichert Ergebnis in currentValue
  switch (e->op) {
    case BinaryExpr::BinaryOp::Add: currentValue = Value::makeInt(lhs.intValue + rhs.intValue); break;
    case BinaryExpr::BinaryOp::Sub: currentValue = Value::makeInt(lhs.intValue - rhs.intValue); break;
    case BinaryExpr::BinaryOp::Mul: currentValue = Value::makeInt(lhs.intValue * rhs.intValue); break;
    case BinaryExpr::BinaryOp::Div: currentValue = Value::makeInt(lhs.intValue / rhs.intValue); break;
    return;
  }
  // Fehlermeldung bei nicht implementiertem Operator
  throw std::runtime_error("Unsupported binary operator");
}

//
void Interpreter::visit(UnaryExpr* e) {
  Value v = evalExpr(e->expr);
  if (e->op == UnaryExpr::UnaryOp::Neg)
    currentValue = Value::makeInt(-v.intValue);
}


// --------------------
// Statements: verändern den Zustand
// --------------------

// execStmt: Führt ein Statement aus
void Interpreter::execStmt(Stmt* stmt) {
  stmt->accept(this);
}

// Variablendeklaration: Neue Variable -> neue Cell
void Interpreter::visit(VarDecl* decl) {
  Cell* cell = new Cell();
  // Initialisierung mit Ausdruck oder Default-Wert
  if (decl->initExpr) {
    cell->value = evalExpr(decl->initExpr);
  } else {
    cell->value = Value::makeInt(0);
  }
  // Variable wird im aktuellen StackFrame unter ihrem Namen gespeichert
  frame().locals[decl->name] = cell;
}

// Zuweisung: Findet Cell der Variable
void Interpreter::visit(AssignExpr* assign) {
  Cell* target = resolveVariable(assign->name);
  // Schreibt neue Value in bestehende Cell
  Value rhs = evalExpr(assign->expr);
  target->value = rhs;
  currentValue = rhs;
}

// Block: neuer Block -> neuer StackFrame
void Interpreter::visit(BlockStmt* block) {
  callStack.emplace_back(); // neuer Scope
  // Statements laufen im neuen Scope
  for (auto* stmt : block->statements) {
    execStmt(stmt);
  }
  // Scope endet -> Variablen verschwinden
  callStack.pop_back();
}

// If
void Interpreter::visit(IfStmt* stmt) {
  Value cond = evalExpr(stmt->condition);
  // Implizite Bool-Konvertierung
  if (cond.intValue != 0) {
    execStmt(stmt->thenBranch);
  } else if (stmt->elseBranch) {
    execStmt(stmt->elseBranch);
  }
}

// While
void Interpreter::visit(WhileStmt* stmt) {
  while (evalExpr(stmt->condition).intValue != 0) {
    execStmt(stmt->body);
  }
}

// Return
void Interpreter::visit(ReturnStmt* stmt) {
  Value v = stmt->expr ? evalExpr(stmt->expr) : Value::makeVoid();
  throw ReturnSignal{v};
}

void Interpreter::visit(FunctionDecl* decl) {
  functions[decl->name] = decl;
}

void Interpreter::visit(CallExpr* call) {
  auto it = functions.find(call->functionName);
  if (it == functions.end()) {
    throw std::runtime_error("Unknown function: " + call->functionName);
  }

  FunctionDecl* func = it->second;

  // 1. Argumente auswerten
  std::vector<Value> argValues;
  for (auto* arg : call->args) {
    argValues.push_back(evalExpr(arg));
  }

  // 2. Neuer StackFrame
  callStack.emplace_back();
  StackFrame& newFrame = frame();

  // 3. Parameter binden (ALS CELLS!)
  for (size_t i = 0; i < func->params.size(); ++i) {
    Cell* cell = new Cell();
    cell->value = argValues[i];
    newFrame.locals[func->params[i]->name] = cell;
  }

  // 4. Body ausführen + Return abfangen
  try {
    execStmt(func->body);
    // Falls kein return:
    currentValue = Value::makeVoid();
  }
  catch (ReturnSignal& r) {
    currentValue = r.value;
  }

  // 5. StackFrame entfernen
  callStack.pop_back();
}

void Interpreter::visit(ClassDecl* decl) {
  classes[decl->name] = decl;
}

void Interpreter::visit(ExprStmt* stmt) {
  evalExpr(stmt->expr);
}

// --------------------
// Helpers
// --------------------

// resolveVariable: liefert Cell aber nicht Value
Cell* Interpreter::resolveVariable(const std::string& name) {
  // Suche
  for (auto it = callStack.rbegin(); it != callStack.rend(); ++it) {
    auto found = it->locals.find(name);
    if (found != it->locals.end()) {
      return found->second;
    }
  }
  // fehler bei undefinierter Variable
  throw std::runtime_error("Undefined variable: " + name);
}
