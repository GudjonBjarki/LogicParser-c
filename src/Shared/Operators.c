#include "Operators.h"

const wchar_t* OperatorToString(Operator op)
{
  switch (op)
  {
    case OP_AND: return L"∧";
    case OP_OR: return L"∨";
    case OP_XOR: return L"⊕";
    case OP_IMPL: return L"→";
    case OP_EQU: return L"↔";
  }
  
  return L"UNKNOWN OPERATOR";
}

