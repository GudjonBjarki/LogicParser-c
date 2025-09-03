#include "WStringScanner.h"

#include "Utils/DynamicBuffer.h"


WStringCursor WSC_Create(const wchar_t* source)
{
  size_t length = wcslen(source);
  return (WStringCursor)
  {
    .source = source,
    .index = 0,
    .length = length,
  };
}

bool WSC_Done(const WStringCursor sc)
{
  return sc.index >= sc.length;
}

wchar_t WSC_Peek(const WStringCursor sc)
{
  return WSC_Done(sc)
    ? '\0' 
    : sc.source[sc.index];
}

WStringCursor WSC_Step(const WStringCursor sc, size_t n)
{
  size_t newIndex = sc.index + n;
  if (newIndex > sc.length) newIndex = sc.length;
  return (WStringCursor)
  {
    .source = sc.source,
    .length = sc.length,
    .index = newIndex,
  };
}



bool WSS_Char(const WStringCursor sc, wchar_t c, WStringCursor* out_sc)
{
  if (WSC_Done(sc)) return false;
  if (WSC_Peek(sc) != c) return false;
  if (out_sc) *out_sc = WSC_Step(sc, 1);
  return true;
}


bool WSS_CharIf(const WStringCursor sc, WCharPredicate predicate, WStringCursor* out_sc, wchar_t* out_c)
{
  if (WSC_Done(sc)) return false;

  wchar_t c = WSC_Peek(sc);
  if (!predicate(c)) return false;

  if (out_sc) *out_sc = WSC_Step(sc, 1);
  if (out_c) *out_c = c;

  return true;
}

bool WSS_String(const WStringCursor sc, const wchar_t* s, WStringCursor* out_sc)
{
  WStringCursor bufferParser = sc;

  size_t length = wcslen(s);
  for (size_t i = 0; i < length; i++)
  {
    if (!WSS_Char(bufferParser, s[i], &bufferParser)) return false;
  }

  if (out_sc) *out_sc = bufferParser;

  return true;
}

ssize_t WSS_Span(const WStringCursor sc, WCharPredicate predicate, WStringCursor* out_sc, wchar_t** out_s)
{
  WStringCursor bufferParser = sc;
  DynamicBuffer charBuffer = DB_Create(sizeof(wchar_t), 16);
  
  size_t nRead = 0;
  while (true)
  {
    wchar_t c;
    if (!WSS_CharIf(bufferParser, predicate, &bufferParser, &c)) break;
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
      if (!DB_Append(&charBuffer, &(wchar_t){'\0'}))
      {
        DB_Free(&charBuffer);
        return -1;
      }
      *out_s = (wchar_t*)DB_Release(&charBuffer);
    }
    if (out_sc) *out_sc = bufferParser;
  }

  return (ssize_t)nRead;
}

