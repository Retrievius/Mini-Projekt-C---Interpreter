#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "external/antlr4-runtime/runtime/src/antlr4-runtime.h"
#include "gen/cppLexer.h"
#include "gen/cppParser.h"

#include "ast/AST.h"
#include "ast/ASTBuilder.h"
#include "ast/PrettyPrinter.h"
#include "interpreter/Interpreter.h"
//#include "semantic/SemanticChecker.h"

static std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Cannot open file: " + path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// ErrorListener, um Syntaxfehler zu sammeln (für REPL "incomplete input")
struct CollectingErrorListener : antlr4::BaseErrorListener {
    std::vector<std::string> errors;
    void syntaxError(antlr4::Recognizer*,
                     antlr4::Token*,
                     size_t line, size_t charPos,
                     const std::string& msg,
                     std::exception_ptr) override {
        std::ostringstream os;
        os << "line " << line << ":" << charPos << " " << msg;
        errors.push_back(os.str());
    }
};

static Program* parseProgram(const std::string& code, std::vector<std::string>& parseErrors) {
    antlr4::ANTLRInputStream input(code);
    cppLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    cppParser parser(&tokens);

    CollectingErrorListener err;
    lexer.removeErrorListeners();
    parser.removeErrorListeners();
    lexer.addErrorListener(&err);
    parser.addErrorListener(&err);

    cppParser::StartContext* tree = parser.start();

    parseErrors = err.errors;
    if (!parseErrors.empty()) return nullptr;

    ASTBuilder builder;
    return builder.build(tree);
}

static bool isIncomplete(const std::vector<std::string>& errs) {
    for (auto& e : errs) {
        if (e.find("<EOF>") != std::string::npos) return true;
    }
    return false;
}

int main(int argc, char** argv) {
    try {
        bool repl = false;
        std::string filePath;

        // CLI: Mini_Projekt_C___Interpreter.exe [--repl] <file.cpp>
        for (int i = 1; i < argc; ++i) {
            std::string a = argv[i];
            if (a == "--repl") repl = true;
            else filePath = a;
        }

        Interpreter interp;

        // ===== Init-Datei (optional) =====
        if (!filePath.empty()) {
            std::string code = readFile(filePath);

            std::vector<std::string> perr;
            Program* prog = parseProgram(code, perr);
            if (!prog) {
                for (auto& e : perr) std::cerr << e << "\n";
                return 1;
            }

            // optional AST dump
            // std::cout << "----- AST -----\n";
            // ASTPrinter printer;
            // for (auto* f : prog->functions) f->accept(&printer);
            // for (auto* c : prog->classes) c->accept(&printer);
            // for (auto* s : prog->statements) s->accept(&printer);
            // std::cout << "---------------\n";

            // Semantik optional
            /*
            try {
                SemanticChecker sem;
                sem.checkProgram(prog);
            } catch (std::exception& e) {
                std::cerr << e.what() << "\n";
                return 1;
            }
            */

            // ausführen (führt main im Session-Scope aus, lässt Session offen)
            interp.run(prog);
        } else {
            // keine Datei: trotzdem Session anlegen, damit REPL Variablen halten kann
            interp.ensureSession();
        }

        // ===== REPL =====
        if (!repl) return 0;

        std::cout << "REPL started. Exit with :q or :exit\n";

        std::string buffer;
        bool cont = false;

        while (true) {
            std::cout << (cont ? "... " : ">>> ");
            std::string line;
            if (!std::getline(std::cin, line)) break;

            if (!cont && (line == ":q" || line == ":exit" || line == "exit")) break;

            buffer += line;
            buffer += "\n";

            std::vector<std::string> perr;
            Program* chunk = parseProgram(buffer, perr);
            if (!chunk) {
                if (isIncomplete(perr)) {
                    cont = true;
                    continue;
                }
                for (auto& e : perr) std::cerr << e << "\n";
                buffer.clear();
                cont = false;
                continue;
            }

            cont = false;
            buffer.clear();

            // Semantik optional (später: REPL = define-before-use)
            /*
            try {
                SemanticChecker sem;
                sem.checkProgram(chunk);
            } catch (std::exception& e) {
                std::cerr << e.what() << "\n";
                continue;
            }
            */

            // WICHTIG: in REPL nur registrieren + statements im Session ausführen
            interp.loadProgram(chunk);
            interp.execRepl(chunk);
        }

        return 0;
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
