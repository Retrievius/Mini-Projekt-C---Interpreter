#include <cassert>
#include <iostream>

#include "interpreter/Interpreter.h"
#include "ast/AST.h"

int main() {
  Interpreter interpreter;

  auto expr = new BinaryExpr(
    BinaryOp::Add,
    new IntLiteral(1),
    new IntLiteral(2)
  );

  Value result = interpreter.evalExpr(expr);
  assert(result.intValue == 3);

  std::cout << "Test passed\n";
}

