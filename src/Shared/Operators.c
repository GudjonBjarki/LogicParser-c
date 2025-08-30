#include "Operators.h"

char* OperatorToString(Operator op)
{
  switch (op)
  {
    case OP_AND: return "&";
    case OP_OR: return "|";
  }
  
  return "UNKNOWN OPERATOR";
}

