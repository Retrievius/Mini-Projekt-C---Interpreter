/* Ein Cell ist ein benannter Speicherort der ein Value enthält. Value kann sich ändern, Cell bleibt gleich. */

// Compilerschutz, Datei wird nur einmal eingebunden
#pragma once
#include "Value.h"

// Speicherplatz mit Value als Inhalt
struct Cell {
  Value value;
};
