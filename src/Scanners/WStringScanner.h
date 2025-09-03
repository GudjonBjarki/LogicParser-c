#pragma once

#include <wchar.h>
#include <stdbool.h>
#include <sys/types.h>

typedef struct s_WStringCursor
{
  const wchar_t* source;
  size_t index;
  size_t length;
} WStringCursor;

typedef bool (*WCharPredicate)(wchar_t);

WStringCursor WSC_Create(const wchar_t* source);
bool WSC_Done(const WStringCursor sc);
wchar_t WSC_Peek(const WStringCursor sc);
WStringCursor WSC_Step(const WStringCursor sc, size_t n);

bool WSS_Char(const WStringCursor sc, wchar_t c, WStringCursor* out_sc);
bool WSS_CharIf(const WStringCursor sc, WCharPredicate predicate, WStringCursor* out_sc, wchar_t* out_c);
bool WSS_String(const WStringCursor sc, const wchar_t* s, WStringCursor* out_sc);
ssize_t WSS_Span(const WStringCursor sc, WCharPredicate predicate, WStringCursor* out_sc, wchar_t** out_s);

