#include <stdio.h>
#include <stdlib.h>

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

#include "Interpreter/ExpressionEvaluator.h"

int main()
{
  char* source = "(1 = a)";
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
  
  printf("Expression: ");
  PrettyPrintExpression(tree);
  printf("\n");

  printf("Evaluates to: %d\n", EvaluateExpression(tree));

  EX_Free(tree);
  return 0;
}

