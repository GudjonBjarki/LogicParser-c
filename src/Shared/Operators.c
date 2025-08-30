#include "Operators.h"

char* OperatorToString(Operator op)
{
  switch (op)
  {
    case OP_AND: return "&";
    case OP_OR: return "|";
    case OP_XOR: return "^";
    case OP_IMPL: return "->";
    case OP_EQU: return "<->";
  }
  
  return "UNKNOWN OPERATOR";
}

