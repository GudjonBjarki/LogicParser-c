#include "StringScanner.h"

#include <string.h>
#include <stddef.h>

#include "Utils/DynamicBuffer.h"

StringCursor SC_Create(const char* source)
{
  size_t length = strlen(source);
  return (StringCursor)
  {
    .source = source,
    .index = 0,
    .length = length,
  };
}

bool SC_Done(const StringCursor sc)
{
  return sc.index >= sc.length;
}

char SC_Peek(const StringCursor sc)
{
  return SC_Done(sc)
    ? '\0'
    : sc.source[sc.index];
}

const char* SC_Cursor(const StringCursor sc)
{
  return SC_Done(sc)
    ? NULL
    : &sc.source[sc.index];
}

StringCursor SC_Step(const StringCursor sc, size_t n)
{
  size_t newIndex = sc.index + n;
  if (newIndex > sc.length) newIndex = sc.length;
  return (StringCursor){
    .source = sc.source,
    .index = newIndex,
    .length = sc.length
  };
}



bool SS_Char(const StringCursor sc, char c, StringCursor* out_sc)
{
  if (SC_Done(sc)) return false;
  if (SC_Peek(sc) != c) return false;
  if (out_sc) *out_sc = SC_Step(sc, 1);
  return true;
}

bool SS_CharIf(const StringCursor sc, CharPredicate predicate, StringCursor* out_sc, char* out_c)
{
  if (SC_Done(sc)) return false;
  const char c = SC_Peek(sc);

  if (!predicate(c)) return false;
 
  if (out_sc) *out_sc = SC_Step(sc, 1);
  if (out_c) *out_c = c;

  return true;
}

bool SS_String(const StringCursor sc, const char* s, StringCursor* out_sc)
{
  StringCursor bufferParser = sc;

  size_t length = strlen(s);
  for (size_t i = 0; i < length; i++)
  {
    if (!SS_Char(bufferParser, s[i], &bufferParser)) return false;
  }

  if (out_sc) *out_sc = bufferParser;

  return true;
}

ssize_t SS_Span(const StringCursor sc, CharPredicate predicate, StringCursor* out_sc, char** out_s)
{
  StringCursor bufferParser = sc;
  DynamicBuffer charBuffer = DB_Create(sizeof(char), 16);
  
  size_t nRead = 0;
  while (true)
  {
    char c;
    if (!SS_CharIf(bufferParser, predicate, &bufferParser, &c)) break;
    if (out_s && !DB_Append(&charBuffer, &c))
    {
      DB_Free(&charBuffer);
      return -1;
    } 
    nRead++;
  }
  
  if (nRead > 0)
  {
    if (out_s)
    {
      // Weird hack to get a pointer to '\0'
      if (!DB_Append(&charBuffer, &(char){'\0'}))
      {
        DB_Free(&charBuffer);
        return -1;
      }
      *out_s = (char*)DB_Release(&charBuffer);
    }
    if (out_sc) *out_sc = bufferParser;
  }

  return (ssize_t)nRead;
}

