#include "Lexer.h"

#include <stdio.h>
#include <ctype.h>

#include "Token.h"
#include "Scanners/StringScanner.h"
#include "Utils/DynamicBuffer.h"


bool IsSpace(char c) { return isspace(c); }
bool ParseWhitespace(const StringCursor sc, StringCursor *out_sc, char** out_s)
{
  return SS_Span(sc, IsSpace, out_sc, out_s);
}

bool ParseOperatorToken(const StringCursor sc, StringCursor* out_sc, Token* out_t)
{
  if (SS_Char(sc, '&', out_sc) || SS_String(sc, "AND ", out_sc))
  {
    if (out_t) *out_t = T_MakeOperator(OP_AND);
    return true;
  }

  if (SS_Char(sc, '|', out_sc) || SS_String(sc, "OR ", out_sc))
  {
    if (out_t) *out_t = T_MakeOperator(OP_OR);
    return true;
  }

  if (SS_Char(sc, '^', out_sc) || SS_String(sc, "XOR ", out_sc))
  {
    if (out_t) *out_t = T_MakeOperator(OP_XOR);
    return true;
  }

  if (SS_String(sc, "->", out_sc) || SS_String(sc, "IMPL ", out_sc))
  {
    if (out_t) *out_t = T_MakeOperator(OP_IMPL);
    return true;
  }

  if (SS_String(sc, "==", out_sc) || SS_String(sc, "<->", out_sc) || SS_String(sc, "EQU ", out_sc))
  {
    if (out_t) *out_t = T_MakeOperator(OP_EQU);
    return true;
  }

  return false;
}

bool IsAlpha(char c) { return isalpha(c); }
bool ParseLiteral(const StringCursor sc, StringCursor* out_sc, Token* out_t)
{
  char* s = NULL;
  if (SS_Span(sc, IsAlpha, out_sc, (out_t) ? &s : NULL) > 0)
  {
    if (out_t) *out_t = T_MakeLiteral(s);
    return true;
  }
  
  return false;
}

bool ParseConstantToken(const StringCursor sc, StringCursor* out_sc, Token* out_t)
{
  if (
    SS_Char(sc, '1', out_sc) ||
    SS_String(sc, "True ", out_sc) ||
    SS_String(sc, "T ", out_sc)
  )
  {
    if (out_t) *out_t = T_MakeConstant(true);
    return true;
  }

  if (
    SS_Char(sc, '0', out_sc) ||
    SS_String(sc, "False ", out_sc) ||
    SS_String(sc, "F ", out_sc)
  )
  {
    if (out_t) * out_t = T_MakeConstant(false);
    return true;
  }

  return false;
}

bool ParseKeywordToken(const StringCursor sc, StringCursor* out_sc, Token* out_t)
{
  if (SS_Char(sc, '(', out_sc))
  {
    if (out_t) *out_t = T_MakeLParen();
    return true;
  }

  if (SS_Char(sc, ')', out_sc))
  {
    if (out_t) *out_t = T_MakeRParen();
    return true;
  }

  if (SS_Char(sc, '!', out_sc))
  { 
    if (out_t) *out_t = T_MakeNot();
    return true;
  }

  return false;
}


bool ParseToken(const StringCursor sc, StringCursor* out_sc, Token* out_t)
{
  return (
    ParseKeywordToken(sc, out_sc, out_t) ||
    ParseOperatorToken(sc, out_sc, out_t) ||
    ParseConstantToken(sc, out_sc, out_t) ||
    ParseLiteral(sc, out_sc, out_t)
  );
}

ssize_t Tokenize(char *source, Token** out_tokens)
{
  StringCursor cursor = SC_Create(source);
  DynamicBuffer tokenBuffer = DB_Create(sizeof(Token), 16);
  
  size_t nRead = 0;
  while (true)
  {
    ParseWhitespace(cursor, &cursor, NULL);
    if (SC_Done(cursor)) break;

    Token token;
    if (!ParseToken(cursor, &cursor, &token))
    {
      fprintf(stderr, "Failed to parse token at char %lu. Remainder: \"%s\"\n", cursor.index, SC_Cursor(cursor));
      fprintf(stderr, "%s\n", cursor.source);
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
