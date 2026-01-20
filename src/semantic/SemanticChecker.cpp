#include "SemanticChecker.h"

// --------------------
// program entry
// --------------------
void SemanticChecker::checkProgram(Program* p) {
    // 1) class table first (fields/methods/ctors)
    buildClassTable(p);

    // 2) declare builtins
    declareBuiltins();

    // 3) declare free functions (signatures) first so calls work
    for (auto* fn : p->functions) {
        fn->accept(this);
    }

    // 4) then check class decls (optional deeper checks)
    for (auto* c : p->classes) {
        c->accept(this);
    }

    // 5) then top-level statements
    for (auto* s : p->statements) {
        s->accept(this);
    }
}

// --------------------
// Type parsing
// --------------------
Type SemanticChecker::parseTypeString(const std::string& t, bool isRefFlag) {
    // minimal normalize: remove spaces
    std::string s;
    for (char c : t) if (c != ' ' && c != '\t' && c != '\n' && c != '\r') s.push_back(c);

    Type base;
    if (s == "int") base = Type::Int();
    else if (s == "bool") base = Type::Bool();
    else if (s == "char") base = Type::Char();
    else if (s == "string") base = Type::String();
    else if (s == "void") base = Type::Void();
    else base = Type::Class(s);

    if (isRefFlag) return Type::Ref(base);
    return base;
}

const SemanticChecker::ClassInfo* SemanticChecker::getClass(const std::string& name) const {
    auto it = classTable.find(name);
    if (it == classTable.end()) return nullptr;
    return &it->second;
}

Type SemanticChecker::lookupFieldType(const std::string& cls, const std::string& field) const {
    const ClassInfo* c = getClass(cls);
    while (c) {
        auto it = c->fields.find(field);
        if (it != c->fields.end()) return it->second;
        if (c->base.empty()) break;
        c = getClass(c->base);
    }
    throw std::runtime_error("Unknown field '" + field + "' in class '" + cls + "'");
}

const SemanticChecker::MethodSig* SemanticChecker::lookupMethod(
    const std::string& cls,
    const std::string& name,
    const std::vector<Type>& args,
    const std::vector<bool>& argIsLValue
) const {
    auto decay = [](Type t) -> Type { return t.isRef() ? t.refType() : t; };

    const ClassInfo* c = getClass(cls);
    while (c) {
        auto mit = c->methods.find(name);
        if (mit != c->methods.end()) {
            const MethodSig* match = nullptr;

            for (const auto& cand : mit->second) {
                if (cand.params.size() != args.size()) continue;

                bool ok = true;
                for (size_t i = 0; i < args.size(); ++i) {
                    Type p = cand.params[i];
                    Type a = args[i];

                    if (p.isRef()) {
                        // Ref-Param: Argument muss LValue sein + Basistyp matcht (decay)
                        if (!argIsLValue[i]) { ok = false; break; }
                        if (!p.refType().equals(decay(a))) { ok = false; break; }
                    } else {
                        // Value-Param: Basistyp matcht (decay)
                        if (!p.equals(decay(a))) { ok = false; break; }
                    }
                }

                if (ok) {
                    if (match)
                        throw std::runtime_error("Ambiguous method call: " + cls + "::" + name);
                    match = &cand;
                }
            }

            if (match) return match;
        }

        if (c->base.empty()) break;
        c = getClass(c->base);
    }

    return nullptr;
}

const SemanticChecker::MethodSig* SemanticChecker::lookupCtor(
    const std::string& cls, const std::vector<Type>& args) const
{
    const ClassInfo* c = getClass(cls);
    if (!c) return nullptr;

    const MethodSig* match = nullptr;
    for (const auto& cand : c->ctors) {
        if (cand.params.size() != args.size()) continue;
        bool ok = true;
        for (size_t i = 0; i < args.size(); ++i) {
            if (!cand.params[i].equals(args[i])) { ok = false; break; }
        }
        if (ok) {
            if (match) throw std::runtime_error("Ambiguous ctor call: " + cls);
            match = &cand;
        }
    }
    return match;
}

