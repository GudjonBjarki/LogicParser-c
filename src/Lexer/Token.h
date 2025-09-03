#pragma once

#include <stdbool.h>
#include <stdlib.h>

#include "Shared/Operators.h"

typedef enum e_TokenType
{
  TT_LITERAL,
  TT_OPERATOR,
  TT_CONSTANT,
  TT_LPAREN,
  TT_RPAREN,
  TT_NOT,
} TokenType;


typedef struct s_Token
{
  TokenType type;

  union u_TokenData
  {
    char* literal;
    Operator operator;
    bool constant;
  } as;
} Token;


Token T_MakeLiteral(char* lit);
Token T_MakeOperator(Operator op);
Token T_MakeConstant(bool v);
Token T_MakeLParen();
Token T_MakeRParen();
Token T_MakeNot();
void T_Free(Token* t);

void PrintToken(const Token t);
void PrettyPrintTokens(const Token* tokens, size_t nTokens);
