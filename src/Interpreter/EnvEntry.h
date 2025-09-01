#pragma once

#include <stdbool.h>

typedef struct s_EnvEntry
{
  const char* key;
  bool value;
} EnvEntry;

EnvEntry ENVE_Make(const char* key, bool value);
EnvEntry ENVE_MakeCopy(const char* key, bool value);

void ENVE_Free(EnvEntry* e);

