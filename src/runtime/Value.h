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
  // union / variant
};
