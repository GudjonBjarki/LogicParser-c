#pragma once

#include <stdbool.h>
#include <wchar.h>

#include "Shared/Operators.h"

struct s_Expression;

typedef enum e_ExpressionType
{
  EXPR_BINARY_OP,
  EXPR_CONSTANT,
  EXPR_PROP,
  EXPR_NEGATION,
} ExpressionType;

typedef struct s_Expression
{
  ExpressionType type; 
  union {
    // EXPR_BINARY_OP
    struct s_ExpressionBinaryOp {
      Operator operation;
      struct s_Expression* left;
      struct s_Expression* right;
    } binaryOp;
  
    // EXPR_CONSTANT
    bool constant;

    // EXPR_PROP
    const wchar_t* proposition;

    // EXPR_NEGATION
    struct s_Expression* negation;
  } as;
} Expression;


void EX_Free(Expression* ex);

Expression* EX_NewConst(bool v);
Expression* EX_NewBinop(Operator op, Expression* left, Expression* right);
Expression* EX_NewProp(const wchar_t* s);
Expression* EX_NewPropCopy(const wchar_t* s);
Expression* EX_NewNegation(Expression* negatedExpr);


void PrettyPrintExpression(Expression* ex);

