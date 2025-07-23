#include<stdio.h>
#include<stdlib.h>
#include "view.h"
#include<string.h>

unsigned int convert_to_little_endian(unsigned char *size) //function to convert the size into little endian
{
    char new[4];
    new[0] = size[3];
    new[1] = size[2];
    new[2] = size[1];
    new[3] = size[0];

    unsigned int updated;
    memcpy(&updated, new, 4);

    return updated;
}

void read_id3_tags(const char *filename) //function to read tags
{
    FILE *fptr = fopen(filename,"r"); //opening file in read mode
    if(!fptr){
        printf("File not found\n");
        fclose(fptr);
        return;
    }

    unsigned char header[10];
    if(fread(header, 1 , 10, fptr) != 10){ //Skipping the first 10 bytes and storing it in the header
        printf("Failed to read header\n");
        fclose(fptr);
        return;
    }

    if(strncmp(header, "ID3", 3) != 0){   //checking the first 3 bytes to see if it is matching standard mp3 signature
        printf("Failed to read ID3 signature\n");
        fclose(fptr);
        return ;
    }

    printf("\n\n=======================================\n");
    printf("\n==============MP3 Details==============\n\n");

    int tag_count=0; 
    while(tag_count < 6){ // because we are reading only 6 tags, the loop will run 6 times

        char tag[5] = {0};
        unsigned char size[4];
        char flag[2];

        if(fread(tag, 1, 4 , fptr) != 4) break;  //skipping 4 bites and storing tag name in tag

        if(fread(size, 1, 4, fptr) != 4) break;  //skipping 4 bites and storing the size of the tag data which is 4 bytesof integer

        if(fread(flag, 1, 2, fptr) != 2) break;  //skipping 2 bites of flag, which are no use to us

        unsigned int updated_size = convert_to_little_endian(size); //because mp3 file stores size in big endian format, we are converting it into little endian so our system understands it

        char *data = (char *)malloc( updated_size + 1 ); //allocating size for data based on the size 

        if(!data){
            printf("Memory allocation to read data failed\n");
            fclose(fptr);
            break;
        }

        if(fread(data, 1, updated_size, fptr) != updated_size){ //skipping the bites as per the size and storing it in data to print further
            printf("Failed to read the data\n");
            break;
            return ;
        }
        data[updated_size] = '\0'; //adding null character at end of the data

        
        if(strcmp(tag, "TIT2") == 0){
            printf("Title    :    %s\n", data + 1); // + 1 to consider the null terminator
            tag_count++;
        }
        else if(strcmp(tag, "TPE1") == 0){
            printf("Artist   :    %s\n", data + 1);
            tag_count++;
        }
        else if(strcmp(tag, "TALB") == 0){
            printf("ALBUM    :    %s\n", data + 1);
            tag_count++;
        }
        else if(strcmp(tag, "TYER") == 0){
            printf("YEAR     :    %s\n", data + 1);
            tag_count++;
        }
        else if(strcmp(tag, "TCON") == 0){
            printf("Content  :    %s\n", data + 1);
            tag_count++;
        }
        else if(strcmp(tag, "COMM") == 0){
            printf("Comment  :    %s\n", data + 1);
            tag_count++;
        }
        else 
        {
            printf("Unreacognizable tag\n");
            break;
        }
       
        free(data); // once one tag is printed, freeing data for reusability
    }
    printf("\n=======================================\n");

    fclose(fptr); // after reading all the tags, closing the file

}