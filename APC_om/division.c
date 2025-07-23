#include<stdio.h>
#include "apc.h"
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

int division(startend *list1, startend *list2, startend *list3,char *left,char *right)
{
    int sign = 1;
    if(left[0] == '-' && right[0] != '-')sign = -1;
    else if(left[0] != '-' && right[0] == '-')sign = -1;
    else sign = 1;

    Dlist *temp1 = list1->head;
    Dlist *temp2 = list2->head;
    Dlist *temp3 = NULL;
    
    if(list2->head->data == 0)
    {
        printf("0\n");
        return FAILURE;
    }

    int count1 = 0, count2 = 0;
   
    while(temp1){
        count1++;
        temp1 = temp1->next;
    }
    while(temp2){
        count2++;
        temp2 = temp2->next;
    }
    temp1 = list1->tail;
    temp2 = list2->tail;

    if(count1 == count2)
    {
        if(list1->head->data < list2->head->data)
        {
            printf("Invalid input\n");
            return FAILURE;
        }
    }
    else{
        if(count1 < count2){
            printf("Invalid input\n");
            return FAILURE;
        }
    }
    long long int res = 0;
    while(1)
    { 
        dividesub(list1,list2,list3);
        res++;
        if(compare(list2,list3) == FAILURE)break;
        
        clear(list1);
        copy(list3,list1);
        clear(list3);
    }
    clear(list3);
    while(res != 0)
    {
        Dlist *new = malloc(sizeof(Dlist));
        if(new == NULL)return FAILURE;
        new->data = res % 10;
        new->prev = NULL;
        new->next = list3->head;
        res /= 10;
        if(list3->head != NULL)list3->head->prev = new;
        list3->head = new;
        if(list3->tail == NULL)list3->tail = new;
    }

    if (list3->head == NULL)
    {
    Dlist *node = malloc(sizeof(Dlist));
    if (!node) return FAILURE;
    node->data = 0;
    node->prev = node->next = NULL;
    list3->head = list3->tail = node;
    }

    if(sign < 0)printf("-");
    temp3 = list3->head;
        while(temp3){
            printf("%d",temp3->data);
            temp3 = temp3->next;
        }
        printf("\n");
        return SUCCESS;
}

int dividesub(startend *list1,startend *list2, startend *list3)
{
    Dlist *temp1 = list1->tail;
    Dlist *temp2 = list2->tail;
    Dlist *temp3 = NULL;

    int borrow = 0;
    while (temp1 != NULL || temp2 != NULL)
    {
        int val1 = (temp1 != NULL) ? temp1->data : 0;
        int val2 = (temp2 != NULL) ? temp2->data : 0;

        val1 -= borrow;
        if (val1 < val2)
        {
            val1 += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        int res = val1 - val2;

        Dlist *node = malloc(sizeof(Dlist));
        if (node == NULL) return FAILURE;
        node->data = res;
        node->prev = NULL;
        node->next = temp3;

        if (temp3 != NULL)
            temp3->prev = node;

        temp3 = node;

        if (list3->tail == NULL)
            list3->tail = node;

        list3->head = node;

        if (temp1) temp1 = temp1->prev;
        if (temp2) temp2 = temp2->prev;
    }
    Dlist *node = list3->head;
    while (node && node->data == 0 && node->next)
{
    list3->head = node->next;
    list3->head->prev = NULL;
    free(node);
    node = list3->head;
}
return SUCCESS;
}

int compare(startend *list2,startend *list3)
{
    Dlist *temp1 = list2->head;
    Dlist *temp2 = list3->head;
    int count1 = 0,count2 = 0;
    while(temp1){
        count1++;
        temp1 = temp1->next;
    }
    while(temp2)
    {
        count2++;
        temp2 = temp2->next;
    }
    if(count1 == count2)
    {
        if(list2->head->data > list3->head->data){
            return FAILURE;
        }
        else return SUCCESS;
    }
    else{
        if(count1 > count2){
            return FAILURE;
        }
        else return SUCCESS;
    }
}