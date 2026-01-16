Person C — Interpreter

Person ist: Linus Martinschledde

Verantwortlich für:

    Value-System

    Environment

    Ausführung

TODO:

    Value.h

        - Int / Bool / Void

    Environment.h

        - Scope stack

        - define()

        - assign()

        - lookup()

    Interpreter.cpp

        - visit(IntLiteral)

        - visit(BinaryExpr)

        - visit(UnaryExpr)

        - visit(VarDecl)

        - visit(AssignExpr)

        - visit(IfStmt)

        - visit(WhileStmt)

        - visit(ReturnStmt)

        - visit(FunctionDecl)

        - visit(CallExpr)

        - Builtins:

            -> print_int

            -> print_bool


TODO main.cpp:

    File oder REPL lesen

    Lexer + Parser

    ASTBuilder

    SemanticChecker

    Interpreter

    Fehler sauber ausgeben