// --------------------
// build class table from AST
// --------------------
void SemanticChecker::buildClassTable(Program* p) {
    classTable.clear();

    // first pass: register class names + base
    for (auto* c : p->classes) {
        ClassInfo info;
        info.name = c->name;
        info.base = c->baseName;
        classTable[c->name] = info;
    }

    // second pass: fill members
    for (auto* c : p->classes) {
        auto& info = classTable[c->name];

        for (auto* m : c->members) {
            if (auto* f = dynamic_cast<VarDecl*>(m)) {
                Type ft = parseTypeString(f->type, f->isRef);
                info.fields[f->name] = ft;
            }
            else if (auto* fn = dynamic_cast<FunctionDecl*>(m)) {
                MethodSig sig;
                sig.name = fn->name;
                sig.ret  = parseTypeString(fn->returnType, false);
                sig.isVirtual = fn->isVirtual;
                sig.ownerClass = fn->ownerClass;

                for (auto* p : fn->params) {
                    sig.params.push_back(parseTypeString(p->type, p->isRef));
                }

                // ctor? name == class name
                if (fn->name == c->name) {
                    info.ctors.push_back(sig);
                } else {
                    info.methods[fn->name].push_back(sig);
                }
            }
        }
    }
}

void SemanticChecker::declareBuiltins() {
    // print_int(int) -> void
    symbols.declareFunction(FunctionSymbol{"print_int", {Type::Int()}, Type::Void()});
    symbols.declareFunction(FunctionSymbol{"print_bool",{Type::Bool()},Type::Void()});
    symbols.declareFunction(FunctionSymbol{"print_char",{Type::Char()},Type::Void()});
    symbols.declareFunction(FunctionSymbol{"print_string",{Type::String()},Type::Void()});
}

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

void SemanticChecker::visit(CharLiteral* lit) {
    (void)lit;
    lastType = Type::Char();
    lastIsLValue = false;
}

void SemanticChecker::visit(StringLiteral* lit) {
    (void)lit;
    lastType = Type::String();
    lastIsLValue = false;
}

void SemanticChecker::visit(VarExpr* var) {
    auto sym = symbols.lookupVar(var->name);
    lastType = sym.type;
    lastIsLValue = true;
}

void SemanticChecker::visit(FieldExpr* fe) {
    auto decay = [](Type t) -> Type { return t.isRef() ? t.refType() : t; };

    Type objT0 = evalExpr(fe->object);
    Type objT  = decay(objT0);

    require(objT.kind == TypeKind::Class, "Field access on non-class type: " + objT0.toString());

    Type ft = lookupFieldType(objT.className, fe->field);
    lastType = ft;
    lastIsLValue = true;
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
    Type l0 = evalExpr(e->lhs);
    Type r0 = evalExpr(e->rhs);

    Type l = l0.isRef() ? l0.refType() : l0;
    Type r = r0.isRef() ? r0.refType() : r0;

    lastIsLValue = false;

    require(l.equals(r), "Binary operands must have same type (" + l.toString() + " vs " + r.toString() + ")");

    switch (e->op) {
        case BinaryExpr::BinaryOp::Add:
        case BinaryExpr::BinaryOp::Sub:
        case BinaryExpr::BinaryOp::Mul:
        case BinaryExpr::BinaryOp::Div:
        case BinaryExpr::BinaryOp::Mod:
            require(l.equals(Type::Int()), "Arithmetic operators require int");
            lastType = Type::Int();
            return;

        case BinaryExpr::BinaryOp::Lt:
        case BinaryExpr::BinaryOp::Le:
        case BinaryExpr::BinaryOp::Gt:
        case BinaryExpr::BinaryOp::Ge:
            require(l.equals(Type::Int()), "<,<=,>,>= require int");
            lastType = Type::Bool();
            return;

        case BinaryExpr::BinaryOp::And:
        case BinaryExpr::BinaryOp::Or:
            require(l.equals(Type::Bool()), "&&/|| require bool");
            lastType = Type::Bool();
            return;
    }

    error("Unsupported binary operator");
}

