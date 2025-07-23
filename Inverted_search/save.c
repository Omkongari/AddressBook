#include "main.h"

status save(hash_t *table,char *str)
{
    FILE *fptr = fopen(str,"w");
    if(fptr == NULL){
        printf("File could not be created\n");
        return FAILURE;
    }

    for (int i = 0; i < 28; i++)
    {
        main_node *mnode = table[i].hash_link;
        if (mnode == NULL)
            continue;

        while (mnode)
        {
            sub_node *snode = mnode->sub_link;
            fprintf(fptr,"#%d;%s",i,mnode->word);
            while (snode)
            {
                fprintf(fptr,";%d;%s;%d;", mnode->filecount, snode->filename, snode->wordcount);
                snode = snode->link;
            }
            fprintf(fptr,"#\n");

            mnode = mnode->main_link;
        }
        
    }

    printf("Saving and Exiting!!!\n");
    return SUCCESS;

}