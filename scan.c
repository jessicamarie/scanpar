#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

#include "token.h"
#include "sysdef.h"
#include "scan.h"
#include "parse.h"

int tokensInLineScan[LIMIT];

int eligibleChar(char c) {
	if (c == '.' || c == '(' || c == ')' || c == ',' || c == '{' || c == '}' ||
        c == ';' || c == '[' || c == ']' || c == '"' || c == '\\' || c == '_' ||
		c == ':' || c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || 
		c == '=' || c == '<' || c == '>' || c == '!' 
		|| c == '#') {
		return 1;
	} else 
		return 0;
}

int eligibleRelationalOp(char c) {
	int result = 0; // false
	if (c == '=' || c == '<' || c == '>' || c == '!') {
		result = 1;
	}
	return result;	
}

int eligibleOp(char c) {
	 int i;
	 int result = 0; // false
	 int length = sizeof(otherOperators) / sizeof(otherOperators[0]);
	 for (i = 0; i < length; i++) {
		if (otherOperators[i] == c) 
			result = 1;
	 }
	 return result;
}

int eligibleDelimiter(char c) {
	 int i;
	 int result = 0; // false
	 int length = sizeof(delimiters) / sizeof(delimiters[0]);
	 for (i = 0; i < length; i++) {
		if (delimiters[i] == c) 
			result = 1;
	 }
	 return result;
}

int eligibleKeyword(char *str) {
	int i;
	int result = 0; // false
	int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
	for (i = 0; i < numKeywords; i++) {
		if (!strcasecmp(keywords[i], str))
			result = 1;
	}
	return result;
}

void splitWords() {
	int i;
	for (i = 0; i < wordi; i++) {
		if (eligibleKeyword(words[i])) {
			strcpy(keys[keyi], words[i]);
			keyLineNums[keyi] =  wordLineNums[i];
			keyi++;
		} else {
			strcpy(idens[ideni], words[i]);
			idenLineNums[ideni] = wordLineNums[i];
			ideni++;

		}
	}
}

void printOtherOperators() {
	int i;
	for (i = 0; i < otherOpi; i++) {
		printf("%s \t (line #%d) \n", otherOps[i], otherOpLineNums[i]);
	}
}

void printDelimiters() {
	int i;
	for (i = 0; i < delimi; i++) {
		printf("%s \t (line #%d) \n", delims[i], delimLineNums[i]);
	}
}

void printRelationalOperators() {
	int i;
	for (i = 0; i < relOpi; i++) {
		printf("%s \t (line #%d) \n", relOps[i], relOpLineNums[i]);
	}
}

void printWords() {
	// printf("Num of words = %d \n", wordi);
	int i;
	for (i = 0; i < wordi; i++) {
		printf("%s \t (line #%d) \n", words[i], wordLineNums[i]);
	}
}

void printKeywords() {
	int i;
	for (i = 0; i < keyi; i++) {
		printf("%s \t (line #%d) \n", keys[i], keyLineNums[i]);
	}
}

void printNumbers() {
	int i;
	for (i = 0; i < numi; i++) {
		printf("%s \t (line #%d) \n", nums[i], numLineNums[i]);
	}
}

void printIdentifiers() {
	int i;
	for (i = 0; i < ideni; i++) {
		printf("%s \t (line #%d)\n", idens[i], idenLineNums[i]);
	}
}

void printFile(FILE *fp){
    char c;
    printf("Beginning of the C file:\n");
    c = fgetc(fp);
    while(c != EOF){
        printf("%c", c);
        c = fgetc(fp); 
    }
    printf("\nEnd Of File\n");
}

void printLinePositions() {
  int i, j;
  //	int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
  for (i = 1; i < lineNumGlobal; i++) {
    for (j = 0; j < tokensInLine[i]; j++) {
      printf("%s ", linePositions[i][j]);
    }
    printf("\n");
  }
}
 
 void printSummary() {
	printf("----------BEGIN SUMMARY---------- \n");
	
	printf("***Note format: token (line #) \n\n");

	printf("Total %d KEYWORDS found are: \n", keyi);
	printKeywords();
	printf("***/END KEYWORD SUMMARY*** \n");

	printf("\nTotal %d IDENTIFIERS found are: \n", ideni);
	printIdentifiers();	
	printf("***/END IDENTIFIER SUMMARY*** \n");

	printf("\nTotal %d NUMBERS found are: \n", numi);
	printNumbers();	
	printf("***/END NUMBER SUMMARY*** \n");

	printf("\nTotal %d DELIMITERS found are: \n", delimi);
	printDelimiters();	
	printf("***/END DELIMITER SUMMARY*** \n");

	printf("\nTotal %d RELATIONAL OPERATORS found are: \n", relOpi);
	printRelationalOperators();	
	printf("***/END RELATIONAL OPERATOR SUMMARY*** \n");

	printf("\nTotal %d OTHER OPERATORS found are: \n", otherOpi);
	printOtherOperators();	
	printf("***/END OTHER OPERATOR SUMMARY*** \n");

	printf("\n----------/END SUMMARY----------- \n");
	printf("\n----------/BEGIN LINE POSITION PRINTOUT----------- \n");
	//printf("LNG: %d || tIL = %d || linePositions[1][1] = %s\n", lineNumGlobal, tokensInLine[1], (char *)linePositions[1][1]); 
	printLinePositions();
	printf("\n----------/END LINE POSITION PRINTOUT----------- \n");
    }

