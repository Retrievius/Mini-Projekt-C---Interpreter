class Interpreter : public ASTVisitor {
public:
  void visit(IntLiteral*) override;
  void visit(BinaryExpr*) override;
  void visit(IfStmt*) override;
  void visit(WhileStmt*) override;
  void visit(ReturnStmt*) override;
  void visit(FunctionDecl*) override;
  // ...
};

void Interpreter::visit(BinaryExpr* e) {
  // TODO
}

std::vector<StackFrame> callStack;

Value lastValue;
