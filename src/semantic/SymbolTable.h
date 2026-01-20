#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>

#include "Type.h"

// -------- Symbole --------
struct VarSymbol {
    std::string name;
    Type type;
};

struct FunctionSymbol {
    std::string name;
    std::vector<Type> paramTypes;
    Type returnType;
};

// -------- Scope --------
struct Scope {
    std::unordered_map<std::string, VarSymbol> variables;
};

// -------- SymbolTable --------
class SymbolTable {
private:
    // Scope-Stack (lokal -> global)
    std::vector<Scope> scopes;

    // Funktionen liegen global (Overloading)
    std::unordered_map<std::string, std::vector<FunctionSymbol>> functions;

public:
    SymbolTable() {
        // globaler Scope
        scopes.emplace_back();
    }

    // ----- Scope Handling -----
    void pushScope() {
        scopes.emplace_back();
    }

    void popScope() {
        if (scopes.size() <= 1)
            throw std::runtime_error("Cannot pop global scope");
        scopes.pop_back();
    }

    // ----- Variablen -----
    void declareVar(const std::string& name, const Type& type) {
        auto& vars = scopes.back().variables;
        if (vars.count(name))
            throw std::runtime_error("Variable redeclared: " + name);
        vars[name] = VarSymbol{name, type};
    }

    VarSymbol lookupVar(const std::string& name) const {
        for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
            auto found = it->variables.find(name);
            if (found != it->variables.end())
                return found->second;
        }
        throw std::runtime_error("Unknown variable: " + name);
    }

    // ----- Funktionen -----
    void declareFunction(const FunctionSymbol& fn) {
        auto& list = functions[fn.name];
        for (const auto& existing : list) {
            if (sameSignature(existing, fn))
                throw std::runtime_error("Function redeclared: " + fn.name);
        }
        list.push_back(fn);
    }

    FunctionSymbol lookupFunction(
        const std::string& name,
        const std::vector<Type>& argTypes
    ) const {
        auto it = functions.find(name);
        if (it == functions.end())
            throw std::runtime_error("Unknown function: " + name);

        const FunctionSymbol* match = nullptr;
        for (const auto& fn : it->second) {
            if (matches(fn, argTypes)) {
                if (match)
                    throw std::runtime_error("Ambiguous function call: " + name);
                match = &fn;
            }
        }

        if (!match)
            throw std::runtime_error("No matching overload for function: " + name);

        return *match;
    }

    const std::vector<FunctionSymbol>& getOverloads(const std::string& name) const {
        static const std::vector<FunctionSymbol> empty;
        auto it = functions.find(name);
        if (it == functions.end()) return empty;
        return it->second;
    }

private:
    static bool sameSignature(const FunctionSymbol& a,
                              const FunctionSymbol& b) {
        if (a.paramTypes.size() != b.paramTypes.size())
            return false;
        for (size_t i = 0; i < a.paramTypes.size(); ++i)
            if (!a.paramTypes[i].equals(b.paramTypes[i]))
                return false;
        return true;
    }

    static bool matches(const FunctionSymbol& fn,
                        const std::vector<Type>& args) {
        if (fn.paramTypes.size() != args.size())
            return false;
        for (size_t i = 0; i < args.size(); ++i)
            if (!fn.paramTypes[i].equals(args[i]))
                return false;
        return true;
    }
};
