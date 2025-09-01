#include "EnvEntry.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

EnvEntry ENVE_Make(const char* key, bool value)
{
  return (EnvEntry)
  {
    .key = key,
    .value = value,
  };
}

EnvEntry ENVE_MakeCopy(const char* key, bool value)
{
  const size_t bufferSize = strlen(key) + 1;
  char* buffer = malloc(bufferSize);

  if (!buffer)
  {
    fprintf(stderr, "Failed to allocate %zu bytes for environment entry key\n", bufferSize);
    return (EnvEntry){.key=NULL, .value=false};
  }
  
  strcpy(buffer, key);

  return (EnvEntry)
  {
    .key = buffer,
    .value = value
  };
}

void ENVE_Free(EnvEntry* e)
{
  free((void*)e->key);
}

