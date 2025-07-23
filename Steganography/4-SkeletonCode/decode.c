#include <stdio.h>
#include "types.h"
#include "decode.h"
#include <string.h>
#include "common.h"


Status read_and_validate_decode_args(char *argv[],DecodeInfo *decodeInfo)
{
    char arr[20];

    decodeInfo->fptr_src_image_decode = fopen(argv[2],"r");

    if(decodeInfo->fptr_src_image_decode == NULL){
        printf("The source image was not able to open\n");
        return e_failure;
    }
    
    fread(arr, 1, 2, decodeInfo->fptr_src_image_decode);
    if(arr[0] == 0x42 && arr[1] == 0x4d)
    {
        printf("The source file is a bmp file.\n");
        decodeInfo->src_image_fname_decode = argv[2];
    }
    else{
        printf("The source file is not a bmp file.\n");
        return e_failure;
    }

    if(argv[3] != NULL)
    {
        strcpy(arr, argv[3]);
        int i;

        for(i = 0; arr[i] != '.' ; i++){
            
        }
        arr[i] = '\0';
        printf("Output file name saved with given name.\n");
        strcpy(decodeInfo->out_fname, arr);
    }
    else{
        strcpy(decodeInfo->out_fname, "stego");
        printf("Output file name saved as the default name(stego).\n");
    }
    return e_success;

}

Status do_decoding(DecodeInfo *decodeInfo)
{
    if(open_files_decode(decodeInfo) == e_failure)
    {
        printf("Failed to open the source file.\n");
        return e_failure;
    }
    if(decode_magic_string(MAGIC_STRING, decodeInfo) == e_failure)
    {
        printf("Failed to decode the magic string.\n");
        return e_failure;
    }
    else{
        printf("Magic string successfully decoded.\n");
    }
    
    decode_out_file_extn_size(decodeInfo);

    decode_out_file_extn(decodeInfo);

    decode_out_file_size(decodeInfo);

    decode_out_file_data(decodeInfo);

}

Status open_files_decode(DecodeInfo *decodeInfo)
{
    decodeInfo->fptr_src_image_decode = fopen(decodeInfo->src_image_fname_decode, "r");
    if(decodeInfo->fptr_src_image_decode == NULL){
        printf("Failed to open the source file.\n");
        return e_failure;
    }
    return e_success;
}

Status decode_magic_string(char *magic_string, DecodeInfo *decodeInfo)
{
    char arr[strlen(magic_string) + 1];
    arr[strlen(magic_string)] = '\0';
    
    char image[8];
    
    fseek(decodeInfo->fptr_src_image_decode, 54, SEEK_SET);
    for(int i=0; i<strlen(magic_string) ; i++)
    {
        fread(image, 1, 8, decodeInfo->fptr_src_image_decode);
        arr[i] = decode_lsb_to_byte(image);
    }

    if(strcmp(arr, magic_string) == 0)
    {
        return e_success;
    }
    else return e_failure;
    
}

Status decode_out_file_extn(DecodeInfo *decodeInfo)
{
    char arr[8];
    int i;
    for(i=0; i<decodeInfo->out_extn_size; i++)
    {
        fread(arr, 1, 8, decodeInfo->fptr_src_image_decode);
        decodeInfo->extn_out_file[i] = decode_lsb_to_byte(arr);
    }
    decodeInfo->extn_out_file[i] = '\0';
    strcat(decodeInfo->out_fname, decodeInfo->extn_out_file);

    printf("Successfully decoded output file extension.\n");

}

Status decode_out_file_data(DecodeInfo *decodeInfo)
{
    decodeInfo->fptr_out_fname = fopen(decodeInfo->out_fname,"w");
    char arr[8];
    char ch;

    for(int i=0; i<decodeInfo->out_file_size; i++)
    {
        fread(arr, 1, 8, decodeInfo->fptr_src_image_decode);
        ch = decode_lsb_to_byte(arr);
        fwrite(&ch, 1, 1, decodeInfo->fptr_out_fname);
    }

    printf("The file data is successfully decoded.\n");
}

Status decode_out_file_size(DecodeInfo *decodeInfo)
{
    decodeInfo->out_file_size = decode_size(decodeInfo);

    printf("File size decoded successfully.\n");
}

char decode_lsb_to_byte(char *image_buffer)
{
    char data = 0;

    for(int i=0; i<8; i++)
    {
        data |= (image_buffer[i] & 1) << (7-i);
    }
    return data;
}

Status decode_out_file_extn_size(DecodeInfo *decodeInfo)
{
    decodeInfo->out_extn_size = decode_size(decodeInfo);
    printf("Successfully decoded the file extension size.\n");
}

uint decode_size(DecodeInfo *decodeInfo)
{
    char arr[32];
    fread(arr, 1, 32, decodeInfo->fptr_src_image_decode);
    unsigned int data = 0;
    for(int i=0; i<32; i++){
        data |= (arr[i] & 1) << (31 - i);
    }
    return data;
}

