/*
Name -: Om kongari
Project name-: Arbitrary Precision Calculator
Date -: 27/06/2025
*/

#include<stdio.h>
#include "apc.h"

int main(int argc, char *argv[])
{
    
    

    if(argc != 4)
    {
        printf("Not enough arguments passed\n");
        return FAILURE;
    }
    startend start1, start2, start3;
    start1.head = NULL;
    start1.tail = NULL;
    start2.head = NULL;
    start2.tail = NULL;
    start3.head = NULL;
    start3.tail = NULL;

    if(validate_operand(argv[1], argv[3]) == SUCCESS)
    {
        if(validate_operator(argv[2]) == SUCCESS)
        {
            if(assign_values(&start1, &start2, argv[1], argv[3]) == SUCCESS)
            {
                switch(*argv[2])
                {
                    case '+':
                    {
                        addition(&start1, &start2, &start3,argv[1],argv[3]);
                        return 0;
                        break;
                    }

                    case '-':
                    {
                        substraction(&start1, &start2, &start3,argv[1],argv[3]);
                        return 0;
                        break;
                        
                    }

                    case '/':
                    {
                        division(&start1, &start2, &start3,argv[1],argv[3]);
                        return 0;
                        break;
                    }

                    default:
                    multiplication(&start1, &start2, &start3,argv[1],argv[3]);
                    return 0;
                    break;
                }
               
            }
            else{
                printf("Failed to assign values\n");
                return FAILURE;
            }
            
        }
        else
        {
            printf("Invalid operator passed\n");
            return FAILURE;
        }
    }
    else
    {
        printf("Invalid operands passed\n");
        return FAILURE;
    }
    
}