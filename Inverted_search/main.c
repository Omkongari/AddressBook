/*
Name-: Om Kongari
Date-: 07/07/2025
Project title-: Inverted search
*/

#include<stdio.h>
#include "main.h"

int main(int argc, char *argv[])
{   
    slist *head = NULL;
    hash_t table[HASH_SIZE];
    int flag = 1,create = 1, update = 1;

    if(argc > 1){
        if(validate(argc,argv,&head) == FAILURE){
            printf("Invalid arguments passed\n");
            return 0;
        }
        else{
            create_hash_table(table ,HASH_SIZE);
            
            printf("Choose which operation to perform: \n");
            printf("1. Create Database\n2. Display Database\n3. Search database\n4. Update database\n5. Save\n6. Exit\n");
            while(1)
            {
                int choice;
                scanf("%d",&choice);

                switch(choice)
                {
                    case 1:
                    {
                        if(create_database(&head,table,&flag,&create) == SUCCESS)
                        {
                            printf("Database successfully created!!!!\n");

                        }
                        else{
                            printf("Database creation failed.\n");
                        }
                        break;
                    }
                    
                    case 2:
                    {
                        print_database(table);
                        break;
                    }
                    
                    case 3:
                    {
                        char str[20];
                        printf("Enter word to search:\n");
                        scanf("%s",str);
                        search_database(table,str);
                        break;
                    }

                    case 4:
                    {
                        update_database(&head,table,&flag,&update);
                        break;
                    }

                    case 5:
                    {
                        char filename[20];
                        printf("Enter filename to create and save the database\n");
                        scanf("%s",filename);
                        save(table,filename);
                        break;
                    }

                    case 6:
                    printf("Exiting!!!!\n");
                    return 0;


                    default:
                    printf("Invalid choice.\n");

                }
            }
        }
    }
    else{
        printf("Not enough arguments passed\n");
        return 0;
    }

}