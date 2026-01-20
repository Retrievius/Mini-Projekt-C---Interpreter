/* Wie arbeitet der Interpreter */

#include "Interpreter.h"
#include <stdexcept>
#include <iostream>
#include <ostream>
#include "runtime/Object.h"
#include <algorithm>
#include <cctype>
#include <functional>

static std::string normalizeType(std::string t);
static bool isBuiltinType(const std::string& t);

// Konstruktor: Beim Start wird ein StackFrame erzeugt
Interpreter::Interpreter() {
  callStack.emplace_back(); // global / session frame
}

// Aktueller Frame: Gibt immer denn obersten StackFrame (aktuell gültigen Scope) zurück
StackFrame& Interpreter::frame() {
  return callStack.back();
}

void Interpreter::loadProgram(Program* program) {
  // 1. Klassen registrieren
  for (auto* c : program->classes) {
    classes[c->name] = c;
  }

  // 2. Funktionen registrieren (freie Funktionen)
  for (auto* f : program->functions) {
    functions[f->name] = f;
  }

  // 3. Methoden + Ctors aus Klassenmitgliedern registrieren
  for (auto* c : program->classes) {
    for (auto* m : c->members) {
      if (auto* fn = dynamic_cast<FunctionDecl*>(m)) {
        std::string key = c->name + "::" + fn->name;
        functions[key] = fn;
      }
    }
  }
}

void Interpreter::ensureSession() {
  if (sessionIndex != -1) return;

  // global frame existiert schon (Interpreter ctor macht callStack.emplace_back())
  callStack.emplace_back(); // Session-Frame
  sessionIndex = (int)callStack.size() - 1;
}

void Interpreter::execTopLevel(Program* program) {
  ensureSession();
  // Statements immer im Session-Frame ausführen:
  // Wir pushen KEINEN neuen Frame, sondern nutzen den offenen session frame.
  // Daher: temporär auf session frame "gehen", indem wir sicherstellen, dass es top ist:
  // In unserem Modell ist session frame sowieso top, solange du keinen anderen pushst.
  for (auto* stmt : program->statements) {
    execStmt(stmt);
  }
}

void Interpreter::execRepl(Program* program) {
  ensureSession();

  for (auto* stmt : program->statements) {
    // Expression-Statements auto-ausgeben
    if (auto* es = dynamic_cast<ExprStmt*>(stmt)) {
      Value v = evalExpr(es->expr);

      // Nur nicht-void automatisch ausgeben
      if (v.kind != ValueKind::Void) {
        // minimal: int/bool/char/string
        if (v.kind == ValueKind::Int) {
          std::cout << v.intValue << "\n";
        } else if (v.kind == ValueKind::Bool) {
          std::cout << (v.boolValue ? "true" : "false") << "\n";
        } else if (v.kind == ValueKind::Char) {
          std::cout << v.charValue << "\n";
        } else if (v.kind == ValueKind::String) {
          std::cout << v.stringValue << "\n";
        } else {
          // object/sonstiges: erstmal nix oder Debug
          std::cout << "<value>\n";
        }
      }
    } else {
      execStmt(stmt);
    }
  }
}


