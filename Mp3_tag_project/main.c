/*
Name -: Om Kongari
Date -: 06/05/2025
Project title -: MP3 tag reader
*/

#include <stdio.h>
#include <string.h>
#include "main.h"
#include "view.h"
#include "edit.h"
#include "error.h"
#include <stdio.h>


void display_help() {  //function to display help
    
    printf("\n============MP3 Tag Reader help section==============\n");

    printf("Options :\n");
    printf("To view the details of the Mp3 file, type:\n");
    printf("./a.out -v <filename>\n\n");

    printf("To edit a particular tag in the file, type the commands in the manner given below :\n");
    printf("First the option to edit :\n");
    printf("./a.out -e <filename>\n");
    printf("After typing -e <filename> , specify which tag you want to edit :\n");
    printf("There are 6 tag options to choose to edit:\n\n");
    printf("1st) -t to edit Title\n");
    printf("2nd) -A to edit Artist\n");
    printf("3rd) -a to edit Album\n");
    printf("4th) -y to edit the year\n");
    printf("5th) -c to edit the content\n");
    printf("6th) -m to edit comment\n\n");

    printf("After specifying what you want to edit, you need to enter the value to replace in the tag you chose to edit\n\n");

    printf("After entering all arguments, your command should look like this : \n");

    printf("./a.out -e <filename> <tag option> <new_value>\n\n");

    printf("For example: ./a.out -e sample.mp3 -t ''Honey singh''\n\n");

    printf("Hope this section was helpful to make you understand how this MP3 tag reader works!!\n\n");


}

int has_mp3_extension(const char *filename) {  // Validate .mp3 
    int len = strlen(filename);
    return len > 4 && strcmp(filename + len - 4, ".mp3") == 0;
}


int main(int argc, char *argv[]) 
{
    if (argc < 2) {
        display_error("No argument passed");
        display_help();
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0) 
    {
        display_help();
        return 0;
    } 
    else if (strcmp(argv[1], "-v") == 0 && argc == 3) 
    {
        if (!has_mp3_extension(argv[2])) 
        {
            printf("Incorrect file name, enter a valid file name\n");
            return 1;
        }
        read_id3_tags(argv[2]);
    } 
    else if (strcmp(argv[1], "-e") == 0 && argc == 5) 
    {
        if (!has_mp3_extension(argv[2])) 
        {
            printf("Incorrect file name, enter a valid file name\n");
            return 1;
        }
        char *filename = argv[2]; 
        char *tag = argv[3];
        char *value = argv[4];
        if (edit_tag(filename, tag, value) != 0) 
        {
            display_error("Failed to edit tag");
            return 1;
        }
        printf("\nTag edited successfully!!\n\n");
    } 
    else 
    {
        display_help();
        return 1;
    }

    return 0;
}
