#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {

    FILE *fptr = fopen("contacts_book.csv", "w");
    if(fptr == NULL){
        printf("File not found\n");
        return;
    }
    fprintf(fptr, "%d\n" , addressBook->contactCount);
    for(int i=0 ; i<addressBook->contactCount ; i++){
        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);

    }
    fclose(fptr);
    printf("Contacts saved in file successfully\n");
  
}

void loadContactsFromFile(AddressBook *addressBook) {

    FILE *fptr = fopen("contacts_book.csv", "r");
    if(fptr == NULL){
        printf("Contacts not found\n");
    }
    fscanf(fptr, "%d\n", &addressBook->contactCount);
    for(int i=0; i<addressBook->contactCount ; i++){
        fscanf(fptr, "%[^,],%[^,],%[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);

    }
    fclose(fptr);
    
    
}
