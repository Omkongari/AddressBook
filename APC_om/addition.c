#include<stdio.h>
#include "apc.h"
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

int addition(startend *list1, startend *list2, startend *list3, char *left, char *right)
{
    
        int i=0;
       
        int is_negative = 0;

        if (left[i] == '-' && right[i] == '-') {
            is_negative = 1;
            left++;   
            right++; 
        }
        else if (left[i] == '-' && right[i] != '-') {
            subadd(list2, list1, list3);
            return SUCCESS;
        }
        else if (left[i] != '-' && right[i] == '-') {
            subadd(list1, list2, list3);
            return SUCCESS;
        }


    Dlist *temp1 = list1->tail;
    Dlist *temp2 = list2->tail;
    Dlist *temp3 = NULL;
    int carry = 0;
    while(temp1 != NULL || temp2 != NULL)
    {
        int val1 = (temp1 != NULL) ? temp1->data : 0;
        int val2 = (temp2 != NULL) ? temp2->data : 0;
        int res = val1 + val2 + carry;

        if(res > 9)
        {
            Dlist *nod = malloc(sizeof(Dlist));
            if(nod == NULL)return FAILURE;
            if(list3->tail == NULL)
            {
                temp3 = nod;
                nod->data = res % 10;
                nod->next = NULL;
                nod->prev = NULL;
                list3->head = nod;
                list3->tail = nod;
                carry = res / 10;
            }
            else
            {
            nod->data = res % 10;
            nod->next = temp3;
            nod->prev = NULL;
            temp3->prev = nod;
            list3->head = nod;
            carry = res / 10;
            temp3 = nod;
            }  
        }
        else
        {
            Dlist *nod2 = malloc(sizeof(Dlist));
            if(nod2 == NULL)return FAILURE;
            if(list3->tail == NULL)
            {
                nod2->prev = NULL;
                nod2->next = NULL;
                list3->tail = nod2;
                list3->head = nod2;
                nod2->data = res % 10;
                temp3 = nod2;
                carry = res / 10;
            }
            else
            {
                nod2->data = res % 10;
                nod2->prev = NULL;
                nod2->next = temp3;
                list3->head = nod2;
                carry = res / 10;
                temp3->prev = nod2;
                temp3 = nod2;
            }
        }
        if(temp1)temp1 = temp1->prev;
        if(temp2)temp2 = temp2->prev;
    }
    if (carry > 0)
    {
        Dlist *nod = malloc(sizeof(Dlist));
        if (nod == NULL) return FAILURE;
        nod->data = carry;
        nod->prev = NULL;
        nod->next = list3->head;
        if (list3->head != NULL) list3->head->prev = nod;
        list3->head = nod;
        if (list3->tail == NULL) list3->tail = nod;
    }
    if (is_negative)
        printf("-");
    Dlist *temp = list3->head;
    while(temp)
    {
        printf("%d", temp->data);
        temp = temp->next;
    }
    printf("\n");
    return SUCCESS;
}


int subadd(startend *list1,startend *list2,startend *list3)
{
    Dlist *temp1 = list1->tail;
    Dlist *temp2 = list2->tail;
    Dlist *temp3 = NULL;

    int count1 = 0;
    int count2 = 0;
    int sign = 1;
    while(temp1){
        count1++;
        temp1 = temp1->prev;
    }
    while(temp2){
        count2++;
        temp2 = temp2->prev;
    }
    if(count1 == count2)
    {
        if(list1->head->data < list2->head->data)
        {
            sign = -1;
        }
        else sign = 1;
    }
    else{
        if(count1 < count2)
        {
            sign = -1;
        }
        else sign = 1;
    }
    
    if(sign < 0)
    {
        temp1 = list2->tail;
        temp2 = list1->tail;
    }
    else{
        temp1 = list1->tail;
        temp2 = list2->tail;
    }

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
    
    if(sign < 0){
        printf("-");
        while(node){
            printf("%d",node->data);
            node = node->next;
        }
        printf("\n");
    }
    else{
        while(node){
            printf("%d",node->data);
            node = node->next;
        }
        printf("\n");
    }
    return SUCCESS;
}