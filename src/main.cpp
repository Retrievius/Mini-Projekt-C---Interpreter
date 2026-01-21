#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <algorithm>

#include "external/antlr4-runtime/runtime/src/antlr4-runtime.h"
#include "gen/cppLexer.h"
#include "gen/cppParser.h"

#include "ast/AST.h"
#include "ast/ASTBuilder.h"
#include "interpreter/Interpreter.h"
#include "semantic/SemanticChecker.h"

namespace fs = std::filesystem;

// -------------------- IO helpers --------------------

static std::string readFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Cannot open file: " + path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

static std::string trim(std::string s) {
    auto is_ws = [](unsigned char c){ return c==' '||c=='\t'||c=='\r'||c=='\n'; };
    size_t i = 0;
    while (i < s.size() && is_ws((unsigned char)s[i])) ++i;
    size_t j = s.size();
    while (j > i && is_ws((unsigned char)s[j-1])) --j;
    return s.substr(i, j - i);
}

// Extract EXPECT block like Makefile: lines between "/* EXPECT" and "*/"
static std::string extractExpect(const std::string& code) {
    auto pos = code.find("/* EXPECT");
    if (pos == std::string::npos) return "";

    // find end of that line
    auto start = code.find('\n', pos);
    if (start == std::string::npos) return "";
    start += 1;

    auto end = code.find("*/", start);
    if (end == std::string::npos) return "";

    std::string block = code.substr(start, end - start);

    // remove leading " * " prefixes if present
    std::stringstream in(block);
    std::stringstream out;
    std::string line;
    while (std::getline(in, line)) {
        // strip common comment decoration
        std::string t = line;
        t = trim(t);
        if (t.rfind("*", 0) == 0) {
            t.erase(0, 1);
            if (!t.empty() && t[0] == ' ') t.erase(0, 1);
        }
        out << t << "\n";
    }
    return out.str();
}

// -------------------- ANTLR error capture --------------------

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

// Less aggressive than "<EOF>" anywhere
static bool isIncomplete(const std::vector<std::string>& errs) {
    for (auto& e : errs) {
        if (e.find("at '<EOF>'") != std::string::npos) return true;
        if (e.find("mismatched input '<EOF>'") != std::string::npos) return true;
        if (e.find("extraneous input '<EOF>'") != std::string::npos) return true;
    }
    return false;
}

// -------------------- Running a program (capture output) --------------------

struct RunResult {
    int exitCode = 0;
    std::string stdoutText;
    std::string stderrText;
};

