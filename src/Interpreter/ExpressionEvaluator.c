#include "ExpressionEvaluator.h"

bool EvaluateBinaryOperation(Environment* env, Operator op, Expression* left, Expression* right)
{
  switch (op)
  {
    case OP_AND:
      return EvaluateExpression(env, left) && EvaluateExpression(env, right);
    case OP_OR:
      return EvaluateExpression(env, left) || EvaluateExpression(env, right);
    case OP_XOR:
      return EvaluateExpression(env, left) != EvaluateExpression(env, right);
    case OP_IMPL:
      return !EvaluateExpression(env, left) || EvaluateExpression(env, right);
    case OP_EQU:
      return EvaluateExpression(env, left) == EvaluateExpression(env, right);
  }

  return false;
}


bool EvaluateExpression(Environment* env, Expression* expr)
{
  switch (expr->type)
  {
    case EXPR_CONSTANT:
      // printf("Evaluating constant %d\n", expr->as.constant);
      return expr->as.constant;

    case EXPR_BINARY_OP:
      // printf("evaluating binary operation\n");
      const struct s_ExpressionBinaryOp* binop = &expr->as.binaryOp;
      return EvaluateBinaryOperation(env, binop->operation, binop->left, binop->right);

    case EXPR_PROP:
      return ENV_Get(env, expr->as.proposition);

    case EXPR_NEGATION:
      return !(EvaluateExpression(env, expr->as.negation));
  }

  return false;
}

