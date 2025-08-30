#pragma once

#include "Lexer/Token.h"


struct s_Expression;

typedef enum e_ExpressionType
{
  EXPR_BINARY_OP,
  EXPR_CONSTANT,
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

  } as;
} Expression;


void EX_Free(Expression* ex);

Expression* EX_NewConst(bool v);
Expression* EX_NewBinop(Operator op, Expression* left, Expression* right);


void PrettyPrintExpression(Expression* ex);

