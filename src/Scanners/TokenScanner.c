#include "TokenScanner.h"

TokenCursor TC_Create(Token* tokens, size_t length)
{
  return (TokenCursor)
  {
    .buffer = tokens,
    .index = 0,
    .length = length
  };
}

bool TC_Done(const TokenCursor tc)
{
  return tc.index >= tc.length;
}

Token* TC_Cursor(const TokenCursor tc)
{
  return TC_Done(tc) ? NULL : &tc.buffer[tc.index];
}

TokenCursor TC_Step(const TokenCursor tc, size_t n)
{
  size_t newIndex = tc.index + n;
  if (newIndex > tc.length) newIndex = tc.length;
  return (TokenCursor)
  {
    .buffer = tc.buffer,
    .length = tc.length,
    .index = newIndex
  };
}


bool TS_OfType(const TokenCursor tc, TokenType type, TokenCursor* out_tc, Token* out_t)
{
  Token* token = TC_Cursor(tc);
  if (!token) return false;
  if (token->type != type) return false;

  if (out_tc) *out_tc = TC_Step(tc, 1);
  if (out_t) *out_t = *token;
  return true;
}


bool TS_Literal(const TokenCursor tc, TokenCursor* out_tc, char** out_literal)
{
  Token token;
  if (!TS_OfType(tc, TT_LITERAL, out_tc, &token)) return false;

  if (out_literal) *out_literal = token.as.literal;
  return true;
}

bool TS_Operator(const TokenCursor tc, TokenCursor* out_tc, Operator* out_op)
{
  Token token;
  if (!TS_OfType(tc, TT_OPERATOR, out_tc, &token)) return false;

  if (out_op) *out_op = token.as.operator;
  return true;
}

bool TS_Constant(const TokenCursor tc, TokenCursor* out_tc, bool* out_const)
{
  Token token;
  if (!TS_OfType(tc, TT_CONSTANT, out_tc, &token)) return false;

  if (out_const) *out_const = token.as.constant;
  return true;
}

bool TS_LParen(const TokenCursor tc, TokenCursor* out_tc)
{
  return TS_OfType(tc, TT_LPAREN, out_tc, NULL);
}

bool TS_RParen(const TokenCursor tc, TokenCursor* out_tc)
{
  return TS_OfType(tc, TT_RPAREN, out_tc, NULL);
}

bool TS_Not(const TokenCursor tc, TokenCursor* out_tc)
{
  return TS_OfType(tc, TT_NOT, out_tc, NULL);
}