TokenType getToken(FILE *fp){
  int lineNum = 1, // line number 
      ccount = 0, // character count for per word (greedy)
      valid = 1; // valid bit is true by default
 	//       check = 0; // check bit is false by default   
    char c, temp[MAX];

    while((c = fgetc(fp)) != EOF){
        // Initial check if file is invalid -- file type, invalid characters etc 
            // New line 
            if(c == '\n'){
                lineNum++; 
            }

            // Comment line 
            if(c == '/'){
                if(fgetc(fp) == '/'){
                    while((c=fgetc(fp)) != '\n') {}
                    lineNum++;
                }
            }

            // Check for number, characters, operators, space 
            if(isalnum(c)){ //Check if c is alphanumeric
                temp[ccount] = c; // this does not handle array-out-of-bound 
                ccount++;
                if(ccount > MAX){
                    printf("Word '%s' on line %d is too long (>= 16 characters).\n", temp, lineNum);
                    exit(EXIT_FAILURE);
                }
            } else if (isspace(c) || eligibleChar(c)) { //Check if c is a space or a symbol
                ccount = 0;
            } else {
                printf("Invalid character '%c' at line %d.\n", c, lineNum);
                valid = 0;
                exit(EXIT_FAILURE);
            }
    } //End of initial check

    rewind(fp); //rewind the file pointer so we can go through the file again
    lineNum = 1; //reset the lineNum
    
    while((c = fgetc(fp)) != EOF){ // Second scan of file
      if (c == '\n') {
	tokensInLine[lineNum] = pos;
	//linePositions[lineNum++][pos] = '\n';
	lineNum++;
	pos = 0;
	continue;
      }
      
      // Ignore comment starting with // to the end of line
      if (c == '/') {
	if (fgetc(fp) == '/') {
	  while ((c = fgetc(fp)) != '\n') {}
	  tokensInLine[lineNum] = pos;
	  lineNum++;
	  pos = 0;
	} else
	  fseek(fp, -1, SEEK_CUR);
      }
      
      if (isalpha(c) || c == '_') { // Check if c is alphnumeric
	words[wordi][wordj++] = c;	
	while (isalpha(c = fgetc(fp))) { //continue seeking and adding to this word until a non-alpha character is reached
	  words[wordi][wordj++] = c;	
	}
	words[wordi][wordj] = '\0';	
	wordLineNums[wordi] = lineNum;
	linePositions[lineNum][pos++] = &words[wordi][0];
	wordi++; wordj = 0;	
	fseek(fp, -1, SEEK_CUR); //rewind one so we rescan the non-alpha character the scanner encountered
      } 
      
      else if (isdigit(c)) {
	nums[numi][numj++] = c;
	while (isdigit(c = fgetc(fp))) { //continue seeking and adding to this number until a non-numeric character is reached
	  nums[numi][numj++] = c;
	}
	nums[numi][numj] = '\0';
	numLineNums[numi] = lineNum;
	linePositions[lineNum][pos++] = &nums[numi][0];
	numi++; numj = 0;
	fseek(fp, -1, SEEK_CUR); //rewind one so we rescan the non-numeric character the scanner encountered
      }
      
      else if (ispunct(c) || c == '#') {
	if (eligibleDelimiter(c)) { //'.', '(', ')', ',', '{', '}', ';', '[', ']'
	  delims[delimi][0] = c;
	  delimLineNums[delimi] = lineNum;
	  delims[delimi][1] = '\0';
	  linePositions[lineNum][pos++] = &delims[delimi][0];
	  delimi++;
	} 
	else if (eligibleOp(c)) { //':', '+', '-', '*', '/', '%', '#'
	  otherOps[otherOpi][0] = c;
	  otherOps[otherOpi][1] = '\0';
	  otherOpLineNums[otherOpi] = lineNum;
	  linePositions[lineNum][pos++] = &otherOps[otherOpi][0];
	  otherOpi++;
	}
	else if (eligibleRelationalOp(c)) { //"==", "<", ">", "!=", ">=", "<="
	  if (c == '<' || c == '>' || c == '!') { 
	    char placeholder = c;
	    if ((c = fgetc(fp)) == '=') { //detect "<=", ">=", "!="
	      relOps[relOpi][relOpj++] = placeholder;
	      relOps[relOpi][relOpj++] = c;	
	      relOps[relOpi][relOpj] = '\0';
	      relOpLineNums[relOpi] = lineNum;
	      linePositions[lineNum][pos++] = &relOps[relOpi][0];
	      relOpi++; relOpj = 0;
	    } else if (isspace(c)) {
	      if (placeholder == '>' || placeholder == '<') {
		relOps[relOpi][relOpj++] = placeholder;
		relOps[relOpi][relOpj] = '\0';
		relOpLineNums[relOpi] = lineNum;
		linePositions[lineNum][pos++] = &relOps[relOpi][0];
		relOpi++; relOpj = 0;
		fseek(fp, -1, SEEK_CUR);
	      } else {
		fseek(fp, -1, SEEK_CUR);
	      }
	    } else {
	      fseek(fp, -1, SEEK_CUR);
	    }
	  } else if (c == '=') {
	    if ((c = fgetc(fp)) == '=') {
	      relOps[relOpi][relOpj++] = '=';	
	      relOps[relOpi][relOpj++] = c;	
	      relOps[relOpi][relOpj] = '\0';
	      relOpLineNums[relOpi] = lineNum;
	      linePositions[lineNum][pos++] = &relOps[relOpi][0];
	      relOpi++; relOpj = 0;
	    } else if (isspace(c)) {
	      fseek(fp, -1, SEEK_CUR);
	      otherOps[otherOpi][0] = '=';
	      otherOps[otherOpi][1] = '\0';
	      otherOpLineNums[otherOpi] = lineNum;
	      linePositions[lineNum][pos++] = &otherOps[otherOpi][0];
	      otherOpi++;
	    } else {
	      fseek(fp, -1, SEEK_CUR);
	    }
	  }
	}
      }
    } // end while           
    lineNumGlobal = lineNum;
    splitWords();
    printSummary();
    saveData();
    rewind(fp);
    /*    int k = 0;
    for (k = 0; k < lineNum; k++){
      printf("Tokensinline %d = %d\n", k, tokensInLine[k]);
      tokensInLineScan[k] = tokensInLine[k];
    }
    */
    return EOT; // return token
}

