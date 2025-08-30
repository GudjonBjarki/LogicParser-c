#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>

typedef struct s_StringCursor
{
  char*   source;
  size_t  index;
  size_t  length;
} StringCursor;


typedef bool (*CharPredicate)(char);

// String cursor functions.
StringCursor SC_Create(char* source);
bool SC_Done(const StringCursor sc);
char SC_Peek(const StringCursor sc);
char* SC_Cursor(const StringCursor sc);
StringCursor SC_Step(const StringCursor sc, size_t n);

// String scanner functions.
bool SS_Char(const StringCursor sc, char c, StringCursor* out_sp);
bool SS_CharIf(const StringCursor sc, CharPredicate predicate, StringCursor* out_sp, char* out_c);
bool SS_String(const StringCursor sc, char* s, StringCursor* out_sp);
ssize_t SS_Span(const StringCursor sc, CharPredicate predicate, StringCursor* out_sp, char** out_s);

