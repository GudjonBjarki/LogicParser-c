#include "TruthTable.h"

#include <string.h>
#include <stdio.h>

#include "Utils/DynamicBuffer.h"
#include "ExpressionEvaluator.h"
#include "Env.h"


void FindPropositionsRec(Expression* expr, DynamicBuffer* propBuffer)
{
  switch (expr->type)
  {
    case EXPR_PROP:
      char* prop = expr->as.proposition;

      for (size_t i = 0; i < propBuffer->length; i++)
      {
        const char* checkProp = *(char**)DB_Get(*propBuffer, i);

        if (strcmp(prop, checkProp) == 0)
          return;
      }
      DB_Append(propBuffer, &expr->as.proposition);
      break;
  
    case EXPR_BINARY_OP:
      FindPropositionsRec(expr->as.binaryOp.left, propBuffer);
      FindPropositionsRec(expr->as.binaryOp.right, propBuffer);
      break;

    default:
      break;
  }
}

size_t FindPropositions(Expression* expr, char*** out_props)
{
  DynamicBuffer buffer = DB_Create(sizeof(char**), 8);
  FindPropositionsRec(expr, &buffer); 

  const size_t numProps =  buffer.length;
  *out_props = DB_Release(&buffer);

  return numProps;
}


void EvaluateTruthTable(Expression* expr)
{
  char** props;
  size_t numProps = FindPropositions(expr, &props);

  Environment env = ENV_Make();
  if (numProps == 0)
  {
    printf("Expression contains no props.\n");
    printf("Statement evaluates to: %d\n", EvaluateExpression(&env, expr));
    goto CLEANUP;
  }

  size_t numIterations = 1 << numProps;
  for (long i = (long)numIterations-1; i >= 0; i--)
  {
    for (size_t j = 0; j < numProps; j++)
    {
      char* prop = props[j];
      bool value = (bool)(i & (1 << (numProps - 1 - j)));

      printf("%s: %d, ", prop, value);
      ENV_Set(&env, props[j], value);
    }

    printf(" -> %d\n", EvaluateExpression(&env, expr));
  }
  
CLEANUP:
  ENV_Free(&env);
  free(props);
}

