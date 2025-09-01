#pragma once

#include <stddef.h>

#include "EnvEntry.h"
#include "Utils/DynamicBuffer.h"


typedef struct s_Environment
{
  DynamicBuffer entries;
} Environment;


Environment ENV_Make();
void ENV_Free(Environment* env);

void ENV_Set(Environment* env, const char* key, bool value);
bool ENV_Get(Environment* env, const char* key);

void PrettyPrintEnv(Environment* env);
