#include "EnvEntry.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Utils/StringUtils.h"

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
  char* keyClone = CloneString(key);
  if (!keyClone)
  {
    // @TODO Better error handling.
    fprintf(stderr, "Failed to clone string for env entry.\n");
    return (EnvEntry){ .key=NULL, .value=false };
  }

  return (EnvEntry)
  {
    .key = keyClone,
    .value = value
  };
}

void ENVE_Free(EnvEntry* e)
{
  free((void*)e->key);
}

