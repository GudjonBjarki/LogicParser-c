#pragma once

#include <stddef.h>
#include <wchar.h>

#include "Utils/DynamicBuffer.h"


typedef struct s_Environment
{
  DynamicBuffer entries;
} Environment;


Environment ENV_Make();
void ENV_Free(Environment* env);

void ENV_Set(Environment* env, const wchar_t* key, bool value);
bool ENV_Get(Environment* env, const wchar_t* key);

void PrettyPrintEnv(Environment* env);
