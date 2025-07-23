#include<stdio.h>
#include "apc.h"
#include<ctype.h>
#include<stdlib.h>
#include<string.h>


int validate_operand(char *left, char *right)
{
        int i=0, j=0;
        if(left[i] == '-' || left[i] == '+')i++;

        while(left[i])
        {
            if(isdigit(left[i]) == 0)
            {
                return FAILURE;
            }
            i++;
        }

        if(right[j] == '-' || right[j] == '+') j++;
        while(right[j])
        {
            if(isdigit(right[j]) == 0)
            {
                return FAILURE;
            }
            j++;
        }
        return SUCCESS;
}

int validate_operator(char *opr)
{
    if(strlen(opr) != 1)return FAILURE;
    
    if(opr[0] == '+' || opr[0] == '-' || opr[0] == '*' || opr[0] == '/')return SUCCESS;
    else return FAILURE;
}



int assign_values(startend *list1, startend *list2, char *right, char *left)
{
    int i=0;
    Dlist *back1 = NULL;
    if(right[i] == '-' || right[i] == '+')i++;
    while(right[i])
    {   
        Dlist *temp = malloc(sizeof(Dlist));
        if(temp == NULL)return FAILURE;
        temp->data = (right[i] - 48);
        if(list1->head == NULL)
        {
            list1->head = temp;
            temp->prev = NULL;
            temp->next = NULL;
            back1 = temp;
            list1->tail = temp;
        }
        else{
        back1->next = temp;
        temp->prev = back1;
        temp->next = NULL;
        back1 = temp;
        list1->tail = temp;
        }
        i++;
    }

    int j=0;
    Dlist *back2 = NULL;
    if(left[j] == '-' || left[j] == '+')j++;
    while(left[j])
    {
        Dlist *temp2 = malloc(sizeof(Dlist));
        if(temp2 == NULL)return FAILURE;
        temp2->data = (left[j] - 48);
        if(list2->head == NULL)
        {
            list2->head = temp2;
            temp2->prev = NULL;
            temp2->next = NULL;
            back2 = temp2;
            list2->tail = temp2;
        }
        else{
           back2->next = temp2;
           temp2->prev = back2;
           temp2->next = NULL;
           back2 = temp2;
           list2->tail = temp2;
        }
        j++;
    }

    return SUCCESS;
}
