#pragma once

#include <wchar.h>


typedef enum e_Operator
{
  OP_AND,
  OP_OR,
  OP_XOR,
  OP_IMPL,
  OP_EQU,
} Operator;

const wchar_t* OperatorToString(Operator op);
