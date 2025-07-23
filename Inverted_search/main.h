#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define HASH_SIZE 28

typedef enum{
    SUCCESS = 0,
    FAILURE = 1
}status;


typedef struct node{
    char filename[30];
    struct node *link;
}slist;

typedef struct sub_node{
    char filename[30];
    int wordcount;
    struct sub_node *link;
}sub_node;

typedef struct main_node{
    int filecount;
    char word[50];
    struct sub_node *sub_link;
    struct main_node *main_link;
}main_node;


typedef struct hash{
    int index;
    struct main_node *hash_link;
}hash_t;

status validate(int argc,char *argv[],slist **head);
status create_database(slist **,hash_t *,int *,int *);
status create_hash_table(hash_t *,int);
status print_database(hash_t *);
status search_database(hash_t *,char *);
status update_database(slist **,hash_t *,int *,int *);
status save(hash_t *,char *);
status print_list(slist *head);
status load_database_from_file(hash_t *table, const char *filename);
int get_index(const char*);