static RunResult runInterpreterOnCode(const std::string& code) {
    RunResult rr;

    // redirect cout/cerr
    std::ostringstream outBuf, errBuf;
    auto* oldCout = std::cout.rdbuf(outBuf.rdbuf());
    auto* oldCerr = std::cerr.rdbuf(errBuf.rdbuf());

    try {
        std::vector<std::string> perr;
        Program* prog = parseProgram(code, perr);
        if (!prog) {
            for (auto& e : perr) std::cerr << e << "\n";
            rr.exitCode = 1;
        } else {


            SemanticChecker sem;
            sem.checkProgram(prog);


            Interpreter interp;
            interp.run(prog);
            rr.exitCode = 0;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        rr.exitCode = 1;
    }

    // restore
    std::cout.rdbuf(oldCout);
    std::cerr.rdbuf(oldCerr);

    rr.stdoutText = outBuf.str();
    rr.stderrText = errBuf.str();
    return rr;
}

// -------------------- Test runner --------------------

static std::vector<fs::path> listCppFiles(const fs::path& dir) {
    std::vector<fs::path> files;
    if (!fs::exists(dir)) return files;

    for (auto& it : fs::directory_iterator(dir)) {
        if (!it.is_regular_file()) continue;
        auto p = it.path();
        if (p.extension() == ".cpp") files.push_back(p);
    }
    std::sort(files.begin(), files.end());
    return files;
}

static int runPosTests(const fs::path& dir) {
    auto files = listCppFiles(dir);
    if (files.empty()) {
        std::cerr << "No pos tests found in: " << dir.string() << "\n";
        return 1;
    }

    int fails = 0;

    for (auto& f : files) {
        std::string code = readFile(f.string());
        std::string expect = extractExpect(code);

        std::cout << "==> POS " << f.filename().string() << "\n";

        RunResult rr = runInterpreterOnCode(code);

        if (rr.exitCode != 0) {
            std::cout << "[FAIL] runtime/parse error\n";
            if (!rr.stderrText.empty()) std::cout << rr.stderrText;
            fails++;
            continue;
        }

        if (!expect.empty()) {
            // normalize newlines
            auto norm = [](std::string s){
                s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
                return s;
            };
            std::string got = norm(rr.stdoutText);
            std::string exp = norm(expect);

            if (got != exp) {
                std::cout << "[FAIL] output mismatch\n";
                std::cout << "--- expected ---\n" << exp;
                std::cout << "--- got ---\n" << got;
                fails++;
            } else {
                std::cout << "[OK]\n";
            }
        } else {
            // no EXPECT block -> just pass if no error
            std::cout << "[OK] (no EXPECT block)\n";
        }
    }

    return fails == 0 ? 0 : 1;
}

static int runNegTests(const fs::path& dir) {
    auto files = listCppFiles(dir);
    if (files.empty()) {
        std::cerr << "No neg tests found in: " << dir.string() << "\n";
        return 1;
    }

    int fails = 0;

    for (auto& f : files) {
        std::string code = readFile(f.string());
        std::cout << "==> NEG " << f.filename().string() << " (should fail)\n";

        RunResult rr = runInterpreterOnCode(code);

        if (rr.exitCode == 0) {
            std::cout << "[FAIL] unexpectedly succeeded\n";
            std::cout << "--- output ---\n" << rr.stdoutText;
            fails++;
        } else {
            std::cout << "[OK]\n";
        }
    }

    return fails == 0 ? 0 : 1;
}

// -------------------- REPL --------------------

static void runRepl(Interpreter& interp) {
    interp.ensureSession();

    std::cout << "REPL started. Exit with :q / :exit. Reset buffer with :reset\n";

    std::string buffer;
    bool cont = false;

    SemanticChecker sem;

    while (true) {
        std::cout << (cont ? "... " : ">>> ");
        std::string line;
        if (!std::getline(std::cin, line)) break;

        line = trim(line);

        // commands ALWAYS (even in cont-mode)
        if (line == ":q" || line == ":exit" || line == "exit") break;
        if (line == ":reset") { buffer.clear(); cont = false; continue; }

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


        sem.checkProgram(chunk);


        interp.loadProgram(chunk);
        interp.execRepl(chunk);
    }
}

// -------------------- CLI --------------------

enum class Mode {
    ReplOnly,
    RunFile,
    Pos,
    Neg,
    All
};

static void printHelp() {
    std::cout <<
        "Usage:\n"
        "  Mini_Projekt_C___Interpreter.exe                 (REPL)\n"
        "  Mini_Projekt_C___Interpreter.exe --file <path>   (run file)\n"
        "  Mini_Projekt_C___Interpreter.exe --file <path> --repl (run file then REPL)\n"
        "  Mini_Projekt_C___Interpreter.exe --pos           (run tests/pos/*.cpp)\n"
        "  Mini_Projekt_C___Interpreter.exe --neg           (run tests/neg/*.cpp)\n"
        "  Mini_Projekt_C___Interpreter.exe --all           (pos + neg)\n";
}

int main(int argc, char** argv) {
    try {
        Mode mode = Mode::ReplOnly;
        bool replAfterFile = false;
        std::string filePath;

        // defaults for your project layout
        fs::path posDir = fs::path("tests") / "pos";
        fs::path negDir = fs::path("tests") / "neg";

        // parse args
        for (int i = 1; i < argc; ++i) {
            std::string a = argv[i];

            if (a == "--help" || a == "-h") {
                printHelp();
                return 0;
            }
            if (a == "--repl") { replAfterFile = true; continue; }

            if (a == "--file" && i + 1 < argc) {
                filePath = argv[++i];
                mode = Mode::RunFile;
                continue;
            }
            if (a == "--pos") { mode = Mode::Pos; continue; }
            if (a == "--neg") { mode = Mode::Neg; continue; }
            if (a == "--all") { mode = Mode::All; continue; }

            // fallback: if user passes a path without --file
            if (a.size() > 4 && a.substr(a.size()-4) == ".cpp") {
                filePath = a;
                mode = Mode::RunFile;
                continue;
            }

            std::cerr << "Unknown argument: " << a << "\n";
            printHelp();
            return 1;
        }

        // mode switch
        switch (mode) {
            case Mode::ReplOnly: {
                Interpreter interp;
                runRepl(interp);
                return 0;
            }
            case Mode::RunFile: {
                if (filePath.empty()) {
                    std::cerr << "--file needs a path\n";
                    return 1;
                }
                std::string code = readFile(filePath);

                std::vector<std::string> perr;
                Program* prog = parseProgram(code, perr);
                if (!prog) {
                    for (auto& e : perr) std::cerr << e << "\n";
                    return 1;
                }

                Interpreter interp;
                interp.run(prog);

                if (replAfterFile) runRepl(interp);
                return 0;
            }
            case Mode::Pos: {
                return runPosTests(posDir);
            }
            case Mode::Neg: {
                return runNegTests(negDir);
            }
            case Mode::All: {
                int a = runPosTests(posDir);
                int b = runNegTests(negDir);
                return (a==0 && b==0) ? 0 : 1;
            }
        }

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
