#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

#include "token.h"
#include "parse.h"

// Grammar Definitions are now in parse.h


void parse(char *lineData[LIMIT][MAXTOKS], int tokensInLine[LIMIT], int lineNumGlobal){
  int k = 0, i = 0;
  //this was for debugging purposes:
  //printf("lng = %d\n", lineNumGlobal);
  //for (k = 1; k < lineNumGlobal; k++){
    //printf("TokensinlinePARSER %d = %d\n", k, tokensInLine[k]);
    //printf("fuck = %s\n\n", lineData[k][0]);
    //tokensInLineScan[k] = tokensInLine[k];
  //}


  printf("Begin Parsing\n");
  char *thisLine[MAXTOKS];
  thisLine[0] = lineData[8][0];
  thisLine[1] = lineData[8][1];
  printf("equality = %d\n", strcmp(thisLine[0], "="));
  printf("equality = %d\n", strcmp(thisLine[1], "="));
  for (k = 1; k < lineNumGlobal; k++){
    if(tokensInLine[k] > 3) {
      //printf("tokens in line %d = %d\n",k, tokensInLine[k]);
      //printf("thisLine = {");
      for (i = 0; i < tokensInLine[k]; i++){
	thisLine[i] = lineData[k][i];
	//	printf("\"%s\", ", thisLine[i]);

      }
      //printf("}\n");
      //Right now, this line /should/ probably have the same format as your array[6] did I THINK. But isAssignment
      //etc aren't functioning / printing these debugging statements. At least line 8 in test.c should be an assignment!
      if (isAssignment(thisLine)){
	printf("assignment\n");
	if (isExpression(thisLine)){
	  newExpression(thisLine);
	  printf("expression\n");
	}
	else{
	  newIdentifier(thisLine);
	  printf("identifier\n");
	}
      }
      else if (isConditional(thisLine)){
	newConditional(thisLine);
	printf("conditional\n");
	}
    }
  }

}

main(){
 
  string array[6] = {"a", "=", "1", "+", "2", ";"};
  newExpression(array);
}

// Main Function
/*int main(int argc, string argv[]){
  
  
  string array[6] = {"a", "=", "1", "+", "2", ";"}; // Example input 
  printf("%s %s %s %s %s %s \n", array[0], array[1], array[2], array[3], array[4], array[5]);
  //int i;
  //printf("%d\n", tokensInLine[8]);
  //for (i=0;i<tokensInLine[8];i++){
  //  printf("%s ", linePositions[8][i]);
  //}
  /*  int k = 0;
  printf("%d\n", lineNumGlobal);
  for (k = 0; k < lineNumGlobal; k++){
    printf("Tokensinline %d = %d\n", k, tokensInLine[k]);
    //tokensInLineScan[k] = tokensInLine[k];
    }
  //  printf
  if (isAssignment(array)){
    if (isExpression(array)){
      newExpression(array);
    }
    else{
      newIdentifier(array);
    }
  }
  else if (isConditional(array)){
    newConditional(array);
  }
}
*/
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

int isExpression(char **arr){
  return isOp(arr[3]);
}

int isOp(string operator){
  return operator == "+" || operator == "-" || operator == "*" || operator == "/";
}

int isConditional(char **arr){
  return arr[0] == "if";
}

struct expression* newExpression(string *arr){
  struct expression* eq_node = malloc(sizeof(struct expression)); 
  eq_node->eq = equals; 
  struct identifier* i = newIdentifier(arr);
  struct operation* p = newOperation(arr);
  eq_node->id = i;
  eq_node->op = p;
  
  printExpression(eq_node);
}

void printExpression(struct expression* exp){
  printf("assignment\n");
  printf("  /  |  \\\n");
  printf(" %s   =   %s\n",exp->id->name, exp->op->opr);
  printf("        / \\\n");
  printf("       %s   %s\n", exp->op->term1->literal, exp->op->term2->literal);

}

struct identifier* newIdentifier(string *arr){
  struct identifier* id_node = malloc(sizeof (struct identifier)); 
  id_node->name = arr[0];
  id_node->t;
}

struct operation* newOperation(string *arr){
  struct operation* op_node = malloc(sizeof(struct operation));
  struct term* term_node1 = malloc(sizeof(struct term));
  struct term* term_node2 = malloc(sizeof(struct term));
  op_node->opr= arr[3];
  term_node1->literal = arr[2];
  term_node2->literal = arr[4];  
  op_node->term1 = term_node1;
  op_node->term2 = term_node2;
}


struct conditional* newConditional(string *arr){
  struct conditional* cond_node = malloc(sizeof(struct conditional));
  struct statement* if_node = malloc(sizeof(struct statement));
  struct statement* else_node = malloc(sizeof(struct statement));  
}
 
