#include "ExpressionEvaluator.h"

bool EvaluateBinaryOperation(Operator op, Expression* left, Expression* right)
{
  switch (op)
  {
    case OP_AND:
      return EvaluateExpression(left) && EvaluateExpression(right);
    case OP_OR:
      return EvaluateExpression(left) || EvaluateExpression(right);
    case OP_XOR:
      return EvaluateExpression(left) != EvaluateExpression(right);
    case OP_IMPL:
      return !EvaluateExpression(left) || EvaluateExpression(right);
    case OP_EQU:
      return EvaluateExpression(left) == EvaluateExpression(right);
  }

  return false;
}


bool EvaluateExpression(Expression* expr)
{
  switch (expr->type)
  {
    case EXPR_CONSTANT:
      // printf("Evaluating constant %d\n", expr->as.constant);
      return expr->as.constant;

    case EXPR_BINARY_OP:
      // printf("evaluating binary operation\n");
      const struct s_ExpressionBinaryOp* binop = &expr->as.binaryOp;
      return EvaluateBinaryOperation(binop->operation, binop->left, binop->right);

    case EXPR_PROP:
      // Temporary set to false.
      return false;
  }

  return false;
}

