#include "main.h"

status search_database(hash_t *table, char *str)
{
    char ch = str[0];
    if(ch >= 'A' && ch <= 'Z')ch += 32;
    int ind = ch % 97;
    
    if(table[ind].hash_link == NULL)
    {
        printf("Word not found in the database\n");
        return FAILURE;
    }
    main_node *new = table[ind].hash_link;
    sub_node *temp = NULL;
    while(new){
        if(strcmp(new->word,str) == 0)
        {
            temp = new->sub_link;
            printf("\n------------Query found------------\n");
            printf("Word found ---> %s\n",new->word);
            printf("File count ---> %d\n",new->filecount);
            break;
        }
        new = new->main_link;
    }
    if(new == NULL){
        printf("Word not found in Database.\n");
        return FAILURE;
    }

    printf("Filename    wordcount\n");
    while(temp){
        printf("%s\t%d\n",temp->filename,temp->wordcount);
        temp = temp->link;
    }
    return SUCCESS;
}