void SemanticChecker::visit(AssignExpr* assign) {
    // target must be lvalue
    assign->target->accept(this);
    require(lastIsLValue, "Assignment target must be LValue");
    Type lhsT = lastType;

    Type rhsT = evalExpr(assign->expr);

    require(lhsT.equals(rhsT), "Assignment type mismatch (" + lhsT.toString() + " vs " + rhsT.toString() + ")");

    lastType = rhsT;
    lastIsLValue = false;
}

void SemanticChecker::visit(CallExpr* call) {
    auto decay = [](Type t) -> Type { return t.isRef() ? t.refType() : t; };
    // eval args first
    std::vector<Type> argTypes;
    std::vector<bool> argIsLValue;
    argTypes.reserve(call->args.size());
    argIsLValue.reserve(call->args.size());

    for (auto* a : call->args) {
        a->accept(this);
        argTypes.push_back(lastType);
        argIsLValue.push_back(lastIsLValue);
    }

    // constructor call? (CallExpr("Point") => class)
    if (getClass(call->functionName)) {
        const auto* ctor = lookupCtor(call->functionName, argTypes);
        // if no ctor found: allow only if zero-args exists implicitly? in your runtime you *need* a ctor body only if defined.
        // We'll be permissive: if no matching ctor found, allow only if args empty.
        if (!ctor) {
            require(argTypes.empty(), "No matching constructor for class: " + call->functionName);
        }
        lastType = Type::Class(call->functionName);
        lastIsLValue = false;
        return;
    }

    // builtin + free functions
    FunctionSymbol fn = symbols.lookupFunction(call->functionName, argTypes);

    // reference parameters: arg must be LValue
    for (size_t i = 0; i < fn.paramTypes.size(); ++i) {
        if (fn.paramTypes[i].isRef()) {
            require(argIsLValue[i], "Reference argument must be LValue at position " + std::to_string(i));
            require(fn.paramTypes[i].refType().equals(decay(argTypes[i])),
        "Reference parameter type mismatch");
        }
    }

    lastType = fn.returnType;
    lastIsLValue = false;
}

void SemanticChecker::visit(MethodCallExpr* mc) {
    auto decay = [](Type t) -> Type {
        return t.isRef() ? t.refType() : t;
    };

    // Objekt-Typ auswerten: kann Class oder Class& sein
    Type objT0 = evalExpr(mc->object);
    Type objT  = decay(objT0);

    require(objT.kind == TypeKind::Class,
            "Method call on non-class type: " + objT0.toString());

    // args sammeln (RAW + lvalue flags)
    std::vector<Type> argTypes;
    std::vector<bool> argIsLValue;
    argTypes.reserve(mc->args.size());
    argIsLValue.reserve(mc->args.size());

    for (auto* a : mc->args) {
        a->accept(this);
        argTypes.push_back(lastType);       // kann Ref sein
        argIsLValue.push_back(lastIsLValue);
    }

    // Method overload selection: NICHT über exakte argTypes matchen,
    // sondern mit ref-decay + lvalue-Regeln (wie bei functions)
    const MethodSig* m = lookupMethod(objT.className, mc->method, argTypes, argIsLValue);
    require(m != nullptr,
            "Unknown method or signature: " + objT.className + "::" + mc->method);

    lastType = m->ret;
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
    // declared type from AST
    Type varT = parseTypeString(decl->type, decl->isRef);

    // if class type, ensure it exists
    if (varT.kind == TypeKind::Class) {
        require(getClass(varT.className) != nullptr, "Unknown class type: " + varT.className);
    }
    if (varT.kind == TypeKind::Ref) {
        // references to classes also allowed
        if (varT.refType().kind == TypeKind::Class) {
            require(getClass(varT.refType().className) != nullptr, "Unknown class type: " + varT.refType().className);
        }
    }

    if (decl->initExpr) {
        decl->initExpr->accept(this);
        Type initT = lastType;

        if (decl->isRef) {
            // ref init must be LValue and base types must match
            require(lastIsLValue, "Reference must bind to LValue");
            require(varT.refType().equals(initT), "Reference init type mismatch (" + varT.toString() + " vs " + initT.toString() + ")");
        } else {
            // allow slicing? semantic rule: Base b = Der d; is allowed if base is base-of derived
            if (varT.kind == TypeKind::Class && initT.kind == TypeKind::Class) {
                if (varT.className != initT.className) {
                    // allow if base chain contains varT
                    const ClassInfo* c = getClass(initT.className);
                    bool ok = false;
                    while (c) {
                        if (c->name == varT.className) { ok = true; break; }
                        if (c->base.empty()) break;
                        c = getClass(c->base);
                    }
                    require(ok, "Cannot init " + varT.className + " from " + initT.className);
                }
            } else {
                require(varT.equals(initT), "VarDecl init type mismatch (" + varT.toString() + " vs " + initT.toString() + ")");
            }
        }
    }

    // declare variable in current scope:
    symbols.declareVar(decl->name, varT);

    lastType = Type::Void();
    lastIsLValue = false;
}

