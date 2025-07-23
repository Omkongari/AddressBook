#include "main.h"

int iskeyword(const char *token)
{
    for(int i=0; keywords[i] ; i++){
        if(strcmp(token,keywords[i]) == 0){
            return 1;
        }
    }
    return 0;
}

void print_token(TokenType type,char *token)
{
    const char *types[] = {"KEYWORD", "IDENTIFIER", "NUMBER", "OPERATOR", "DELIMITER","STRING_LITERAL", "COMMENT", "UNKNOWN","ERROR"};

    printf("Token: %-15s Lexeme : %s\n",types[type],token);

}

int isoperator(char check)
{
    if((strchr(operators,check)) != NULL)return 1;
    else return 0;
}

int isdelimeter(char ch)
{
    if((strchr(delimiters,ch)) != NULL)return 1;
    else return 0;
}

