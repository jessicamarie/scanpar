#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

#include "token.h"
#include "sysdef.h"
#include "scan.h"

// Grammar Definitions

typedef char* string;

typedef enum{
  equals
} assignment;

typedef enum{
  Int, 
  Float
} type;

struct identifier{
  string name;  
  type t;
};

struct term{
  string literal;
  type t;
};

struct operation{
  string op;
  struct term *term1;
  struct term *term2;
};

struct expression{
  assignment eq;
  struct identifier *id;
  struct operation *op;
};

// Function Prototypes
int isArray(string *arr);
int isAssignment(string *arr);
int isExpression(string *arr);
int isOp(string operator);

struct expression* newExpression(string *arr);
struct identifier* newIdentifier(string *arr);
struct operation* newOperation(string *arr);

// Main Function
int main(int argc, string argv[]){
  
  
  string array[6] = {"a", "=", "1", "+", "2", ";"}; // Example input 
  if (isAssignment(array)){
    if (isExpression(array)){
      newExpression(array);
    }
  }

}

//Function definitions

int isArray(char **arr){
  return arr[1] == "[";
}

int isAssignment(char **arr){
  return arr[1] == "=" || arr[4] == "=";
}

int isExpression(char **arr){
  return isOp(arr[3]);
}

int isOp(string operator){
  return operator == "+" || operator == "-" || operator == "*" || operator == "/";
}

struct expression* newExpression(string *arr){
  struct expression* eq_node = malloc(sizeof(struct expression)); 
  eq_node->eq = equals; 
  struct identifier* i = newIdentifier(arr);
  struct operation* p = newOperation(arr);
}

struct identifier* newIdentifier(string *arr){
  struct identifier* id_node = malloc(sizeof (struct identifier));
  if (!isArray(arr)){   
  
  }
  else{  
  
  } 
  id_node->name = arr[0];
  id_node->t;
}

struct operation* newOperation(string *arr){
  struct operation* op_node = malloc(sizeof(struct operation));
  struct term* term_node1 = malloc(sizeof(struct term));
  struct term* term_node2 = malloc(sizeof(struct term));
  op_node->op = arr[3];
  op_node->term1 = term_node1;
  op_node->term2 = term_node2;
  term_node1->literal = arr[2];
  term_node2->literal = arr[4];
  op_node->term1 = term_node1;  
}  
