#include "main.h"

status update_database(slist **head, hash_t *table, int *flag, int *update)
{
    if (*flag == 0) {
        printf("Can't update after create\n");
        return FAILURE;
    }

    if (*update == 1) *update = 0;
    else {
        printf("Can't update more than once\n");
        return FAILURE;
    }
   
    if (load_database_from_file(table, "result.txt") == SUCCESS) {
        printf("Previous data loaded from result.txt into database.\n");
    } else {
        printf("No previous data found in result.txt\n");
    }

    
    if (*head == NULL) {
        printf("No update file found in slist.\n");
        return FAILURE;
    }

    char str[100];
    strcpy(str, (*head)->filename);
    FILE *fptr = fopen(str, "r");
    if (fptr == NULL) {
        printf("The update file does not exist\n");
        return FAILURE;
    }

    if (strlen(str) < 4 || strcmp(str + strlen(str) - 4, ".txt") != 0) {
        printf("The file is not a .txt file\n");
        fclose(fptr);
        return FAILURE;
    }

    char word[100];
    while (fscanf(fptr, "%s", word) == 1) {

        
        for (int i = 0; word[i]; i++) {
            if (word[i] >= 'A' && word[i] <= 'Z')
                word[i] += 32;
        }

        int index = get_index(word);
        main_node *temp = table[index].hash_link;
        main_node *prev = NULL;

       
        while (temp) {
            if (strcmp(temp->word, word) == 0) break;
            prev = temp;
            temp = temp->main_link;
        }

        
        if (!temp) {
            temp = malloc(sizeof(main_node));
            if (!temp) return FAILURE;

            strcpy(temp->word, word);
            temp->filecount = 0;
            temp->sub_link = NULL;
            temp->main_link = NULL;

            if (prev)
                prev->main_link = temp;
            else
                table[index].hash_link = temp;
        }

        
        sub_node *s = temp->sub_link;
        int found = 0;
        while (s) {
            if (strcmp(s->filename, str) == 0) {
                s->wordcount++;  
                found = 1;
                break;
            }
            s = s->link;
        }

        
        if (!found) {
            sub_node *new = malloc(sizeof(sub_node));
            if (!new) return FAILURE;

            strcpy(new->filename, str);
            new->wordcount = 1;
            new->link = NULL;

            if (!temp->sub_link)
                temp->sub_link = new;
            else {
                s = temp->sub_link;
                while (s->link)
                    s = s->link;
                s->link = new;
            }
            temp->filecount++;
        }
    }

    fclose(fptr);
    printf("Database updated successfully\n");
    print_database(table);
    return SUCCESS;
}


status load_database_from_file(hash_t *table, const char *filename)
{
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
        return FAILURE;

    int index, file_count, word_count;
    char word[100], file_name[100];

    while (fscanf(fptr, "#%d;%[^;];", &index, word) == 2)
    {
        if (fscanf(fptr, "%d;", &file_count) != 1)
            break;

        main_node *temp = table[index].hash_link;
        main_node *prev = NULL;

        while (temp != NULL) {
            if (strcmp(temp->word, word) == 0)
                break;
            prev = temp;
            temp = temp->main_link;
        }

        if (temp == NULL) {
        temp = malloc(sizeof(main_node));
        if (!temp) return FAILURE;

        if (prev)
            prev->main_link = temp;
        else
            table[index].hash_link = temp;

        strcpy(temp->word, word);
        temp->filecount = file_count; 
        temp->sub_link = NULL;
        temp->main_link = NULL;
        }
        for (int i = 0; i < file_count; i++)
        {
            if (fscanf(fptr, "%[^;];%d;", file_name, &word_count) != 2)
                break;

            sub_node *check = temp->sub_link;
            int exists = 0;
            while (check != NULL) {
                if (strcmp(check->filename, file_name) == 0) {
                    exists = 1;
                    break;
                }
                check = check->link;
            }

            if (exists)
                continue;

            sub_node *new = malloc(sizeof(sub_node));
            if (!new) return FAILURE;

            strcpy(new->filename, file_name);
            new->wordcount = word_count;
            new->link = NULL;

            if (temp->sub_link == NULL)
                temp->sub_link = new;
            else {
                sub_node *sub_temp = temp->sub_link;
                while (sub_temp->link)
                    sub_temp = sub_temp->link;
                sub_temp->link = new;
            }

        }

        fscanf(fptr, "#\n");
    }

    fclose(fptr);
    return SUCCESS;
}

int get_index(const char *word)
{
    char ch = word[0];
    if (ch >= 'A' && ch <= 'Z')
        ch += 32;
    return ch % 97;
}
