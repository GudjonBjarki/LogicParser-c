#pragma once

#include <sys/types.h>

#include "Token.h"

ssize_t Tokenize(char* source, Token** out_tokens);

void FreeTokenArray(Token* tokens, size_t numTokens);
