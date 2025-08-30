#pragma once

#include "AST.h"
#include "Lexer/Token.h"

bool Parse(Token* tokens, size_t numTokens, Expression** out_expr);
