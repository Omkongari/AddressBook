#include<stdio.h>
#include "apc.h"
#include<ctype.h>
#include<stdlib.h>
#include<string.h>


int clear(startend *delete)
{
    Dlist *temp1 = delete->tail;

    while(temp1){
         Dlist *temp2 = temp1->prev;
        free(temp1);
        temp1 = temp2;
        
    }
    delete->head = NULL;
    delete->tail = NULL;
    return SUCCESS;
}


int copy(startend *res,startend *temp)
{
    if(res == NULL)return FAILURE;
    clear(temp);
    Dlist *temp1 = res->tail;
    while(temp1)
    {
        Dlist *new = malloc(sizeof(Dlist));
        if(new == NULL)return FAILURE;
        new->data = temp1->data;
        new->next = temp->head;
        new->prev = NULL;
        if(temp->head != NULL)temp->head->prev = new;
        temp->head = new;
        if(temp->tail == NULL)temp->tail = new;
        temp1 = temp1->prev;
    }
    return SUCCESS;
}
