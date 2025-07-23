#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edit.h"
#include "view.h"
#include "error.h"

int convert_little(unsigned const char *new)  //function to convert the size value into little endian
{
    char updated[4];
    updated[0] = new[3];
    updated[1] = new[2];
    updated[2] = new[1];
    updated[3] = new[0];
    
    unsigned int result;
    memcpy(&result, updated, 4);
    return result;
}

void convert_to_big(int new, unsigned char bytes[4])  //function to convert the size into big endian to store it in the new mp3 file
{
    char *swapped = (char *)&new;
    bytes[0] = swapped[3];
    bytes[1] = swapped[2];
    bytes[2] = swapped[1];
    bytes[3] = swapped[0];
}

int edit_tag(const char *filename, const char *tag, const char *new)  // Function to edit tags
{
    const char *tag_edit;
    //to check and assign the tag to edit                                                
    if(strcmp(tag, "-t") == 0) tag_edit = "TIT2";       //For title
    else if(strcmp(tag, "-A") == 0) tag_edit = "TPE1";  //For Artist
    else if(strcmp(tag, "-a") == 0) tag_edit = "TALB";  //For Album
    else if(strcmp(tag, "-y") == 0) tag_edit = "TYER";  //For year
    else if(strcmp(tag, "-c") == 0) tag_edit = "TCON";  //For Content
    else if(strcmp(tag, "-m") == 0) tag_edit = "COMM";  //For Comment
    else{
        printf("Entered tag option not available\n");  //if the tag not option not found, return
        return 1;
    }

    FILE *old = fopen("sample.mp3","r");  //open the .mp3 file in read mode to read the data
    if(!old){                             //if the file is not present, terminate the function
        printf("File not available\n");
        fclose(old);
        return 1;
    }

    FILE *fresh = fopen("new.mp3", "w");  //create new file to store the data of the previous file and to store the edited option
    if(!fresh){
        printf("Could not create new file\n");
        fclose(fresh);
        return 1;
    }

    unsigned char header[10];
    
    if(fread(header, 1, 10, old) != 10){  //skipping the first 10 bytes of file and storing it in header
        printf("File header corrupted\n");
        fclose(old);
        return 1;
    }
    if(strncmp(header, "ID3", 3) != 0){  //comparing the signature of the file, which is ID3, if the tag is not matching terminate the program
        printf("ID3 signature not found\n");
        fclose(old);
        return 1;
    }

    fwrite(header, 1, 10, fresh);  //because header is same, copying the header as it is into the new file
    

    int found = 0;  //to make sure only one tag is edited when it is found

    while(found != 1)
    {
        char tag_header[5] = {0};   //to store the tag header which is 4 bytes, but 5 due to null character
        unsigned char old_size[4];  
        char flags[2];

        if(fread(tag_header, 1, 4, old) != 4){        //Skipping 4 bytes and storing the tag header in tag_header
            printf("Could not read the tag header\n");
            break;
        }
        if(fread(old_size, 1, 4, old) != 4){      //skipping 4 bytes of integer size and storing it in old_size   
            printf("Could not read tag size\n");
            break;
        }
        if(fread(flags, 1, 2, old) != 2){     //skipping 2 bytes of flag which of no use to use
            printf("Failed to read tags\n");
            break;
        }
        
        unsigned int new_size = convert_little(old_size);   //Calling a function to convert the old_size into little endian, so that our systme understands it, and storing it in new_size
        if(strncmp(tag_header, tag_edit, 4) == 0 && !found){ //Checking if the tag to edit is found and tracking found variable is zero or not 
            found = 1;                      

            fseek(old, new_size, SEEK_CUR);  //skipping the data of the found tag, in the previous file

            fwrite(tag_header, 1 , 4, fresh);  //writing the found tag header to the fresh file

            int len = strlen(new) + 1;  //calculating the length the data that we provided in the new value in the command argument, +1 is for the null character

            unsigned char new_byte[4];  //to convert the calculated length to big endian

            convert_to_big(len, new_byte);  //to convert the calculated length of the new value, because int mp3 we store the size in big endian format 

            fwrite(new_byte, 1, 4, fresh);  //writing the size that is now converted to big endian to fresh file
            fwrite(flags, 1, 2, fresh);  //writing the 2 bytes of flag to fresh file
            fputc(0, fresh);   //adding a null character before the data

            fwrite(new, 1, strlen(new), fresh);  //writing the updated data to the fresh file, of new bytes size
        }
        else 
        {   //if the tag to edit is not yet found, copy that tag to the new file as it is
            fwrite(tag_header, 1, 4, fresh); //first write the tag header
            fwrite(old_size, 1, 4, fresh);   //the size
            fwrite(flags, 1, 2, fresh);    //the flags

            unsigned char *data = malloc(new_size);  //allocate the memory in heap segment to store the the data of the tag
            if(!data){
                printf("Memory allocation failed for data\n");
                fclose(old);
                fclose(fresh);
                return 1;
            }

            fread(data, 1, new_size, old);  //read the data of the old file into allocated data memory
            fwrite(data, 1, new_size, fresh);  //write the data into new file
            free(data);  // free the data to reuse to same pointer for the new iteration
        }
    }

    char buffer[1024]; //once the tag is edited, copy the remaining data of the entire file to the new file
    int a;
    while((a = fread(buffer, 1, sizeof(buffer), old)) > 0){  //to read from old file and write to new file the entire data
        fwrite(buffer, 1, a, fresh);
    }

    fclose(old);   //close the file pointer after use completed
    fclose(fresh);

    remove(filename);  //delete the old file
    rename("new.mp3", filename);  //replace and rename the new file as the old file

    

    read_id3_tags(filename);  //to display that tag was successfully edited

    return 0;

}