// Programmausführung
void Interpreter::run(Program* program) {
  // registrieren
  loadProgram(program);

  // Top-Level Statements (falls es welche gibt): im Session scope
  execTopLevel(program);

  // main() optional ausführen, aber Session offen lassen
  auto it = functions.find("main");
  if (it != functions.end()) {
    ensureSession();

    FunctionDecl* mainFn = it->second;

    // main im Session-Frame laufen lassen (kein CallExpr, weil der einen Call-Frame pusht)
    try {
      execStmt(mainFn->body);
    } catch (ReturnSignal&) {
      // main return ignorieren
    }
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
  // 1) lokale Variable?
  for (auto it = callStack.rbegin(); it != callStack.rend(); ++it) {
    auto found = it->locals.find(var->name);
    if (found != it->locals.end()) {
      currentValue = found->second->get();
      return;
    }
  }

  // 2) fallback: field von this?
  // 2) fallback: field von this?
  Cell* thisCell = nullptr;
  for (auto it = callStack.rbegin(); it != callStack.rend(); ++it) {
    auto f = it->locals.find("this");
    if (f != it->locals.end()) {
      thisCell = f->second;
      break;
    }
  }

  if (thisCell) {
    Value thisV = thisCell->get();
    if (thisV.kind == ValueKind::Object) {
      auto fit = thisV.objectValue->fields.find(var->name);
      if (fit != thisV.objectValue->fields.end()) {
        currentValue = fit->second->get();
        return;
      }
    }
  }


  throw std::runtime_error("Undefined variable: " + var->name);
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
    const std::string declType = normalizeType(decl->type);

    // --- Referenzvariable ---
    if (decl->isRef) {
        if (!decl->initExpr) throw std::runtime_error("Reference must be initialized");

        auto* varExpr = dynamic_cast<VarExpr*>(decl->initExpr);
        if (!varExpr) throw std::runtime_error("Reference must bind to variable");

        Cell* target = resolveVariable(varExpr->name);

        Cell* cell = new Cell();
        cell->alias = target;
        cell->staticType = declType;

        frame().locals[decl->name] = cell;
        return;
    }

    // --- Normale Variable ---
    Cell* cell = new Cell();
    cell->staticType = declType;

    // =========================================================
    // 1) MIT initExpr
    // =========================================================
    if (decl->initExpr) {
        Value v = evalExpr(decl->initExpr);

        // Builtins
        if (v.kind != ValueKind::Object) {
            cell->value = v;
            frame().locals[decl->name] = cell;
            return;
        }

        // Objekt-Init (Copy / Slicing)
        const std::string dstType = declType;
        const std::string srcDyn  = normalizeType(v.objectValue->dynamicClass);

        // Slicing?
        if (dstType != srcDyn) {
            if (!isBaseOf(dstType, srcDyn)) {
                throw std::runtime_error("Cannot init " + dstType + " from " + srcDyn);
            }

            auto newObj = std::make_shared<Object>();
            newObj->dynamicClass = dstType;

            for (auto* fieldDecl : collectFields(dstType)) {
                const std::string fname = fieldDecl->name;

                auto itF = v.objectValue->fields.find(fname);
                if (itF == v.objectValue->fields.end())
                    throw std::runtime_error("Missing field in source object: " + fname);

                Cell* fcell = new Cell();
                fcell->staticType = normalizeType(fieldDecl->type);
                fcell->value = itF->second->get(); // value copy
                newObj->fields[fname] = fcell;
            }

            Value nv;
            nv.kind = ValueKind::Object;
            nv.objectValue = newObj;

            cell->value = nv;
            frame().locals[decl->name] = cell;
            return;
        }

        // gleicher Typ -> deep copy
        auto newObj = std::make_shared<Object>();
        newObj->dynamicClass = srcDyn;

        for (auto* fieldDecl : collectFields(srcDyn)) {
            const std::string fname = fieldDecl->name;

            auto itF = v.objectValue->fields.find(fname);
            if (itF == v.objectValue->fields.end())
                throw std::runtime_error("Missing field in source object: " + fname);

            Cell* fcell = new Cell();
            fcell->staticType = normalizeType(fieldDecl->type);
            fcell->value = itF->second->get();
            newObj->fields[fname] = fcell;
        }

        Value nv;
        nv.kind = ValueKind::Object;
        nv.objectValue = newObj;

        cell->value = nv;
        frame().locals[decl->name] = cell;
        return;
    }

    // =========================================================
    // 2) OHNE initExpr  (Default-Konstruktion)
    // =========================================================
    if (declType == "int") {
        cell->value = Value::makeInt(0);
        frame().locals[decl->name] = cell;
        return;
    }
    if (declType == "bool") {
        cell->value = Value::makeBool(false);
        frame().locals[decl->name] = cell;
        return;
    }
    if (declType == "char") {
        cell->value = Value::makeChar('\0');
        frame().locals[decl->name] = cell;
        return;
    }
    if (declType == "string") {
        cell->value = Value::makeString("");
        frame().locals[decl->name] = cell;
        return;
    }

    // --- Klassenobjekt anlegen ---
    auto clsIt = classes.find(declType);
    if (clsIt == classes.end()) throw std::runtime_error("Unknown type: " + declType);

    auto obj = std::make_shared<Object>();
    obj->dynamicClass = declType;

    for (auto* fieldDecl : collectFields(declType)) {
        Cell* fcell = new Cell();
        const std::string ft = normalizeType(fieldDecl->type);
        fcell->staticType = ft;

        if (ft == "int") fcell->value = Value::makeInt(0);
        else if (ft == "bool") fcell->value = Value::makeBool(false);
        else if (ft == "char") fcell->value = Value::makeChar('\0');
        else if (ft == "string") fcell->value = Value::makeString("");
        else fcell->value = Value::makeVoid();

        obj->fields[fieldDecl->name] = fcell;
    }

    Value objV;
    objV.kind = ValueKind::Object;
    objV.objectValue = obj;
    cell->value = objV;

    // Variable ist jetzt sichtbar
    frame().locals[decl->name] = cell;

    // Default-ctor Point() ausführen, falls existiert
    if (FunctionDecl* ctor = findCtor(declType, 0)) {
        callStack.emplace_back();
        StackFrame& newFrame = frame();

        Cell* thisCell = new Cell();
        thisCell->value = objV;
        thisCell->staticType = declType;
        newFrame.locals["this"] = thisCell;

        try { execStmt(ctor->body); }
        catch (ReturnSignal&) { /* ctor return ignorieren */ }

        callStack.pop_back();
    }
}

// Zuweisung: Findet Cell der Variable
void Interpreter::visit(AssignExpr* assign) {
  Cell* target = resolveLValue(assign->target);
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

  // --- Constructor call?  Point(3,4) ---
  //std::cerr << "CtorCheck: [" << call->functionName << "]\n";
auto clsIt = classes.find(call->functionName);
if (clsIt != classes.end()) {

    const std::string className = call->functionName;

    // 1) Objekt erstellen + Felder anlegen (wie bei VarDecl-Klassenobjekt)
    auto obj = std::make_shared<Object>();
    obj->dynamicClass = className;

    // Felder (inkl Basen) anlegen – du hast sowas schon in VarDecl, am besten als Helper auslagern.
    for (auto* fieldDecl : collectFields(className)) {
        Cell* fcell = new Cell();
        fcell->staticType = normalizeType(fieldDecl->type);

        const std::string ft = fcell->staticType;
        if (ft == "int") fcell->value = Value::makeInt(0);
        else if (ft == "bool") fcell->value = Value::makeBool(false);
        else if (ft == "char") fcell->value = Value::makeChar('\0');
        else if (ft == "string") fcell->value = Value::makeString("");
        else fcell->value = Value::makeVoid();

        obj->fields[fieldDecl->name] = fcell;
    }

    Value objV;
    objV.kind = ValueKind::Object;
    objV.objectValue = obj;

    // 2) ctor suchen nach Argumentanzahl
    FunctionDecl* ctor = findCtor(className, call->args.size());
  if (!ctor && call->args.size() != 0) {
    throw std::runtime_error("No matching constructor: " + className +
                             "(" + std::to_string(call->args.size()) + ")");
  }

    // 3) Argumente auswerten
    std::vector<Value> argValues;
    for (auto* a : call->args) argValues.push_back(evalExpr(a));

    // 4) falls ctor existiert: call-frame, this binden, params binden, body ausführen
    if (ctor) {

      CallDepthGuard guard(*this);

        callStack.emplace_back();
        StackFrame& newFrame = frame();

        Cell* thisCell = new Cell();
        thisCell->value = objV;
        thisCell->staticType = className;
        newFrame.locals["this"] = thisCell;

        for (size_t i = 0; i < ctor->params.size(); ++i) {
            Param* param = ctor->params[i];
            const std::string pType = normalizeType(param->type);

            Cell* cell = new Cell();
            cell->value = argValues[i];
            cell->staticType = pType;
            newFrame.locals[param->name] = cell;
        }

        try {
            execStmt(ctor->body);
        } catch (ReturnSignal&) {
            // ctor return ignorieren / verbieten
        }

        callStack.pop_back();
    }

    // 5) Ergebnis ist das Objekt
    currentValue = objV;
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

  CallDepthGuard guard(*this);

  callStack.emplace_back();
  StackFrame& newFrame = frame();

  // 3. Parameter binden
  for (size_t i = 0; i < func->params.size(); ++i) {
    Param* param = func->params[i];
    const std::string pType = normalizeType(param->type);

    if (param->isRef) {
      auto* varExpr = dynamic_cast<VarExpr*>(call->args[i]);
      if (!varExpr)
        throw std::runtime_error("Reference parameter requires variable");

      Cell* target = resolveVariable(varExpr->name);

      Cell* cell = new Cell();
      cell->alias = target;
      cell->staticType = pType;                     // << WICHTIG: Base bei Base& p

      newFrame.locals[param->name] = cell;
    } else {
      Cell* cell = new Cell();
      cell->value = argValues[i];
      cell->staticType = pType;                     // << WICHTIG: auch bei Value-Param

      newFrame.locals[param->name] = cell;
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

void Interpreter::visit(FieldExpr* fe) {
  Cell* c = resolveLValue(fe);   // liefert Field-Cell
  currentValue = c->get();
}

void Interpreter::visit(MethodCallExpr* mc) {
    // 1) Objekt auswerten
    Value objV = evalExpr(mc->object);
    if (objV.kind != ValueKind::Object) {
        throw std::runtime_error("Method call on non-object");
    }

    // 2) statischen Typ bestimmen (für static dispatch)
    std::string staticType;

    // Falls object ein VarExpr ist, nehmen wir dessen Cell->staticType
    if (auto* v = dynamic_cast<VarExpr*>(mc->object)) {
        Cell* c = resolveVariable(v->name);
        staticType = c->staticType;
    } else {
        // Fallback: wenn wir den statischen Typ nicht kennen, nimm dynamicClass
        staticType = objV.objectValue->dynamicClass;
    }

    staticType = normalizeType(staticType);

    // 3) dyn. Typ bestimmen (für virtual dispatch)
    std::string dynamicType = normalizeType(objV.objectValue->dynamicClass);

    // 4) Methode anhand staticType suchen (damit wir wissen, ob virtual)
    //    Wir suchen entlang der Vererbungskette.
    auto findMethodInClassChain = [&](const std::string& startClass) -> FunctionDecl* {
        std::string cur = startClass;
        while (!cur.empty()) {
            auto it = functions.find(cur + "::" + mc->method);
            if (it != functions.end()) return it->second;

            auto cit = classes.find(cur);
            if (cit == classes.end()) break;
            cur = cit->second->baseName;
        }
        return nullptr;
    };

    FunctionDecl* staticMethod = findMethodInClassChain(staticType);
    if (!staticMethod) {
        throw std::runtime_error("Unknown method: " + staticType + "::" + mc->method);
    }

    // 5) Zielmethode wählen
    FunctionDecl* targetMethod = staticMethod;

    if (staticMethod->isVirtual) {
        // virtual -> dynamic dispatch: in dynamicType suchen (auch entlang base chain)
        FunctionDecl* dynMethod = findMethodInClassChain(dynamicType);
        if (!dynMethod) {
            // Wenn Der keine override hat, fällt es auf Base zurück
            dynMethod = staticMethod;
        }
        targetMethod = dynMethod;
    }

    // 6) Argumente auswerten
    std::vector<Value> argValues;
    for (auto* a : mc->args) {
        argValues.push_back(evalExpr(a));
    }

    // 7) Call-Frame erstellen

  CallDepthGuard guard(*this);

    callStack.emplace_back();
    StackFrame& newFrame = frame();

    // 8) implizites this binden
    Cell* thisCell = new Cell();
    thisCell->value = objV;
    thisCell->staticType = targetMethod->ownerClass; // "Base" oder "Der" (passend zum Body)
    newFrame.locals["this"] = thisCell;

    // 9) normale Parameter binden (wie bei CallExpr)
    for (size_t i = 0; i < targetMethod->params.size(); ++i) {
        Param* param = targetMethod->params[i];
        const std::string pType = normalizeType(param->type);

        if (param->isRef) {
            auto* varExpr = dynamic_cast<VarExpr*>(mc->args[i]);
            if (!varExpr)
                throw std::runtime_error("Reference parameter requires variable");

            Cell* target = resolveVariable(varExpr->name);

            Cell* cell = new Cell();
            cell->alias = target;
            cell->staticType = pType;
            newFrame.locals[param->name] = cell;
        } else {
            Cell* cell = new Cell();
            cell->value = argValues[i];
            cell->staticType = pType;
            newFrame.locals[param->name] = cell;
        }
    }

    // 10) Body ausführen + return abfangen
    try {
        execStmt(targetMethod->body);
        currentValue = Value::makeVoid();
    }
    catch (ReturnSignal& r) {
        currentValue = r.value;
    }

    callStack.pop_back();
}


// --------------------
// Helpers
// --------------------

// resolveVariable: liefert Cell aber nicht Value
Cell* Interpreter::resolveVariable(const std::string& name) {
  for (int i = (int)callStack.size() - 1; i >= 0; --i) {

    // In Funktions-/Methoden-/Ctor-Calls darf Session NICHT sichtbar sein
    if (callDepth > 0 && i == sessionIndex) continue;

    auto found = callStack[i].locals.find(name);
    if (found != callStack[i].locals.end()) return found->second;
  }
  throw std::runtime_error("Undefined variable: " + name);
}

Cell* Interpreter::resolveLValue(Expr* e) {
  if (auto* v = dynamic_cast<VarExpr*>(e)) {

    // 1) normale Variable (lokal / outer scopes)
    for (auto it = callStack.rbegin(); it != callStack.rend(); ++it) {
      auto found = it->locals.find(v->name);
      if (found != it->locals.end()) return found->second;
    }

    // 2) fallback: this.<field> (für ctor/method bodies)
    Cell* thisCell = nullptr;
    for (auto it = callStack.rbegin(); it != callStack.rend(); ++it) {
      auto f = it->locals.find("this");
      if (f != it->locals.end()) { thisCell = f->second; break; }
    }

    if (thisCell) {
      Value thisV = thisCell->get();
      if (thisV.kind == ValueKind::Object) {
        auto fit = thisV.objectValue->fields.find(v->name);
        if (fit != thisV.objectValue->fields.end()) return fit->second;
      }
    }

    throw std::runtime_error("Undefined variable: " + v->name);
  }

  if (auto* f = dynamic_cast<FieldExpr*>(e)) {
    Value objV = evalExpr(f->object);
    if (objV.kind != ValueKind::Object) throw std::runtime_error("Field access on non-object");
    auto& fields = objV.objectValue->fields;
    auto it = fields.find(f->field);
    if (it == fields.end()) throw std::runtime_error("Unknown field: " + f->field);
    return it->second;
  }

  throw std::runtime_error("Assignment target must be lvalue");
}


static std::string normalizeType(std::string t) {
  // entfernt alle '&' und Spaces (einfach, reicht fuer dein Projekt)
  t.erase(std::remove(t.begin(), t.end(), '&'), t.end());
  t.erase(std::remove_if(t.begin(), t.end(),
    [](unsigned char ch){ return std::isspace(ch); }), t.end());
  return t;
}

static bool isBuiltinType(const std::string& t) {
  return t == "int" || t == "bool" || t == "char" || t == "string" || t == "void";
}

bool Interpreter::isBaseOf(const std::string& base, const std::string& derived) {
  std::string cur = derived;
  while (!cur.empty()) {
    if (cur == base) return true;
    auto it = classes.find(cur);
    if (it == classes.end()) break;
    cur = it->second->baseName;
  }
  return false;
}

// sammelt Felder der Klasse + ihrer Basen (Base zuerst oder egal, Hauptsache eindeutig)
std::vector<VarDecl*> Interpreter::collectFields(const std::string& clsName) {
  std::vector<VarDecl*> out;
  auto it = classes.find(clsName);
  if (it == classes.end()) return out;

  ClassDecl* c = it->second;
  if (!c->baseName.empty()) {
    auto baseFields = collectFields(c->baseName);
    out.insert(out.end(), baseFields.begin(), baseFields.end());
  }

  for (auto* m : c->members) {
    if (auto* f = dynamic_cast<VarDecl*>(m)) out.push_back(f);
  }
  return out;
}

FunctionDecl* Interpreter::findCtor(const std::string& classNameRaw, size_t argc) {
  const std::string className = normalizeType(classNameRaw);

  auto cit = classes.find(className);
  if (cit == classes.end()) return nullptr;

  for (auto* m : cit->second->members) {
    auto* fn = dynamic_cast<FunctionDecl*>(m);
    if (!fn) continue;

    if (normalizeType(fn->ownerClass) == className &&
        fn->name == className &&
        fn->params.size() == argc) {
      return fn;
        }
  }
  return nullptr;
}

