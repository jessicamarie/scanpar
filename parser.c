#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

#include "token.h"
#include "parse.h"

// Grammar Definitions are now in parse.h


void parse(char *lineData[LIMIT][MAXTOKS], int tokensInLine[LIMIT], int lineNumGlobal){
  int k = 0, l = 0;
  for(l=0; l < LIMIT; l++){
    for(k=0; k < tokensInLine[l]; k++){
      //printf("%s\n", lineData[l][k]);
      if (isExpression(lineData, l)){
        newExpression(lineData, l);  
      }
    }
  }
}

//Function definitions
int isArray(char **arr){
  return (!strcmp(arr[1], "[") && !strcmp(arr[3], "]"));
}
int isAssignment(char **arr){
  if(!strcmp(arr[1], "=")){
    return 1;
  }
  return 0;
}
int isExpression(char *arr[][100], int idx){
  printf("%s", arr[idx][0]);
  return isOp(arr[idx][3]);
}
int isOp(string operator){
  return strcmp(operator, "+") || strcmp(operator, "-") || strcmp(operator,"*") || strcmp(operator, "/");
}
int isConditional(char **arr){
  return arr[0] == "if";
}
struct expression* newExpression(string arr[][100], int idx){
  struct expression* eq_node = malloc(sizeof(struct expression)); 
  eq_node->eq = equals; 
  struct identifier* i = newIdentifier(arr, idx);
  struct operation* p = newOperation(arr, idx);
  eq_node->id = i;
  eq_node->op = p;
  
  //printExpression(eq_node);
}

void printExpression(struct expression* exp){
  printf("assignment\n");
  printf("  /  |  \\\n");
  printf(" %s   =   %s\n",exp->id->name, exp->op->opr);
  printf("        / \\\n");
  printf("       %s   %s\n", exp->op->term1->literal, exp->op->term2->literal);

}

struct identifier* newIdentifier(string arr[][100], int idx){
  struct identifier* id_node = malloc(sizeof (struct identifier)); 
  id_node->name = arr[idx][0];
  id_node->t;
  return id_node;
}

struct operation* newOperation(string arr[][100], int idx){
  struct operation* op_node = malloc(sizeof(struct operation));
  struct term* term_node1 = malloc(sizeof(struct term));
  struct term* term_node2 = malloc(sizeof(struct term));
  op_node->opr= arr[idx][3];
  term_node1->literal = arr[idx][2];
  term_node2->literal = arr[idx][4];  
  op_node->term1 = term_node1;
  op_node->term2 = term_node2;
  return op_node;
}


struct conditional* newConditional(string *arr){
  struct conditional* cond_node = malloc(sizeof(struct conditional));
  struct statement* if_node = malloc(sizeof(struct statement));
  struct statement* else_node = malloc(sizeof(struct statement));  
}
 
