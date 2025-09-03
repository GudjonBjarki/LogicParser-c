#pragma once

#include <wchar.h>

#include "Lexer/Token.h"

typedef struct s_TokenCursor
{
  const Token* buffer;
  size_t index;
  size_t length;
} TokenCursor;


TokenCursor TC_Create(const Token* tokens, size_t length);
bool TC_Done(const TokenCursor tc);
const Token* TC_Cursor(const TokenCursor tc);

bool TS_Literal(const TokenCursor tc, TokenCursor* out_tc, const wchar_t** out_literal);
bool TS_Operator(const TokenCursor tc, TokenCursor* out_tc, Operator* out_op);
bool TS_Constant(const TokenCursor tc, TokenCursor* out_tc, bool* out_const);
bool TS_LParen(const TokenCursor tc, TokenCursor* out_tc);
bool TS_RParen(const TokenCursor tc, TokenCursor* out_tc);
bool TS_Not(const TokenCursor tc, TokenCursor* out_tc);
