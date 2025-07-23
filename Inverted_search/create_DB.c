#include "main.h"

status create_database(slist **head,hash_t *table,int *yo,int *create)
{
    if(*yo == 1){
        *yo = 0;
    }

    if(*create == 1)*create = 0;
    else{
        printf("Can't create more than once\n");
        return FAILURE;
    }
    
    if(*head == NULL)return FAILURE;
    slist *temp = *head;
    
    while(temp)
    {
        FILE *fptr = fopen(temp->filename,"r");
        if(fptr == NULL)return FAILURE;
        char str[20];
        while(fscanf(fptr,"%s",str) == 1)
        {   
            char ch = str[0];
            if(ch >= 'A' && ch <= 'Z') ch +=32;

            int ind = ch % 97;

            if(table[ind].hash_link == NULL){
                main_node *new = malloc(sizeof(main_node));
                if(new == NULL)return FAILURE;
                new->filecount = 1;
                strcpy(new->word,str);
                new->main_link = NULL;
                sub_node *slink = malloc(sizeof(sub_node));
                if(slink == NULL)return FAILURE;
                strcpy(slink->filename,temp->filename);
                slink->wordcount = 1;
                slink->link = NULL;
                new->sub_link = slink;
                table[ind].hash_link = new;
            }
            else
            {
                main_node *next = table[ind].hash_link;
                main_node *back = NULL;
                int flag = 1;
                int wordfound = 0;
                while(next)
                {
                    sub_node *snode = next->sub_link;
                    sub_node *prev = NULL;
                    if(strcmp(str,next->word) == 0)
                    {
                        wordfound = 1;
                        while(snode){
                            if(strcmp(snode->filename,temp->filename) == 0)
                            {
                                snode->wordcount++;
                                flag = 0;
                                break;
                            }
                            prev = snode;
                            snode = snode->link;
                        }
                        if(flag)
                        {
                            next->filecount++;
                            snode = next->sub_link;
                            while(snode->link != NULL){
                                snode = snode->link;
                            }
                            sub_node *new = malloc(sizeof(sub_node));
                            if(new == NULL)return FAILURE;
                            new->wordcount = 1;
                            strcpy(new->filename,temp->filename);
                            new->link = NULL;
                            snode->link = new;
                            flag = 0;
                        }
                    }
                    back = next;
                    next = next->main_link;
                }
                if(!wordfound)
                {
                     main_node *new = malloc(sizeof(main_node));
                    if(new == NULL)return FAILURE;
                    if (back)back->main_link = new;

                    else table[ind].hash_link = new;
                        
                    new->filecount = 1;
                    strcpy(new->word,str);
                    new->main_link = NULL;
                    sub_node *another = malloc(sizeof(sub_node));
                    if(another == NULL)return FAILURE;
                    another->wordcount = 1;
                    strcpy(another->filename,temp->filename);
                    another->link = NULL;
                    new->sub_link = another;
                }
            }
        }
        fclose(fptr);
        temp = temp->link;
    }
    return SUCCESS;
}
