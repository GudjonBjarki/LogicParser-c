#include "Token.h"

#include <stdio.h>

Token T_MakeLiteral(wchar_t* lit)
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

Token T_MakeNot()
{
  return (Token) { .type = TT_NOT };
}

void T_Free(Token* t)
{
  switch (t->type)
  {
    case TT_LITERAL:
      free((void*)t->as.literal);
      t->as.literal = NULL;
      break;

    case TT_OPERATOR: break;
    case TT_CONSTANT: break;
    case TT_LPAREN: break;
    case TT_RPAREN: break;
    case TT_NOT: break;
  }
}

void PrintToken(const Token t)
{
  switch (t.type)
  {
    case TT_LITERAL:
      printf("Literal('%ls')", t.as.literal);
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

    case TT_NOT:
       printf("Not");
       break;
  }
}

void PrettyPrintTokens(const Token* tokens, size_t nTokens)
{
  for (size_t i = 0; i < nTokens; i++)
  {
    PrintToken(tokens[i]);
    printf(", ");
  }
  printf("\n");
}

