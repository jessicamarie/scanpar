//Type and struct Definitions
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
  int isArray;
};

struct term{
  string literal;
  type t;
};

struct operation{
  string opr;
  struct term *term1;
  struct term *term2;
};

struct expression{
  assignment eq;
  struct identifier *id;
  struct operation *op;
};

struct statement{
  string cdtlStatement;
  string condition;
  struct statement *elses;
};

struct conditional{
  struct statement *ifs;
};

struct expression* newExpression(string arr[][100], int idx);
struct identifier* newIdentifier(string arr[][100], int idx);
struct operation* newOperation(string arr[][100], int idx);
struct conditional* newConditional(string *arr);
void printExpression(struct expression *expression_node);


// Function Prototypes
int isArray(string *arr);
int isAssignment(string *arr);
int isExpression(string arr[][100], int idx);
int isOp(string operator);
int isConditional(string *arr);
void parse(char *lineData[LIMIT][MAXTOKS], int tokensInLine[LIMIT], int lineNumGlobal);
//void readData();

