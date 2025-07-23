#include "main.h"

void lexer(FILE *fptr)
{
    char ch, buffer[100];
    int i;

    while((ch = fgetc(fptr)) != EOF)
    {
        if(isspace(ch))continue;

        if(isalpha(ch))
        {
            i=0;
            buffer[i++] = ch;
            while(isalnum(ch = fgetc(fptr)) || ch == '_')
            {
                if(i >= sizeof(buffer) - 1)break;
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            ungetc(ch,fptr);
            if(iskeyword(buffer))
            print_token(KEYWORD,buffer);
            else print_token(IDENTIFIER, buffer);
        }

        else if(isdigit(ch))
        {
            i=0;
            buffer[i++] = ch;
            int invalid = 0;
            while(isalnum(ch = fgetc(fptr)) || ch == '_'){
                if(i >= sizeof(buffer)-1)break;
                buffer[i++] = ch;
                if(isalpha(ch))invalid = 1;
            }
            buffer[i] = '\0';
            if(invalid)
            {
                print_token(ERROR,buffer);
            }
            else{
            ungetc(ch,fptr);
            print_token(NUMBER,buffer);
            }
        }

        else if(ch == '"')
        {
            i=0;
            buffer[i++] = ch;
            int ter = 1;
            while((ch = fgetc(fptr)) != EOF)
            {
                if(ch == '\n')
                {
                    ungetc(ch,fptr);
                    break;
                }

                if(ch == '"')
                {
                    buffer[i++] = ch;
                    ter = 0;
                    break;
                }

                if(i >= sizeof(buffer)-2)break;
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            if(ter)print_token(ERROR,buffer);
            else print_token(STRING_LITERAL,buffer);
            
        }

        else if(ch == '/')
        {
            char next = fgetc(fptr);
            if(next == '/')
            {
                while((ch = fgetc(fptr)) != '\n' && ch != EOF)
                {
                    ;
                }

            }
            else if(next == '*')
            {
                int invalid = 0;

                while(1)
                {
                    ch = fgetc(fptr);
                    if(ch == '*' && fgetc(fptr) == '/')
                    {
                        invalid = 1;
                        break;
                    }
                    if(ch == EOF)break;
                }
                if(!invalid)print_token(ERROR,"Error: Comment Unterminated\n");
            }
            else{
                buffer[0] = ch;
                buffer[1] = '\0';
                ungetc(next,fptr);
                print_token(OPERATOR,buffer);
            }
        }

        else if(isoperator(ch))
        {
            buffer[0] = ch;
            buffer[1] = '\0';
            char next = fgetc(fptr);
            if((ch == '=' || ch == '!' || ch == '>' || ch == '<') && next == '='){
                buffer[1] = next;
                buffer[2] = '\0';
            }
            else{
                ungetc(next,fptr);
            }
            print_token(OPERATOR,buffer);
        }

        else if(isdelimeter(ch))
        {
            buffer[0] = ch;
            buffer[1] = '\0';
            print_token(DELIMITER,buffer);
        }

        else{
            buffer[0] = ch;
            buffer[1] = '\0';
            print_token(UNKNOWN,buffer);
        }
        
    }
}