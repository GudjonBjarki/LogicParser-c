#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

#include "Interpreter/TruthTable.h"



void ThruthTableFromSource(wchar_t* source)
{
  printf("Source: %ls\n", source);

  Token* tokens;
  ssize_t res = Tokenize(source, &tokens);
  if (res == -1)
  {
    fprintf(stderr, "Failed to tokenize source.\n");
    return;
  }

  size_t numTokens = (size_t)res;
  printf("Tokens: "); PrettyPrintTokens(tokens, numTokens);

  Expression* tree;
  if (!Parse(tokens, numTokens, &tree))
  {
    fprintf(stderr, "Failed to parse tokens\n");
    FreeTokenArray(tokens, numTokens);
    return;
  }
  FreeTokenArray(tokens, numTokens);

  printf("Parsed expression: "); PrettyPrintExpression(tree); printf("\n");

  EvaluateTruthTable(tree);

  EX_Free(tree);
}


bool ReadLine(wchar_t* dst, int maxLength)
{
    wchar_t* ret = fgetws(dst, maxLength, stdin);
    if (ret == NULL) return false;

    size_t len = wcslen(dst);
    if (len > 0 && dst[len - 1] == L'\n') {
        dst[len - 1] = L'\0';
    }

    return true;
}

int main()
{
  setlocale(LC_ALL, "");

  wchar_t source[1024];
  while (ReadLine(source, sizeof(source)))
  {
    if (wcslen(source) == 0) break;
    ThruthTableFromSource(source);
  }
  return 0;
}

