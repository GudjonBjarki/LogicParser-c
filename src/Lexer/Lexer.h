#pragma once

#include <sys/types.h>
#include <wchar.h>

#include "Token.h"

ssize_t Tokenize(wchar_t* source, Token** out_tokens);

void FreeTokenArray(Token* tokens, size_t numTokens);
