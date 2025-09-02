#include "Parser.h"

#include "Scanners/TokenScanner.h"

#include <stdio.h>

bool ParseExpression(const TokenCursor tc, TokenCursor* out_tc, Expression** out_expr);


bool ParseConstantExpr(const TokenCursor tc, TokenCursor* out_tc, Expression** out_expr)
{
  bool v;
  if (!TS_Constant(tc, out_tc, &v))
  {
    return false;
  }
  
  if (out_expr) *out_expr = EX_NewConst(v);
  return true;
}

bool ParseBinaryOpInfixExpr(const TokenCursor tc, TokenCursor* out_tc, Expression** out_expr)
{
  TokenCursor bufferCursor = tc;

  if (!TS_LParen(bufferCursor, &bufferCursor))
  {
    return false;
  }
  
  Expression* left;
  if (!ParseExpression(bufferCursor, &bufferCursor, out_expr ? &left : NULL))
  {
    return false;
  }

  Operator op;
  if (!TS_Operator(bufferCursor, &bufferCursor, &op))
  {
    EX_Free(left);
    return false;
  }

  Expression* right;
  if (!ParseExpression(bufferCursor, &bufferCursor, out_expr ? &right : NULL))
  {
    EX_Free(left);
    return false;
  }


  if (!TS_RParen(bufferCursor, &bufferCursor))
  {
    return false;
  }

   if (out_expr)
   {
     *out_expr = EX_NewBinop(op, left, right);
   }

   if (out_tc) *out_tc = bufferCursor;

  return true;
}

bool ParseProposition(const TokenCursor tc, TokenCursor* out_tc, Expression** out_expr)
{
  char* prop;
  if (!TS_Literal(tc, out_tc, &prop) || prop == NULL) return false;
  
  if (out_expr)
  {
    *out_expr = EX_NewPropCopy(prop);
  }

  return true;
}

bool ParseNegation(const TokenCursor tc, TokenCursor* out_tc, Expression** out_expr)
{
  TokenCursor bufferCursor = tc;
  if (!TS_Not(bufferCursor, &bufferCursor)) return false;

  Expression* expr;
  if (!ParseExpression(bufferCursor, &bufferCursor, &expr))
  {
    return false;
  }

  if (out_expr) *out_expr = EX_NewNegation(expr);
  if (out_tc) *out_tc = bufferCursor;

  return true;
}


bool ParseExpression(const TokenCursor tc, TokenCursor* out_tc, Expression** out_expr)
{
  Expression* expr;
  if (
    ParseBinaryOpInfixExpr(tc, out_tc, out_expr ? &expr : NULL) ||
    ParseNegation(tc, out_tc, out_expr ? &expr : NULL) ||
    ParseConstantExpr(tc, out_tc, out_expr ?  &expr : NULL) ||
    ParseProposition(tc, out_tc, out_expr ? &expr : NULL)
  )
  {
    if (out_expr) *out_expr = expr;
    return true;
  }

  return false;
}


bool Parse(Token* tokens, size_t numTokens, Expression** out_expr)
{
  TokenCursor cursor = TC_Create(tokens, numTokens);
  bool res = ParseExpression(cursor, &cursor, out_expr);
  
  if (!res) return false;
  if (!TC_Done(cursor))
  {
    fprintf(stderr, "Tokens still remain after parsing.\n");
    fprintf(stderr, "Remainder: "); PrettyPrintTokens(TC_Cursor(cursor), cursor.length - cursor.index);
    fprintf(stderr, "\n");
  }

  return true;
}

