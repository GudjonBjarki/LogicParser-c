#include "Token.h"

#include <stdio.h>

Token T_MakeLiteral(char* lit)
{
  return (Token) { .type = TT_LITERAL, .as.literal = lit };
}

Token T_MakeOperator(Operator op)
{
  return (Token) { .type = TT_OPERATOR, .as.operator = op };
}

Token T_MakeConstant(bool v)
{
  return (Token) { .type = TT_CONSTANT, .as.constant = v };
}

Token T_MakeLParen()
{
  return (Token) { .type = TT_LPAREN };
}

Token T_MakeRParen()
{
  return (Token) { .type = TT_RPAREN };
}

void T_Free(Token* t)
{
  switch (t->type)
  {
    case TT_LITERAL:
      free(t->as.literal);
      t->as.literal = NULL;
      break;

    default:
      break;
  }
}

void PrintToken(Token t)
{
  switch (t.type)
  {
    case TT_LITERAL:
      printf("Literal('%s')", t.as.literal);
      break;

    case TT_OPERATOR:
      printf("Operator(%s)", OperatorToString(t.as.operator));
      break;

    case TT_CONSTANT:
       if (t.as.operator) printf("Literal(T)");
       else               printf("Literal(F)");
       break;

    case TT_LPAREN:
       printf("LeftParen");
       break;

    case TT_RPAREN:
       printf("RightParen");
       break;
  }
}

