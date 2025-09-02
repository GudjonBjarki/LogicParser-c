#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

#include "Interpreter/TruthTable.h"



void ThruthTableFromSource(char* source)
{
  printf("Source: %s\n", source);

  Token* tokens;
  ssize_t res = Tokenize(source, &tokens);
  if (res == -1)
  {
    fprintf(stderr, "Failed to tokenize source. \"%s\"\n", source);
    return;
  }

  size_t numTokens = (size_t)res;
  PrettyPrintTokens(tokens, numTokens);

  Expression* tree;
  if (!Parse(tokens, numTokens, &tree))
  {
    fprintf(stderr, "Failed to parse tokens\n");
    FreeTokenArray(tokens, numTokens);
    return;
  }
  FreeTokenArray(tokens, numTokens);

  PrettyPrintExpression(tree); printf("\n");

  EvaluateTruthTable(tree);

  EX_Free(tree);
}


bool ReadLine(char* dst, int maxLength)
{
  char* ret = fgets(dst, maxLength, stdin);
  if (ret == NULL) return false;
  dst[strcspn(dst, "\n")] = '\0';
  return true;
}

int main()
{
  char source[1024];
  while (ReadLine(source, sizeof(source)))
  {
    if (strlen(source) == 0) break;
    ThruthTableFromSource(source);
  }
  return 0;
}

