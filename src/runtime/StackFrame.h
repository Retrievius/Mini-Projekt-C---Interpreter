/* Ein StackFrame speichert alle lokalen Variablen eines Scopes. */

// Compilerschutz, Datei wird nur einmal eingebunden
#pragma once
#include <unordered_map>
#include <string>
#include "Cell.h"

// Scope, locals bedeutet Name von Cell
struct StackFrame {
  std::unordered_map<std::string, Cell*> locals;
};
