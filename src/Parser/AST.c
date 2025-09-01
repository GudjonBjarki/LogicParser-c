#include "AST.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Utils/StringUtils.h"


Expression* AllocateExpression()
{
  Expression* ex = malloc(sizeof(Expression));
  if (!ex)
  {
    fprintf(stderr, "Failed to allocate %zu bytes for new expression\n", sizeof(Expression));
    return NULL;
  }
  return ex;
}



void EX_Free(Expression* ex)
{
  switch (ex->type)
  {
    case EXPR_BINARY_OP:
      EX_Free(ex->as.binaryOp.left);
      EX_Free(ex->as.binaryOp.right);
      break; 

    case EXPR_PROP:
      free(ex->as.proposition);
      break;

    default: break;
  }

  free(ex);
}

Expression* EX_NewConst(bool v)
{
  Expression* ex = AllocateExpression();
  if (!ex) return NULL;

  ex->type = EXPR_CONSTANT;
  ex->as.constant = v;

  return ex;
}

Expression* EX_NewBinop(Operator op, Expression* left, Expression* right)
{
  Expression* ex = AllocateExpression();
  if (!ex) return NULL;

  ex->type = EXPR_BINARY_OP;
  ex->as.binaryOp.operation = op;
  ex->as.binaryOp.left = left;
  ex->as.binaryOp.right = right;

  return ex;
}

Expression* EX_NewProp(char* s)
{
  Expression* ex = AllocateExpression();
  if (!ex) return NULL;

  ex->type = EXPR_PROP;
  ex->as.proposition = s;
  
  return ex;
}

Expression* EX_NewPropCopy(char* s)
{
  char* sClone = CloneString(s);
  if (!sClone)
  {
    fprintf(stderr, "Failed to clone string for proposition expression\n");
    return NULL;
  }

  Expression* ex = EX_NewProp(sClone);
  if (!ex)
  {
    free(sClone);
    return NULL;
  }
  
  return ex;
}

void PrettyPrintExpression(Expression* ex)
{
  switch (ex->type)
  {
    case EXPR_CONSTANT:
      printf("%d", ex->as.constant);
      break;

    case EXPR_BINARY_OP:
      printf("(");
      PrettyPrintExpression(ex->as.binaryOp.left);
      printf(" %s ", OperatorToString(ex->as.binaryOp.operation));
      PrettyPrintExpression(ex->as.binaryOp.right);
      printf(")");
      break;

    case EXPR_PROP:
      printf("%s", ex->as.proposition);
      break;
  }
}
