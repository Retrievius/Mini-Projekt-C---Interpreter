#pragma once
#include <string>
#include <memory>

// Typkategorien (C++-Subset)
enum class TypeKind {
    Int,
    Bool,
    Char,
    String,
    Void,
    Class,
    Ref
};

struct Type {
    TypeKind kind;

    // Für Class: Klassenname
    // Für Ref:   Basistyp
    std::string className;
    std::shared_ptr<Type> refBase;

    // ---- Factory-Methoden ----
    static Type Int()    { return {TypeKind::Int, "", nullptr}; }
    static Type Bool()   { return {TypeKind::Bool, "", nullptr}; }
    static Type Char()   { return {TypeKind::Char, "", nullptr}; }
    static Type String() { return {TypeKind::String, "", nullptr}; }
    static Type Void()   { return {TypeKind::Void, "", nullptr}; }

    static Type Class(const std::string& name) {
        return {TypeKind::Class, name, nullptr};
    }

    static Type Ref(const Type& base) {
        return {TypeKind::Ref, "", std::make_shared<Type>(base)};
    }

    // ---- Abfragen ----
    bool isRef() const {
        return kind == TypeKind::Ref;
    }

    const Type& refType() const {
        return *refBase;
    }

    // ---- Typgleichheit (exakt, inkl. &) ----
    bool equals(const Type& other) const {
        if (kind != other.kind) return false;

        if (kind == TypeKind::Class)
            return className == other.className;

        if (kind == TypeKind::Ref)
            return refType().equals(other.refType());

        return true; // primitive + void
    }

    // ---- Bool-Kontext (if / while) ----
    bool isBoolContextConvertible() const {
        return kind == TypeKind::Bool ||
               kind == TypeKind::Int ||
               kind == TypeKind::Char ||
               kind == TypeKind::String;
    }

    // ---- Für Fehlermeldungen ----
    std::string toString() const {
        switch (kind) {
            case TypeKind::Int:    return "int";
            case TypeKind::Bool:   return "bool";
            case TypeKind::Char:   return "char";
            case TypeKind::String: return "string";
            case TypeKind::Void:   return "void";
            case TypeKind::Class:  return className;
            case TypeKind::Ref:    return refType().toString() + "&";
        }
        return "<?>";
    }
};

