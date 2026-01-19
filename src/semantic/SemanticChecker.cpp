#include "SemanticChecker.h"

// --------------------
// Expressions
// --------------------

void SemanticChecker::visit(IntLiteral* lit) {
    (void)lit;
    lastType = Type::Int();
    lastIsLValue = false;
}

void SemanticChecker::visit(BoolLiteral* lit) {
    (void)lit;
    lastType = Type::Bool();
    lastIsLValue = false;
}

void SemanticChecker::visit(VarExpr* var) {
    // define-before-use
    auto sym = symbols.lookupVar(var->name);
    lastType = sym.type;
    lastIsLValue = true; // Variable ist LValue
}

void SemanticChecker::visit(UnaryExpr* e) {
    Type t = evalExpr(e->expr);
    lastIsLValue = false;

    switch (e->op) {
        case UnaryExpr::UnaryOp::Neg:
            require(t.equals(Type::Int()), "Unary '-' requires int");
            lastType = Type::Int();
            return;

        case UnaryExpr::UnaryOp::Not:
            require(t.equals(Type::Bool()), "Unary '!' requires bool");
            lastType = Type::Bool();
            return;
    }

    error("Unsupported unary operator");
}

void SemanticChecker::visit(BinaryExpr* e) {
    Type l = evalExpr(e->lhs);
    Type r = evalExpr(e->rhs);
    lastIsLValue = false;

    // Regel: bei binären Operatoren müssen beide Seiten gleichen Typ haben
    require(l.equals(r), "Binary operands must have same type (" + l.toString() + " vs " + r.toString() + ")");

    switch (e->op) {
        // Arithmetik: nur int
        case BinaryExpr::BinaryOp::Add:
        case BinaryExpr::BinaryOp::Sub:
        case BinaryExpr::BinaryOp::Mul:
        case BinaryExpr::BinaryOp::Div:
        case BinaryExpr::BinaryOp::Mod:
            require(l.equals(Type::Int()), "Arithmetic operators require int");
            lastType = Type::Int();
            return;

        // Vergleiche
        case BinaryExpr::BinaryOp::Eq:
        case BinaryExpr::BinaryOp::Neq:
            // aktuell: int/bool sind in eurem AST sicher vorhanden
            require(l.equals(Type::Int()) || l.equals(Type::Bool()),
                    "==/!= allowed for int/bool in current implementation");
            lastType = Type::Bool();
            return;

        case BinaryExpr::BinaryOp::Lt:
        case BinaryExpr::BinaryOp::Le:
        case BinaryExpr::BinaryOp::Gt:
        case BinaryExpr::BinaryOp::Ge:
            require(l.equals(Type::Int()), "<,<=,>,>= require int");
            lastType = Type::Bool();
            return;

        // Logik
        case BinaryExpr::BinaryOp::And:
        case BinaryExpr::BinaryOp::Or:
            require(l.equals(Type::Bool()), "&&/|| require bool");
            lastType = Type::Bool();
            return;
    }

    error("Unsupported binary operator");
}

void SemanticChecker::visit(AssignExpr* assign) {
    // ACHTUNG: euer aktuelles AST hat AssignExpr(name, expr) (kein lhs Expr),
    // daher prüfen wir: Variable muss existieren + Typ muss passen.
    auto lhs = symbols.lookupVar(assign->name);
    Type rhsT = evalExpr(assign->expr);

    require(lhs.type.equals(rhsT), "Assignment type mismatch (" + lhs.type.toString() + " vs " + rhsT.toString() + ")");

    // Zuweisung ist Ausdruck: Typ = RHS
    lastType = rhsT;
    lastIsLValue = false;
}

void SemanticChecker::visit(CallExpr* call) {
    // In eurem Interpreter sind print_int / print_bool builtins:
    // Hier machen wir minimale Semantik:
    // - Funktionsname existiert (falls registriert)
    // - Argumente typprüfen
    // - Für builtins prüfen wir die erwarteten Typen

    // args typprüfen
    std::vector<Type> argTypes;
    std::vector<bool> argIsLValue;
    argTypes.reserve(call->args.size());
    argIsLValue.reserve(call->args.size());

    for (auto* a : call->args) {
        a->accept(this);
        argTypes.push_back(lastType);
        argIsLValue.push_back(lastIsLValue);
    }

    // builtins (wie Spezifikation / Interpreter)
    if (call->functionName == "print_int") {
        require(argTypes.size() == 1, "print_int expects 1 argument");
        require(argTypes[0].equals(Type::Int()), "print_int expects int");
        lastType = Type::Void();
        lastIsLValue = false;
        return;
    }
    if (call->functionName == "print_bool") {
        require(argTypes.size() == 1, "print_bool expects 1 argument");
        require(argTypes[0].equals(Type::Bool()), "print_bool expects bool");
        lastType = Type::Void();
        lastIsLValue = false;
        return;
    }

    // normale Funktionen (wenn in SymbolTable registriert)
    FunctionSymbol fn = symbols.lookupFunction(call->functionName, argTypes);

    // Referenzparameter: Argument muss LValue
    for (size_t i = 0; i < fn.paramTypes.size(); ++i) {
        if (fn.paramTypes[i].isRef()) {
            require(argIsLValue[i], "Reference argument must be LValue at position " + std::to_string(i));
            require(fn.paramTypes[i].refType().equals(argTypes[i]),
                    "Reference parameter type mismatch");
        }
    }

    lastType = fn.returnType;
    lastIsLValue = false;
}

