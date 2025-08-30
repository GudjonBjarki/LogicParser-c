#pragma once


typedef enum e_Operator
{
  OP_AND,
  OP_OR,
} Operator;

char* OperatorToString(Operator op);
