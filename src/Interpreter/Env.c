#include "Env.h"

#include <string.h>
#include <stdio.h>

#include "EnvEntry.h"

EnvEntry* FetchEntry(Environment* env, const wchar_t* key)
{
  for (size_t i = 0; i < env->entries.length; i++)
  {
    EnvEntry* entry = DB_Get(env->entries, i);
    if (wcscmp(key, entry->key) == 0)
    {
      return entry;
    }
  }

  return NULL;
}



Environment ENV_Make()
{
  return (Environment)
  {
    .entries = DB_Create(sizeof(EnvEntry), 4),
  };
}

void ENV_Free(Environment* env)
{
  for (size_t i = 0; i < env->entries.length; i++)
  {
    ENVE_Free((EnvEntry*)DB_Get(env->entries, i));
  }
  DB_Free(&env->entries);
}


void ENV_Set(Environment* env, const wchar_t* key, bool value)
{
  EnvEntry* existing = FetchEntry(env, key);
  if (existing != NULL)
  {
    existing->value = value;
    return;
  }

  EnvEntry entry = ENVE_MakeCopy(key, value);
  DB_Append(&env->entries, &entry);
}

bool ENV_Get(Environment* env, const wchar_t* key)
{
   EnvEntry* entry = FetchEntry(env, key);
   if (!entry)
   {
     fprintf(stderr, "Attempting to fetch entry not contained in env. Key: %ls\n", key);
     return false;
   }

   return entry->value;
}

void PrettyPrintEnv(Environment* env)
{
  printf("Environment:\n");
  for (size_t i = 0; i < env->entries.length; i++)
  {
    EnvEntry* e = DB_Get(env->entries, i);
    printf("  %ls: %d\n", e->key, e->value);
  }
}
