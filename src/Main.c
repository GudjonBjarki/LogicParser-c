#include <stdio.h>
#include <stdlib.h>

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

#include "Interpreter/Env.h"
#include "Interpreter/ExpressionEvaluator.h"

int main()
{
  char* source = "(a & b)";
  Token* tokens;
  ssize_t res = Tokenize(source, &tokens);
  if (res == -1)
  {
    fprintf(stderr, "Failed to tokenize source. \"%s\"\n", source);
    return 1;
  }

  size_t numTokens = (size_t)res;
  Expression* tree;
  if (!Parse(tokens, numTokens, &tree))
  {
    fprintf(stderr, "Failed to parse tokens\n");
    FreeTokenArray(tokens, numTokens);
    return 1;
  }
  FreeTokenArray(tokens, numTokens);

  Environment env = ENV_Make();
  ENV_Set(&env, "a", true);
  ENV_Set(&env, "b", true);
  
  printf("Expression: ");
  PrettyPrintExpression(tree);
  printf("\n");
  
  PrettyPrintEnv(&env);

  printf("Evaluates to: %d\n", EvaluateExpression(&env, tree));
  
  EX_Free(tree);
  ENV_Free(&env);
  return 0;
}

