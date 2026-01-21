#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "Cell.h"

struct Object {
    std::string dynamicClass;
    std::unordered_map<std::string, Cell*> fields;
};
