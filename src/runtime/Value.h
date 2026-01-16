#pragma once
#include <string>
#include <memory>
#include <stdexcept>

struct Object; // forward

enum class ValueKind {
    Int,
    Bool,
    Char,
    String,
    Object,
    Void
  };

struct Value {
    ValueKind kind;

    int intValue = 0;
    bool boolValue = false;
    char charValue = 0;
    std::string stringValue;
    std::shared_ptr<Object> objectValue;

    // --- Factory-Methoden ---

    static Value makeInt(int v) {
        Value val;
        val.kind = ValueKind::Int;
        val.intValue = v;
        return val;
    }

    static Value makeBool(bool v) {
        Value val;
        val.kind = ValueKind::Bool;
        val.boolValue = v;
        return val;
    }

    static Value makeChar(char v) {
        Value val;
        val.kind = ValueKind::Char;
        val.charValue = v;
        return val;
    }

    static Value makeString(const std::string& v) {
        Value val;
        val.kind = ValueKind::String;
        val.stringValue = v;
        return val;
    }

    static Value makeVoid() {
        Value val;
        val.kind = ValueKind::Void;
        return val;
    }

    // --- Bool-Konvertierung (für if/while) ---
    bool isTrue() const {
        switch (kind) {
            case ValueKind::Bool:   return boolValue;
            case ValueKind::Int:    return intValue != 0;
            case ValueKind::Char:   return charValue != 0;
            case ValueKind::String:return !stringValue.empty();
            case ValueKind::Void:   return false;
            default:
                throw std::runtime_error("Cannot convert value to bool");
        }
    }

    // --- Debug / Print ---
    std::string toString() const {
        switch (kind) {
            case ValueKind::Int:    return std::to_string(intValue);
            case ValueKind::Bool:   return boolValue ? "true" : "false";
            case ValueKind::Char:   return std::string(1, charValue);
            case ValueKind::String: return stringValue;
            case ValueKind::Void:   return "<void>";
            default:
                return "<object>";
        }
    }
};
