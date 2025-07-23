#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>


typedef enum {
    KEYWORD, IDENTIFIER, NUMBER, OPERATOR, DELIMITER, STRING_LITERAL, COMMENT, UNKNOWN, ERROR
} TokenType;


extern const char *keywords[];    
extern const char operators[];
extern const char delimiters[];

void lexer(FILE *);
int iskeyword(const char *);
void print_token(TokenType, char *);
int isoperator(char);
int isdelimeter(char);