void SemanticChecker::visit(BlockStmt* block) {
    symbols.pushScope();

    bool blockAlwaysReturns = false;
    for (auto* s : block->statements) {
        s->accept(this);
        if (currentAlwaysReturns) {
            blockAlwaysReturns = true;
        }
    }

    symbols.popScope();
    (void)blockAlwaysReturns;

    lastType = Type::Void();
    lastIsLValue = false;
}

void SemanticChecker::visit(IfStmt* stmt) {
    Type condT = evalExpr(stmt->condition);
    require(condT.isBoolContextConvertible(), "if condition not convertible to bool: " + condT.toString());

    bool before = currentAlwaysReturns;

    currentAlwaysReturns = false;
    stmt->thenBranch->accept(this);
    bool thenReturns = currentAlwaysReturns;

    bool elseReturns = false;
    if (stmt->elseBranch) {
        currentAlwaysReturns = false;
        stmt->elseBranch->accept(this);
        elseReturns = currentAlwaysReturns;
    }

    currentAlwaysReturns = before || (stmt->elseBranch && thenReturns && elseReturns);

    lastType = Type::Void();
    lastIsLValue = false;
}

void SemanticChecker::visit(WhileStmt* stmt) {
    Type condT = evalExpr(stmt->condition);
    require(condT.isBoolContextConvertible(), "while condition not convertible to bool: " + condT.toString());

    bool before = currentAlwaysReturns;
    stmt->body->accept(this);
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
// Top level
// --------------------
void SemanticChecker::visit(FunctionDecl* decl) {
    // only free functions in symbol table (methods are in classTable)
    if (!decl->ownerClass.empty()) {
        lastType = Type::Void();
        lastIsLValue = false;
        return;
    }

    FunctionSymbol fn;
    fn.name = decl->name;
    fn.returnType = parseTypeString(decl->returnType, false);

    for (auto* p : decl->params) {
        fn.paramTypes.push_back(parseTypeString(p->type, p->isRef));
    }

    // declare signature (overloads ok)
    symbols.declareFunction(fn);

    // now check body
    bool prevIn = inFunction;
    Type prevRet = currentReturnType;
    bool prevAlways = currentAlwaysReturns;

    inFunction = true;
    currentReturnType = fn.returnType;
    currentAlwaysReturns = false;

    symbols.pushScope();

    // params in scope
    for (auto* p : decl->params) {
        symbols.declareVar(p->name, parseTypeString(p->type, p->isRef));
    }

    decl->body->accept(this);

    symbols.popScope();

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
    // minimal: ensure base exists if mentioned
    if (!decl->baseName.empty()) {
        require(getClass(decl->baseName) != nullptr, "Unknown base class: " + decl->baseName);
    }
    lastType = Type::Void();
    lastIsLValue = false;
}
