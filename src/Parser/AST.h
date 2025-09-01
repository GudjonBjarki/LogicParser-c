#pragma once

#include "Lexer/Token.h"


struct s_Expression;

typedef enum e_ExpressionType
{
  EXPR_BINARY_OP,
  EXPR_CONSTANT,
  EXPR_PROP
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
    char* proposition;
  } as;
} Expression;


void EX_Free(Expression* ex);

Expression* EX_NewConst(bool v);
Expression* EX_NewBinop(Operator op, Expression* left, Expression* right);
Expression* EX_NewProp(char* s);
Expression* EX_NewPropCopy(char* s);


void PrettyPrintExpression(Expression* ex);

