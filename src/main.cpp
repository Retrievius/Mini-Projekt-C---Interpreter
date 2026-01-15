#include <cassert>
#include <iostream>
#include <string>

#include "external/antlr4-runtime/runtime/src/antlr4-runtime.h"
#include "gen/cppLexer.h"
#include "gen/cppParser.h"
#include "ast/AST.h"
#include "ast/ASTBuilder.h"
#include "interpreter/Interpreter.h"

int main() {
    // 1. Code, den wir parsen wollen
    std::string code = "1 + 2;"; // Beispielcode, kann erweitert werden

    // 2. ANTLR InputStream, Lexer, TokenStream und Parser erstellen
    antlr4::ANTLRInputStream input(code);
    cppLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    cppParser parser(&tokens);

    // 3. Parsebaum erzeugen
    cppParser::StartContext* tree = parser.start();

    // 4. ASTBuilder erzeugen und AST bauen
    ASTBuilder builder;
    Program* prog = builder.build(tree);

    // 5. Interpreter ausführen
    Interpreter interp;
    interp.run(prog);

    std::cout << "Parsing and interpretation completed successfully!\n";

    return 0;
}