// --------------------
// Statements
// --------------------

void SemanticChecker::visit(ExprStmt* stmt) {
    evalExpr(stmt->expr);
    lastType = Type::Void();
    lastIsLValue = false;
}

void SemanticChecker::visit(VarDecl* decl) {
    // Interpreter nutzt: decl->name, decl->initExpr
    // Typen sind aktuell nicht im ASTBuilder gesetzt -> wir nehmen minimal:
    // - ohne init: int (default wie Interpreter)
    // - mit init: Typ = Typ(init)
    Type t = Type::Int(); // default

    if (decl->initExpr) {
        Type initT = evalExpr(decl->initExpr);
        t = initT;
    }

    symbols.declareVar(decl->name, t);

    lastType = Type::Void();
    lastIsLValue = false;
}

void SemanticChecker::visit(BlockStmt* block) {
    symbols.pushScope();

    bool blockAlwaysReturns = false;

    for (auto* s : block->statements) {
        s->accept(this);

        // falls schon garantiert returnt, könnten weitere stmts "dead code" sein (optional)
        if (currentAlwaysReturns) {
            blockAlwaysReturns = true;
            // wir laufen trotzdem weiter, damit mehr Fehler gefunden werden können
        }
    }

    symbols.popScope();

    // currentAlwaysReturns bleibt wie es ist (für Return-Path-Check im Funktionskontext)
    (void)blockAlwaysReturns;

    lastType = Type::Void();
    lastIsLValue = false;
}

void SemanticChecker::visit(IfStmt* stmt) {
    Type condT = evalExpr(stmt->condition);
    require(condT.isBoolContextConvertible(), "if condition not convertible to bool: " + condT.toString());

    bool before = currentAlwaysReturns;

    // then
    currentAlwaysReturns = false;
    stmt->thenBranch->accept(this);
    bool thenReturns = currentAlwaysReturns;

    // else
    bool elseReturns = false;
    if (stmt->elseBranch) {
        currentAlwaysReturns = false;
        stmt->elseBranch->accept(this);
        elseReturns = currentAlwaysReturns;
    }

    // guaranteed return only if else exists and both return
    currentAlwaysReturns = before || (stmt->elseBranch && thenReturns && elseReturns);

    lastType = Type::Void();
    lastIsLValue = false;
}

void SemanticChecker::visit(WhileStmt* stmt) {
    Type condT = evalExpr(stmt->condition);
    require(condT.isBoolContextConvertible(), "while condition not convertible to bool: " + condT.toString());

    bool before = currentAlwaysReturns;

    stmt->body->accept(this);

    // konservativ: while garantiert keinen return
    currentAlwaysReturns = before;

    lastType = Type::Void();
    lastIsLValue = false;
}

void SemanticChecker::visit(ReturnStmt* stmt) {
    require(inFunction, "return outside of function");

    if (!stmt->expr) {
        require(currentReturnType.equals(Type::Void()),
                "Missing return value, expected " + currentReturnType.toString());
    } else {
        require(!currentReturnType.equals(Type::Void()),
                "Returning a value from void function");
        Type rt = evalExpr(stmt->expr);
        require(currentReturnType.equals(rt),
                "Return type mismatch (" + currentReturnType.toString() + " vs " + rt.toString() + ")");
    }

    currentAlwaysReturns = true;

    lastType = Type::Void();
    lastIsLValue = false;
}

// --------------------
// Top-Level
// --------------------

void SemanticChecker::visit(FunctionDecl* decl) {
    // Eure ASTBuilder baut Functions noch nicht vollständig,
    // aber wir implementieren Semantik + Return-Path-Check.

    // Minimal: ohne Typinfos -> void return, params als int
    // Wenn ihr in AST.h Typen ergänzt, kann man das hier erweitern.
    FunctionSymbol fn;
    fn.name = decl->name;
    fn.returnType = Type::Void();

    // Params: im Interpreter: func->params[i]->name existiert
    // Typen fehlen -> wir setzen int
    for (auto* p : decl->params) {
        fn.paramTypes.push_back(Type::Int());
        (void)p;
    }

    symbols.declareFunction(fn);

    // Function body check
    bool prevIn = inFunction;
    Type prevRet = currentReturnType;
    bool prevAlways = currentAlwaysReturns;

    inFunction = true;
    currentReturnType = fn.returnType;
    currentAlwaysReturns = false;

    symbols.pushScope();

    // Params ins Scope
    for (auto* p : decl->params) {
        symbols.declareVar(p->name, Type::Int());
    }

    decl->body->accept(this);

    symbols.popScope();

    // Return-Path-Check für nicht-void (hier aktuell void)
    if (!currentReturnType.equals(Type::Void())) {
        require(currentAlwaysReturns, "Not all paths return a value in function: " + decl->name);
    }

    inFunction = prevIn;
    currentReturnType = prevRet;
    currentAlwaysReturns = prevAlways;

    lastType = Type::Void();
    lastIsLValue = false;
}

void SemanticChecker::visit(ClassDecl* decl) {
    // Klassen-Semantik kommt später (Felder/Methoden/Vererbung/virtual)
    (void)decl;
    lastType = Type::Void();
    lastIsLValue = false;
}
