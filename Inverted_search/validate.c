#include "main.h"

status validate(int argc,char *argv[],slist **head)
{
    slist *back = NULL;
    if(argc > 1)
    {
        for(int i=1; i<argc; i++)
        {
            if(strlen(argv[i]) > 4 && strcmp(argv[i] + strlen(argv[i]) - 4 , ".txt") == 0)
            {

                FILE *fptr = fopen(argv[i],"r");
                if(fptr == NULL)return FAILURE;
                
                fseek(fptr,0,SEEK_END);
                if(ftell(fptr) != 0){
                    if(*head == NULL){
                        slist *new = malloc(sizeof(slist));
                        if(new == NULL)return FAILURE;
                        new->link = NULL;
                        strcpy(new->filename,argv[i]);
                        *head = new;
                        back = new;
                    }
                    else{
                        int flag = 1;
                        slist *temp = *head;
                        while(temp){
                            if(strcmp(temp->filename,argv[i]) == 0)
                            {
                                flag = 0;
                                break;
                            }
                            temp = temp->link;
                        }
                        if(flag){
                            slist *new = malloc(sizeof(slist));
                            if(new == NULL)return FAILURE;
                            new->link = NULL;
                            strcpy(new->filename,argv[i]);
                            back->link = new;
                            back = new;
                        }
                    }
                }
            }
        }
    }
    else
    {
        return FAILURE;
    }
}