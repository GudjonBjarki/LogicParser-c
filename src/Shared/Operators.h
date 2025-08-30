#pragma once


typedef enum e_Operator
{
  OP_AND,
  OP_OR,
  OP_XOR,
  OP_IMPL,
  OP_EQU,
} Operator;

char* OperatorToString(Operator op);
