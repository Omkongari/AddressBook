#include "main.h"

status print_database(hash_t *table)
{
    printf("Index\tWord\tFileCount\tFilename\tWordCount\n");

    for (int i = 0; i < 28; i++)
    {
        main_node *mnode = table[i].hash_link;
        if (mnode == NULL)
            continue;

        while (mnode)
        {
            sub_node *snode = mnode->sub_link;
            
            while (snode)
            {
                printf("%d\t%s\t%d\t\t%s\t\t%d\n", i, mnode->word, mnode->filecount, snode->filename, snode->wordcount);
                snode = snode->link;
            }
            mnode = mnode->main_link;
        }
    }

    return SUCCESS;
}
