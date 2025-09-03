#include "Lexer.h"

#include <stdio.h>
#include <ctype.h>
#include <wctype.h>

#include "Token.h"
#include "Scanners/WStringScanner.h"
#include "Utils/DynamicBuffer.h"


bool IsSpace(wchar_t c) { return iswspace((wint_t)c); }
bool ParseWhitespace(const WStringCursor sc, WStringCursor *out_sc, wchar_t** out_s)
{
  return WSS_Span(sc, IsSpace, out_sc, out_s);
}

bool ParseOperatorToken(const WStringCursor sc, WStringCursor* out_sc, Token* out_t)
{
  if (WSS_Char(sc, L'&', out_sc) || WSS_String(sc, L"AND ", out_sc))
  {
    if (out_t) *out_t = T_MakeOperator(OP_AND);
    return true;
  }

  if (WSS_Char(sc, L'|', out_sc) || WSS_String(sc, L"OR ", out_sc))
  {
    if (out_t) *out_t = T_MakeOperator(OP_OR);
    return true;
  }

  if (WSS_Char(sc, L'^', out_sc) || WSS_String(sc, L"XOR ", out_sc))
  {
    if (out_t) *out_t = T_MakeOperator(OP_XOR);
    return true;
  }

  if (WSS_String(sc, L"->", out_sc) || WSS_String(sc, L"IMPL ", out_sc))
  {
    if (out_t) *out_t = T_MakeOperator(OP_IMPL);
    return true;
  }

  if (WSS_String(sc, L"==", out_sc) || WSS_String(sc, L"<->", out_sc) || WSS_String(sc, L"EQU ", out_sc))
  {
    if (out_t) *out_t = T_MakeOperator(OP_EQU);
    return true;
  }

  return false;
}

bool IsAlpha(wchar_t c) { return iswalpha((wint_t)c); }
bool ParseLiteral(const WStringCursor sc, WStringCursor* out_sc, Token* out_t)
{
  wchar_t* s = NULL;
  if (WSS_Span(sc, IsAlpha, out_sc, (out_t) ? &s : NULL) > 0)
  {
    if (out_t) *out_t = T_MakeLiteral(s);
    return true;
  }
  
  return false;
}

bool ParseConstantToken(const WStringCursor sc, WStringCursor* out_sc, Token* out_t)
{
  if (
    WSS_Char(sc, L'1', out_sc) ||
    WSS_String(sc, L"True ", out_sc) ||
    WSS_String(sc, L"T ", out_sc)
  )
  {
    if (out_t) *out_t = T_MakeConstant(true);
    return true;
  }

  if (
    WSS_Char(sc, L'0', out_sc) ||
    WSS_String(sc, L"False ", out_sc) ||
    WSS_String(sc, L"F ", out_sc)
  )
  {
    if (out_t) * out_t = T_MakeConstant(false);
    return true;
  }

  return false;
}

bool ParseKeywordToken(const WStringCursor sc, WStringCursor* out_sc, Token* out_t)
{
  if (WSS_Char(sc, L'(', out_sc))
  {
    if (out_t) *out_t = T_MakeLParen();
    return true;
  }

  if (WSS_Char(sc, L')', out_sc))
  {
    if (out_t) *out_t = T_MakeRParen();
    return true;
  }

  if (WSS_Char(sc, L'!', out_sc))
  { 
    if (out_t) *out_t = T_MakeNot();
    return true;
  }

  return false;
}


bool ParseToken(const WStringCursor sc, WStringCursor* out_sc, Token* out_t)
{
  return (
    ParseKeywordToken(sc, out_sc, out_t) ||
    ParseOperatorToken(sc, out_sc, out_t) ||
    ParseConstantToken(sc, out_sc, out_t) ||
    ParseLiteral(sc, out_sc, out_t)
  );
}

ssize_t Tokenize(wchar_t *source, Token** out_tokens)
{
  WStringCursor cursor = WSC_Create(source);
  DynamicBuffer tokenBuffer = DB_Create(sizeof(Token), 16);
  
  size_t nRead = 0;
  while (true)
  {
    ParseWhitespace(cursor, &cursor, NULL);
    if (WSC_Done(cursor)) break;

    Token token;
    if (!ParseToken(cursor, &cursor, &token))
    {
      fprintf(stderr, "Failed to parse token at char %lu. Remainder: \"%ls\"\n", cursor.index, WSC_Cursor(cursor));
      fprintf(stderr, "%ls\n", cursor.source);
      for (size_t i = 0; i < cursor.index; i++) fprintf(stderr, " ");
      fprintf(stderr, "^\n");

      DB_Free(&tokenBuffer);
      return -1;
    }

    if (out_tokens) 
    {
      if (!DB_Append(&tokenBuffer, &token))
      {
        DB_Free(&tokenBuffer);
        return -1;
      }
    }

    nRead++;
  }
  
  if (out_tokens) *out_tokens = DB_Release(&tokenBuffer);
  return (ssize_t)nRead;
}

void FreeTokenArray(Token* tokens, size_t numTokens)
{
  for (size_t i = 0; i < numTokens; i++)
  {
    T_Free(&tokens[i]);
  }
  free(tokens);
}
