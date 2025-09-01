#include "StringUtils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


char* CloneString(const char* s)
{
  size_t bufferSize = strlen(s) + 1;
  char* buffer = malloc(bufferSize);
  if (buffer == NULL)
  {
    fprintf(stderr, "Failed to allocate %zu bytes to clone string \"%s\"\n", bufferSize, s);
    return NULL;
  }

  strcpy(buffer, s);

  return buffer;
}
