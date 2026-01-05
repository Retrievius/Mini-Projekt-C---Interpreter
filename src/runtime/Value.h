/* Ein Value ist ein konkreter Laufzeitwert (Int, String, Object, etc.) */

// Compilerschutz, Datei wird nur einmal eingebunden
#pragma once
#include <string>
#include <memory>

struct Object; // forward

// Welche Art von Wert
enum class ValueKind {
  Int,
  Bool,
  Char,
  String,
  Object,
  Void
};

// Jeder Value weiß welcher ValueKind er ist
struct Value {
  ValueKind kind;

// Nur eins davon ist gültig
  int intValue;
  bool boolValue;
  char charValue;
  std::string stringValue;
  std::shared_ptr<Object> objectValue;

// Verhindert das kind nicht gesetzt wird
  static Value makeInt(int v) {
    Value val; val.kind = ValueKind::Int; val.intValue = v; return val;
  }

// Funktion ohne Rückgabewert
  static Value makeVoid() {
    Value val; val.kind = ValueKind::Void; return val;
  }
};
