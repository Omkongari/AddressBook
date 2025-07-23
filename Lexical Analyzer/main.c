#include "main.h"

int main()
{
    FILE *fptr = fopen("input.txt","r");
    if(!fptr)
    {
        printf("Provide input file\n");
        fclose(fptr);
        return 0;
    }
    lexer(fptr);
    fclose(fptr);

    return 0;
}

