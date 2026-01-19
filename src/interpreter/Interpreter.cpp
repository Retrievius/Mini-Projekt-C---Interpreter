/* Wie arbeitet der Interpreter */

#include "Interpreter.h"
#include <stdexcept>
#include <iostream>
#include <ostream>

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

  // 1. Klassen registrieren
  for (auto* c : program->classes) {
    classes[c->name] = c;
  }

  // 2. Funktionen registrieren
  for (auto* f : program->functions) {
    functions[f->name] = f;
  }

  // 3. Top-Level Statements ausführen (falls vorhanden)
  for (auto* stmt : program->statements) {
    execStmt(stmt);
  }

  // 4. main() suchen und starten
  auto it = functions.find("main");
  if (it == functions.end()) {
    throw std::runtime_error("No main() function found");
  }

  CallExpr callMain("main");
  visit(&callMain);
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

  switch (e->op) {

    // -------- Arithmetik --------
    case BinaryExpr::BinaryOp::Add:
      currentValue = Value::makeInt(lhs.intValue + rhs.intValue);
      return;
    case BinaryExpr::BinaryOp::Sub:
      currentValue = Value::makeInt(lhs.intValue - rhs.intValue);
      return;
    case BinaryExpr::BinaryOp::Mul:
      currentValue = Value::makeInt(lhs.intValue * rhs.intValue);
      return;
    case BinaryExpr::BinaryOp::Div:
      if (rhs.intValue == 0) throw std::runtime_error("Division by zero");
      currentValue = Value::makeInt(lhs.intValue / rhs.intValue);
      return;
    case BinaryExpr::BinaryOp::Mod:
      currentValue = Value::makeInt(lhs.intValue % rhs.intValue);
      return;

      // -------- Vergleiche --------
    case BinaryExpr::BinaryOp::Eq:
      currentValue = Value::makeBool(lhs.intValue == rhs.intValue);
      return;
    case BinaryExpr::BinaryOp::Neq:
      currentValue = Value::makeBool(lhs.intValue != rhs.intValue);
      return;
    case BinaryExpr::BinaryOp::Lt:
      currentValue = Value::makeBool(lhs.intValue < rhs.intValue);
      return;
    case BinaryExpr::BinaryOp::Le:
      currentValue = Value::makeBool(lhs.intValue <= rhs.intValue);
      return;
    case BinaryExpr::BinaryOp::Gt:
      currentValue = Value::makeBool(lhs.intValue > rhs.intValue);
      return;
    case BinaryExpr::BinaryOp::Ge:
      currentValue = Value::makeBool(lhs.intValue >= rhs.intValue);
      return;

      // -------- Logik --------
    case BinaryExpr::BinaryOp::And:
      currentValue = Value::makeBool(lhs.isTrue() && rhs.isTrue());
      return;
    case BinaryExpr::BinaryOp::Or:
      currentValue = Value::makeBool(lhs.isTrue() || rhs.isTrue());
      return;
  }

  throw std::runtime_error("Unsupported binary operator");
}



//
void Interpreter::visit(UnaryExpr* e) {
  Value v = evalExpr(e->expr);

  switch (e->op) {
    case UnaryExpr::UnaryOp::Neg:
      currentValue = Value::makeInt(-v.intValue);
      return;
    case UnaryExpr::UnaryOp::Not:
      currentValue = Value::makeBool(!v.isTrue());
      return;
  }

  throw std::runtime_error("Unsupported unary operator");
}

// Bool-Literal
void Interpreter::visit(BoolLiteral* lit) {
  currentValue = Value::makeBool(lit->value);
}

void Interpreter::visit(CharLiteral* lit) {
  currentValue = Value::makeChar(lit->value);
}

void Interpreter::visit(StringLiteral* lit) {
  currentValue = Value::makeString(lit->value);
}


// Variablen-Zugriff
void Interpreter::visit(VarExpr* var) {
  Cell* cell = resolveVariable(var->name);
  currentValue = cell->get();
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

  // Referenz?
  if (decl->isRef) {

    if (!decl->initExpr)
      throw std::runtime_error("Reference must be initialized");

    // Initialwert MUSS Variable sein
    auto* varExpr = dynamic_cast<VarExpr*>(decl->initExpr);
    if (!varExpr)
      throw std::runtime_error("Reference must bind to variable");

    Cell* target = resolveVariable(varExpr->name);

    Cell* cell = new Cell();
    cell->alias = target;   // ← DAS ist der Trick

    frame().locals[decl->name] = cell;
    return;
  }

  // Normale Variable
  Cell* cell = new Cell();
  if (decl->initExpr) {
    cell->value = evalExpr(decl->initExpr);
  } else {
    cell->value = Value::makeInt(0);
  }

  frame().locals[decl->name] = cell;
}



// Zuweisung: Findet Cell der Variable
void Interpreter::visit(AssignExpr* assign) {
  Cell* target = resolveVariable(assign->name);
  // Schreibt neue Value in bestehende Cell
  Value rhs = evalExpr(assign->expr);
  target->get() = rhs;
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
  if (cond.isTrue()) {
    execStmt(stmt->thenBranch);
  } else if (stmt->elseBranch) {
    execStmt(stmt->elseBranch);
  }
}

// While
void Interpreter::visit(WhileStmt* stmt) {
  while (evalExpr(stmt->condition).isTrue()) {
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

  // -------- Builtins --------
  if (call->functionName == "print_int") {
    Value v = evalExpr(call->args[0]);
    std::cout << v.intValue << std::endl;
    currentValue = Value::makeVoid();
    return;
  }

  if (call->functionName == "print_bool") {
    Value v = evalExpr(call->args[0]);
    std::cout << (v.boolValue ? "true" : "false") << std::endl;
    currentValue = Value::makeVoid();
    return;
  }

  if (call->functionName == "print_char") {
    Value v = evalExpr(call->args[0]);
    std::cout << v.charValue << std::endl;
    currentValue = Value::makeVoid();
    return;
  }

  if (call->functionName == "print_string") {
    Value v = evalExpr(call->args[0]);
    std::cout << v.stringValue << std::endl;
    currentValue = Value::makeVoid();
    return;
  }

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

  // 3. Parameter binden
  for (size_t i = 0; i < func->params.size(); ++i) {
    Param* param = func->params[i];

    if (func->params[i]->isRef) {
      // Argument MUSS Variable sein
      auto* varExpr = dynamic_cast<VarExpr*>(call->args[i]);
      if (!varExpr)
        throw std::runtime_error("Reference parameter requires variable");

      Cell* target = resolveVariable(varExpr->name);

      Cell* cell = new Cell();
      cell->alias = target;   // ← Alias

      newFrame.locals[func->params[i]->name] = cell;
    } else {
      Cell* cell = new Cell();
      cell->value = argValues[i];
      newFrame.locals[func->params[i]->name] = cell;
    }
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
