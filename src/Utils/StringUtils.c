#include "StringUtils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


char* CloneString(const char* s)
{
  size_t bufferSize = strlen(s) + 1;
  char* buffer = malloc(bufferSize * sizeof(char));
  if (!buffer)
  {
    fprintf(stderr, "Failed to allocate %zu bytes to clone string \"%s\"\n", bufferSize, s);
    return NULL;
  }

  strcpy(buffer, s);

  return buffer;
}

wchar_t* CloneWString(const wchar_t* s)
{
  size_t bufferSize = wcslen(s) + 1;
  wchar_t* buffer = malloc(bufferSize * sizeof(wchar_t));
  if (!buffer)
  {
    fprintf(stderr, "Failed to allocate %zu bytes to clone string \"%ls\"\n", bufferSize, s);
    return NULL;
  }

  wcscpy(buffer, s);

  return buffer;
}
