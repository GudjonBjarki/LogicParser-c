#pragma once

#include "Parser/AST.h"
#include "Env.h"

bool EvaluateExpression(Environment* env, Expression* expr);
