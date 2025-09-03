#pragma once

#include <stdbool.h>
#include <wchar.h>

typedef struct s_EnvEntry
{
  const wchar_t* key;
  bool value;
} EnvEntry;

EnvEntry ENVE_Make(const wchar_t* key, bool value);
EnvEntry ENVE_MakeCopy(const wchar_t* key, bool value);

void ENVE_Free(EnvEntry* e);

