#include "ASTBuilder.h"
#include "ast/AST.h"
#include <stdexcept>

using namespace cppParser;

    for (auto* child : ctx->children) {

        // Statement?
        if (auto* stmtCtx = dynamic_cast<cppParser::StmtContext*>(child)) {
            prog->statements.push_back(visitStmt(stmtCtx));
        }

        // Top-Level Decl?
        else if (auto* declCtx = dynamic_cast<cppParser::TopLevelDeclContext*>(child)) {

            if (declCtx->fnDecl()) {
                prog->functions.push_back(visitFnDecl(declCtx->fnDecl()));
            }
            else if (declCtx->classDecl()) {
                prog->classes.push_back(visitClassDecl(declCtx->classDecl()));
            }
            else {
                throw std::runtime_error("Unknown top-level declaration");
            }
        }
    }

    return prog;
}


// Statements
Stmt* ASTBuilder::visitStmt(cppParser::StmtContext* ctx) {
    if (ctx->vardecl()) {
        std::string type = ctx->vardecl()->type()->getText();
        std::string name = ctx->vardecl()->ID()->getText();
        auto* expr = ctx->vardecl()->expr() ? visitExpr(ctx->vardecl()->expr()) : nullptr;

        auto* decl = new VarDecl(type, name, expr);
        decl->isRef = (ctx->vardecl()->AMP() != nullptr);
        return decl;

    } else if (ctx->assign()) {
        Expr* target = visitPostfixExpr(ctx->assign()->postfixExpr()); // VarExpr oder FieldExpr
        Expr* rhs    = visitExpr(ctx->assign()->expr());
        return new AssignExpr(target, rhs);

    } else if (ctx->exprStmt()) {
        auto* expr = visitExpr(ctx->exprStmt()->expr());
        return new ExprStmt(expr);

    } else if (ctx->block()) {
        BlockStmt* block = new BlockStmt();
        for (auto* s : ctx->block()->stmt())
            block->statements.push_back(visitStmt(s));
        return block;

    } else if (ctx->ifStmt()) {
        auto* s = new IfStmt();
        s->condition = visitExpr(ctx->ifStmt()->expr());

// ================= Statements =================

Stmt* ASTBuilder::visitStmt(StmtContext* ctx) {

    if (ctx->vardecl()) {
        auto* decl = ctx->vardecl();
        std::string name = decl->ID()->getText();
        Expr* init = decl->expr() ? visitExpr(decl->expr()) : nullptr;

        return new VarDecl(name, init);
    }

    if (ctx->assign()) {
        auto* as = ctx->assign();
        std::string name = as->postfixExpr()->getText();
        Expr* value = visitExpr(as->expr());

        return new AssignExpr(name, value);
    }

    if (ctx->exprStmt()) {
        return new ExprStmt(visitExpr(ctx->exprStmt()->expr()));
    }

    if (ctx->block()) {
        auto* b = new BlockStmt();
        for (auto* s : ctx->block()->stmt())
            b->statements.push_back(visitStmt(s));
        return b;
    }

    if (ctx->ifStmt()) {
        auto* s = new IfStmt();
        s->condition = visitExpr(ctx->ifStmt()->expr());
        s->thenBranch = dynamic_cast<BlockStmt*>(visitStmt(ctx->ifStmt()->stmt(0)));

        if (ctx->ifStmt()->stmt().size() > 1)
            s->elseBranch = dynamic_cast<BlockStmt*>(visitStmt(ctx->ifStmt()->stmt(1)));

        return s;
    }

    if (ctx->whileStmt()) {
        auto* s = new WhileStmt();
        s->condition = visitExpr(ctx->whileStmt()->expr());
        s->body = dynamic_cast<BlockStmt*>(visitStmt(ctx->whileStmt()->stmt()));
        return s;
    }

    if (ctx->returnStmt()) {
        auto* r = new ReturnStmt();
        if (ctx->returnStmt()->expr())
            r->expr = visitExpr(ctx->returnStmt()->expr());
        return r;
    }

    throw std::runtime_error("Unknown statement");
}


Expr* ASTBuilder::visitUnaryExpr(cppParser::UnaryExprContext* ctx) {
    if (ctx->postfixExpr()) {
        return visitPostfixExpr(ctx->postfixExpr());
    }
    else if (ctx->unaryExpr()) {
        Expr* inner = visitUnaryExpr(ctx->unaryExpr());
        auto opToken = ctx->children[0]->getText();

        if (opToken == "-")
            return new UnaryExpr(UnaryExpr::UnaryOp::Neg, inner);
        if (opToken == "!")
            return new UnaryExpr(UnaryExpr::UnaryOp::Not, inner);

        throw std::runtime_error("Unknown unary operator");
    }

    throw std::runtime_error("Unknown unary expression");
}


Expr* ASTBuilder::visitPrimaryExpr(cppParser::PrimaryExprContext* ctx) {
    if (ctx->literal()) {
        auto* lit = ctx->literal();

        if (lit->NUMBER())
            return new IntLiteral(std::stoi(lit->NUMBER()->getText()));

        if (lit->getText() == "true")
            return new BoolLiteral(true);

        if (lit->getText() == "false")
            return new BoolLiteral(false);

        if (lit->CHAR()) {
            std::string t = lit->CHAR()->getText(); // 'A'
            char c = t[1];
            return new CharLiteral(c);
        }

        if (lit->STRING()) {
            std::string t = lit->STRING()->getText(); // "foo"
            std::string s = t.substr(1, t.size() - 2);
            return new StringLiteral(s);
        }
    }
    else if (ctx->ID()) {
        return new VarExpr(ctx->ID()->getText());
    }
    else if (ctx->expr()) {
        return visitExpr(ctx->expr());
    }

    throw std::runtime_error("Unknown primary expression");
}


Expr* ASTBuilder::visitLogicalOrExpr(cppParser::LogicalOrExprContext* ctx) {
    Expr* left = visitLogicalAndExpr(ctx->logicalAndExpr(0));

    for (size_t i = 1; i < ctx->logicalAndExpr().size(); ++i) {
        Expr* right = visitLogicalAndExpr(ctx->logicalAndExpr(i));
        left = new BinaryExpr(BinaryExpr::BinaryOp::Or, left, right);
    }
    return left;
}

Expr* ASTBuilder::visitLogicalAndExpr(LogicalAndExprContext* ctx) {
    Expr* left = visitEqualityExpr(ctx->equalityExpr(0));

    for (size_t i = 1; i < ctx->equalityExpr().size(); ++i) {
        Expr* right = visitEqualityExpr(ctx->equalityExpr(i));
        left = new BinaryExpr(BinaryExpr::BinaryOp::And, left, right);
    }
    return left;
}

Expr* ASTBuilder::visitEqualityExpr(EqualityExprContext* ctx) {
    Expr* left = visitRelationalExpr(ctx->relationalExpr(0));

    for (size_t i = 1; i < ctx->relationalExpr().size(); ++i) {
        Expr* right = visitRelationalExpr(ctx->relationalExpr(i));
        std::string op = ctx->children[2 * i - 1]->getText();

        if (op == "==") left = new BinaryExpr(BinaryExpr::BinaryOp::Eq, left, right);
        else if (op == "!=") left = new BinaryExpr(BinaryExpr::BinaryOp::Neq, left, right);
        else throw std::runtime_error("Unknown equality operator");
    }
    return left;
}

Expr* ASTBuilder::visitRelationalExpr(RelationalExprContext* ctx) {
    Expr* left = visitAdditiveExpr(ctx->additiveExpr(0));

    for (size_t i = 1; i < ctx->additiveExpr().size(); ++i) {
        Expr* right = visitAdditiveExpr(ctx->additiveExpr(i));
        std::string op = ctx->children[2 * i - 1]->getText();

        if (op == "<") left = new BinaryExpr(BinaryExpr::BinaryOp::Lt, left, right);
        else if (op == "<=") left = new BinaryExpr(BinaryExpr::BinaryOp::Le, left, right);
        else if (op == ">") left = new BinaryExpr(BinaryExpr::BinaryOp::Gt, left, right);
        else if (op == ">=") left = new BinaryExpr(BinaryExpr::BinaryOp::Ge, left, right);
        else throw std::runtime_error("Unknown relational operator");
    }
    return left;
}

Expr* ASTBuilder::visitAdditiveExpr(AdditiveExprContext* ctx) {
    Expr* left = visitMultiplicativeExpr(ctx->multiplicativeExpr(0));

    for (size_t i = 1; i < ctx->multiplicativeExpr().size(); ++i) {
        Expr* right = visitMultiplicativeExpr(ctx->multiplicativeExpr(i));
        std::string op = ctx->children[2 * i - 1]->getText();

        BinaryExpr::BinaryOp bop = (op == "+") ? BinaryExpr::BinaryOp::Add : BinaryExpr::BinaryOp::Sub;
        left = new BinaryExpr(bop, left, right);
    }
    return left;
}

Expr* ASTBuilder::visitMultiplicativeExpr(MultiplicativeExprContext* ctx) {
    Expr* left = visitUnaryExpr(ctx->unaryExpr(0));

    for (size_t i = 1; i < ctx->unaryExpr().size(); ++i) {
        Expr* right = visitUnaryExpr(ctx->unaryExpr(i));
        std::string op = ctx->children[2 * i - 1]->getText();

        BinaryExpr::BinaryOp bop;
        if (op == "*") bop = BinaryExpr::BinaryOp::Mul;
        else if (op == "/") bop = BinaryExpr::BinaryOp::Div;
        else bop = BinaryExpr::BinaryOp::Mod;

        left = new BinaryExpr(bop, left, right);
    }
    return left;
}

Expr* ASTBuilder::visitPostfixExpr(cppParser::PostfixExprContext* ctx) {
    Expr* base = visitPrimaryExpr(ctx->primaryExpr());

    // wir laufen über die Suffixe in Reihenfolge:
    // primaryExpr (memberAccess | call)*
    for (size_t i = 1; i < ctx->children.size(); ++i) {
        auto* child = ctx->children[i];

        if (auto* mem = dynamic_cast<cppParser::MemberAccessContext*>(child)) {
            std::string field = mem->ID()->getText();
            base = new FieldExpr(base, field);
            continue;
        }

        if (auto* call = dynamic_cast<cppParser::CallContext*>(child)) {
            // Fall 1: base ist VarExpr => normaler Funktionsaufruf
            if (auto* var = dynamic_cast<VarExpr*>(base)) {
                auto* c = new CallExpr(var->name);
                if (call->args()) {
                    for (auto* a : call->args()->expr()) c->args.push_back(visitExpr(a));
                }
                base = c;
                continue;
            }

            // Fall 2: base ist FieldExpr => Methodenaufruf obj.m(...)
            if (auto* fe = dynamic_cast<FieldExpr*>(base)) {
                auto* mc = new MethodCallExpr(fe->object, fe->field);
                if (call->args()) {
                    for (auto* a : call->args()->expr()) mc->args.push_back(visitExpr(a));
                }
                base = mc;
                continue;
            }

            throw std::runtime_error("Unsupported call target");
        }
    }

    return base;
}


FunctionDecl* ASTBuilder::visitFnDecl(cppParser::FnDeclContext* ctx) {
    auto* fn = new FunctionDecl();

    fn->name = ctx->ID()->getText();

    // Parameter
    if (ctx->params()) {
        for (auto* p : ctx->params()->param()) {
            fn->params.push_back(visitParam(p));
        }
    }

    fn->body = visitBlock(ctx->block());

    fn->returnType = ctx->type()->getText();

    return fn;
}

Param* ASTBuilder::visitParam(cppParser::ParamContext* ctx) {
    auto* p = new Param();
    p->name = ctx->ID()->getText();
    p->type = ctx->type()->getText();
    // type : baseType ('&')?
    p->isRef = (ctx->AMP() != nullptr);
    return p;
}


BlockStmt* ASTBuilder::visitBlock(cppParser::BlockContext* ctx) {
    auto* block = new BlockStmt();

    for (auto* s : ctx->stmt()) {
        block->statements.push_back(visitStmt(s));
    }

    return block;
}

ClassDecl* ASTBuilder::visitClassDecl(cppParser::ClassDeclContext* ctx) {
    auto* cls = new ClassDecl();
    cls->name = ctx->ID(0)->getText();

    // optional ": public Base"
    if (ctx->ID().size() > 1) cls->baseName = ctx->ID(1)->getText();

    auto* body = ctx->classBody();

    // classMember*
    for (auto* m : body->classMember()) {

        if (m->fieldDecl()) {
            std::string t = m->fieldDecl()->type()->getText();
            std::string n = m->fieldDecl()->ID()->getText();
            cls->members.push_back(new VarDecl(t, n));
        }
        else if (m->methodDecl()) {
            auto* md = m->methodDecl();
            auto* fn = new FunctionDecl();
            fn->ownerClass = cls->name;
            fn->isVirtual = (md->getText().rfind("virtual", 0) == 0);
            fn->returnType = md->type()->getText();
            fn->name       = md->ID()->getText();

            if (md->params()) {
                for (auto* p : md->params()->param()) fn->params.push_back(visitParam(p));
            }
            fn->body = visitBlock(md->block());

            cls->members.push_back(fn);
        }
        else if (m->ctorDecl()) {
            auto* cd = m->ctorDecl();

            auto* fn = new FunctionDecl();
            fn->ownerClass = cls->name;
            fn->returnType = "void";     // ctors liefern nichts (in deinem Modell)
            fn->name       = cd->ID()->getText(); // = Klassenname
            fn->isVirtual  = false;      // ctor ist nicht virtual
            // optional: Flag fn->isConstructor = true; (falls du eins einführen willst)

            if (cd->params()) {
                for (auto* p : cd->params()->param()) fn->params.push_back(visitParam(p));
            }
            fn->body = visitBlock(cd->block());

            cls->members.push_back(fn);
        }
    }

    return cls;
}

