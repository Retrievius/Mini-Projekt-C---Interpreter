#include <cassert>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "external/antlr4-runtime/runtime/src/antlr4-runtime.h"
#include "gen/cppLexer.h"
#include "gen/cppParser.h"
#include "ast/AST.h"
#include "ast/ASTBuilder.h"
#include "interpreter/Interpreter.h"
#include "ast/PrettyPrinter.h"
//#include "semantic/SemanticChecker.h"

// Datei einlesen
std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Cannot open file: " + path);

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    try {
        // Datei einlesen
        //std::string code = readFile("../tests/pos/GOLD01_basics.cpp");
        //std::string code = readFile("../tests/pos/GOLD02_ref_params.cpp");
        std::string code = readFile("../tests/pos/GOLD03_classes_dispatch.cpp");
        //std::string code = readFile("../tests/pos/GOLD04_slicing.cpp");
        //std::string code = readFile("../tests/pos/GOLD05_virtual_override.cpp");
        //std::string code = readFile("../tests/pos/GOLD06_constructors_basic.cpp");
        //std::string code = readFile("../tests/pos/GOLD07_constructors_inheritance.cpp");

        // ANTLR InputStream, Lexer, TokenStream, Parser
        antlr4::ANTLRInputStream input(code);
        cppLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        cppParser parser(&tokens);

        cppParser::StartContext* tree = parser.start();

        // AST bauen
        ASTBuilder builder;
        Program* prog = builder.build(tree);

        // AST pretty print
        std::cout << "----- AST -----\n";
        ASTPrinter printer;

        for (auto* stmt : prog->functions)
            stmt->accept(&printer);

        for (auto* stmt : prog->classes)
            stmt->accept(&printer);

        for (auto* stmt : prog->statements)
            stmt->accept(&printer);

        std::cout << "---------------\n";

        /*
        try {
            SemanticChecker sem;
            sem.checkProgram(prog);
        } catch (std::exception& e) {
            std::cerr << e.what() << "\n";
            return 1;
        }
        */

        // Interpreter ausführen
        std::cout << "----- Interpreter Output -----\n";
        Interpreter interp;
        interp.run(prog);
        std::cout << "-----------------------------\n";
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
