Person B — SemanticChecker

Person ist:

Verantwortlich für:

    Type-System

    Symboltabelle

    Semantik-Prüfung

TODO:

    Type.h

        - Enum Type

    SymbolTable.h

        - Scope Stack

        - pushScope()

        - popScope()

        - declareVar()

        - lookupVar()

        - declareFunction()

        - lookupFunction()

    SemanticChecker.h / cpp

        - visit(IntLiteral) → Type::Int

        - visit(BinaryExpr)

            -> Typprüfung

            -> Operator-kompatibilität

        - visit(VarDecl)

        - visit(AssignExpr)

        - visit(CallExpr)

        - visit(FunctionDecl)

        - visit(ReturnStmt)

        - visit(IfStmt)

        - visit(WhileStmt)

        - Return-Path-Check