#include<stdio.h>
#include "apc.h"
#include<ctype.h>
#include<stdlib.h>
#include<string.h>


int multiplication(startend *list1,startend *list2, startend *list3,char *left,char *right)
{
   int sign = 1;
   if(left[0] == '-' && right[0] != '-'){
        sign = -1;
   }
   else if(left[0] != '-' && right[0] == '-')sign = -1;
   else sign = 1;
    Dlist *temp1 = list1->tail;
    Dlist *temp2 = list2->tail;
    
    startend res = {NULL, NULL};
    startend toadd = {NULL, NULL};
    startend extra = {NULL, NULL};
    int count= 0;
    
    while(temp2 != NULL){
        clear(&res);
        int i=0;
        multiply(temp1,temp2->data,&res);
        while(i < count){
            addelementlast(&res);
            i++;
        }
        copy(list3, &extra);      
        clear(list3);             
        copy(&res, &toadd);       
        addmul(&toadd, &extra, list3);

        
        clear(&toadd);
        clear(&extra);
        temp2 = temp2->prev;
        count++;
    }
    Dlist *temp3 = list3->head;
    if(sign < 0)printf("-");
    while(temp3){
        printf("%d",temp3->data);
        temp3 = temp3->next;
    }
    printf("\n");
    return SUCCESS;
}

int multiply(Dlist *list,int data, startend *store)
{
    int carry = 0;
    while(list != NULL){
        int res = list->data * data + carry;
        if(res > 9){
            carry = res / 10;
        }
        else carry = 0;
        addelement(res % 10,store);
        list = list->prev;
    }
    if(carry > 0){
        addelement(carry,store);
    }
    return SUCCESS;
}

int addelementlast(startend *res)
{
    Dlist *new = malloc(sizeof(Dlist));
    if(new == NULL)return FAILURE;
    new->data = 0;
    new->next = NULL;
    if(res->tail == NULL){
        res->head = res->tail = new;
    }
    else{
    res->tail->next = new;
    new->prev = res->tail;
    res->tail = new;
    }
    return SUCCESS;
}

int addelement(int data,startend *store)
{
    Dlist *new = malloc(sizeof(Dlist));
    if(new == NULL)return FAILURE;
    new->data = data;
    new->next = store->head;
    new->prev = NULL;
    if(store->head != NULL)store->head->prev = new;
    store->head = new;
    if(store->tail == NULL){
        store->tail = new;
    }
    return SUCCESS;
}

int addmul(startend *list1, startend *list2, startend *list3)
{
    clear(list3);
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
    return SUCCESS;
}