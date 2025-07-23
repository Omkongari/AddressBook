#include "main.h"

status create_hash_table(hash_t *table,int size)
{

    for(int i=0 ; i<size ; i++){
        table[i].index = i;
        table[i].hash_link = NULL;
    }
    return SUCCESS;
    
}