void saveData(){
  FILE *f = fopen("scanoutput.txt", "w");
  if (f == NULL)
    {
      printf("Error opening file!\n");
      exit(1);
    }

  int i, j;
  //	int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
  for (i = 1; i < lineNumGlobal; i++) {
    for (j = 0; j < tokensInLine[i]; j++) {
      fprintf(f, "%s\n", linePositions[i][j]);
    }
    fprintf(f, "\n");
  }
  /* print some text 
  const char *text = "Write this to the file";
  fprintf(f, "Some text: %s\n", text);
  
  /* print integers and floats 
  int i = 1;
  float py = 3.1415927;
  fprintf(f, "Integer: %d, float: %f\n", i, py);
  
  /* printing single chatacters
  char c = 'A';
  fprintf(f, "A character: %c\n", c);
  */
  //  fprintf("EOF");
  fclose(f);

  /*  FILE *fp; 
  char *file; 
  
  // File name 
  file = argv[2]; 
  
  if((fp = fopen(file,"r"))== NULL){
    printf("File does not exist or corrupted.\n");
    exit(EXIT_FAILURE);
  }
  fseek(fp, 0, SEEK_END); // Reset file pointer position -> 0
  //if(ftell(fp) == 0){
  //  printf("File is empty.\n");
  //  exit(EXIT_FAILURE);
  //}
  
  //rewind(fp);
  
  TokenType token = UNDEF; 
  while ((token = getToken(fp)) != EOT) {}
  
  fclose(fp);
  */
  //  return 0;
}

int main(int argc, char *argv[]){
    FILE *fp; 
    char *file; 

    // File name 
    file = argv[1]; 

    if((fp = fopen(file,"r"))== NULL){
        printf("File does not exist or corrupted.\n");
        exit(EXIT_FAILURE);
    }
    fseek(fp, 0, SEEK_END); // Reset file pointer position -> 0
    if(ftell(fp) == 0){
        printf("File is empty.\n");
        exit(EXIT_FAILURE);
    }

    rewind(fp);
    
    TokenType token = UNDEF; 
    while ((token = getToken(fp)) != EOT) {}

    if (argv[2]){
      if (!strcmp(argv[2], "y")){
	parse(linePositions, tokensInLine, lineNumGlobal);
      }
    }
    fclose(fp);
    exit(EXIT_SUCCESS); 
    return 0; // Should never reach here
}
