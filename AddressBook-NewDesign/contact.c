#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

int nres = 0, pres = 0, eres = 0;

int valname(char *name);
int valphone(char *number);
int duphn(char *number, AddressBook *addressbook);
int valemail(char *email);
int duemail(char *mail, AddressBook *addressbook);

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    AddressBook temp;
    switch(sortCriteria)
    {
        case 1:
        {
        for(int i=0 ; i < addressBook->contactCount - 1; i++){
            for(int j=0; j<addressBook->contactCount-1-i; j++){
                int ns = strcasecmp(addressBook->contacts[j].name, addressBook->contacts[j+1].name );
                if(ns > 0){
                    temp.contacts[0] = addressBook->contacts[j] ;
                    addressBook->contacts[j] = addressBook->contacts[j+1];
                    addressBook->contacts[j+1] = temp.contacts[0];
                }
            }
            
        }
        break;
        }

        case 2:
        {
        for(int i=0; i<addressBook->contactCount-1;i++){
            for(int j=0; j<addressBook->contactCount-1-i; j++){
                int ns = strcmp(addressBook->contacts[j].phone, addressBook->contacts[j+1].phone);
                if(ns > 0){
                    temp.contacts[0] = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j+1];
                    addressBook->contacts[j+1] = temp.contacts[0];
                }
            }
        }
        break;
        }  
        
        case 3:
        {
        for(int i=0 ; i<addressBook->contactCount-1 ; i++){
            for(int j=0; j<addressBook->contactCount-1-i; j++){
                int ns = strcmp(addressBook->contacts[j].email, addressBook->contacts[j+1].email);
                if(ns > 0){
                    temp.contacts[0] = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j+1];
                    addressBook->contacts[j+1] = temp.contacts[0];
                }
            }
        }
        break;
        }
    }

    printf("\033[0;31m");
	for(int i=1;i<=116;i++)
	{
		printf("-");
	}
	printf("\n");
	printf("|%-10s %-30s %-30s %-40s %-10c\n|%115c\n","Sr.No.","CONTACT NAME","CONTACT MOBILE NUMBER","CONTACT EMAIL ID",'|','|');
	printf("\033[0m");

	for(int i=0;i<addressBook->contactCount;i++)
   	{
	printf("\033[31m|\033[0m%-10d %-35s %-25s %-20s\033[31m %21c\n|%115c\033[0m\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email,'|','|');
  	}

	for(int i=1;i<=116;i++)
	{
		printf("\033[31m-\033[0m");
	}
	
	printf("\n\nPress Enter to continue...");
            while (getchar() != '\n');
			getchar();
}
    
    

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    // populateAddressBook(addressBook);
    loadContactsFromFile(addressBook);
    
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */ 
      
    do{
        printf("\nEnter the name\n");
        scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);
        nres = valname(addressBook->contacts[addressBook->contactCount].name);
        }while(nres != 1 );
    
    do{
        printf("Enter phone number\n");
        scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].phone);
        pres = valphone(addressBook->contacts[addressBook->contactCount].phone);
        if(pres){
              pres = duphn(addressBook->contacts[addressBook->contactCount].phone, addressBook);
        }
    }while(pres != 1);

    do{
        printf("Enter email address\n");
        scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].email);
        eres = valemail(addressBook->contacts[addressBook->contactCount].email);
        if(eres){
            eres = duemail(addressBook->contacts[addressBook->contactCount].email, addressBook);
        }
    }while(eres != 1);
    addressBook->contactCount++;
    printf("\n\nContact Created successfully\n ");
}


int searchContact(AddressBook *addressBook) 
{
	int c;
	char temp[40];

choice:
	printf("\nPress 1 for name search:\n");
	printf("Press 2 for phone NUMBER search:\n");
	printf("Press 3 for email search:\n");
	printf("Enter Your Choice: ");
	scanf("%d", &c);

	if (c > 3 || c < 1) {
		printf("\nInvalid Choice, Please try again.");
		goto choice;
	}

	int found = 0;

	switch (c) {
	case 1:
		printf("\nEnter Name: ");
		scanf(" %[^\n]", temp);
		for (int i = 0; i < addressBook->contactCount; i++) {
			if (strcasestr(addressBook->contacts[i].name, temp) != NULL) {
				if (!found) {
					printf("\n\n------CONTACT DETAILS------\n");
				}
				printf("[%d]  %s,  %s,  %s\n", i,
					addressBook->contacts[i].name,
					addressBook->contacts[i].phone,
					addressBook->contacts[i].email);
				found = 1;
			}
		}
		break;

	case 2:
		printf("\nEnter Number: ");
		scanf(" %[^\n]", temp);
		for (int i = 0; i < addressBook->contactCount; i++) {
			if (!strcmp(temp, addressBook->contacts[i].phone)) {
				printf("\n\n------CONTACT DETAILS------\n");
				printf("[%d] %s,  %s,  %s\n", i,
					addressBook->contacts[i].name,
					addressBook->contacts[i].phone,
					addressBook->contacts[i].email);
				found = 1;
			}
		}
		break;

	case 3:
		printf("\nEnter Email: ");
		scanf(" %[^\n]", temp);
		for (int i = 0; i < addressBook->contactCount; i++) {
			if (!strcmp(temp, addressBook->contacts[i].email)) {
				printf("\n\n------CONTACT DETAILS------\n");
				printf("[%d] %s,  %s,  %s\n", i,
					addressBook->contacts[i].name,
					addressBook->contacts[i].phone,
					addressBook->contacts[i].email);
				found = 1;
			}
		}
		break;
	}

	if (!found) {
		char choice;
		printf("\nContact not found, Do you want to try again(Y/N)? ");
		scanf(" %c", &choice);
		if (choice == 'y' || choice == 'Y') {
			goto choice;
		}else return 1;
	}

	printf("\n\nPress Enter to continue...");
	while (getchar() != '\n');
	getchar();

	return 0;
}


void editContact(AddressBook *addressBook)
{
	if(searchContact(addressBook)){ // Show matches with index
		printf("\n No contact to edit\n");
		return;
	}

	int index;
	printf("\nEnter the index of the contact you want to edit: ");
	scanf("%d", &index);

	if (index < 0 || index >= addressBook->contactCount) {
		printf("\nInvalid index.\n");
		return;
	}


	int n, r;
	char temp[100];

	edit_menu:
	printf("\nPress 1 to edit Name");
	printf("\nPress 2 to edit Number");
	printf("\nPress 3 to edit Email\n");
	scanf("%d", &n);

	switch (n) {
	case 1:
	name:
		printf("Enter new name: ");
		scanf(" %[^\n]", temp);
		r = valname(temp);
		if (!r) {
			printf("Invalid name, try again.\n");
			goto name;
		}
		strcpy(addressBook->contacts[index].name, temp);
		break;

	case 2:
	number:
		printf("Enter new number: ");
		scanf(" %[^\n]", temp);
		r = valphone(temp);
		if (!r) {
			printf("Invalid or duplicate number, try again.\n");
			goto number;
		}
		strcpy(addressBook->contacts[index].phone, temp);
		break;

	case 3:
	email:
		printf("Enter new email: ");
		scanf(" %[^\n]", temp);
		r = valemail(temp);
		if (!r) {
			printf("Invalid or duplicate email, try again.\n");
			goto email;
		}
		strcpy(addressBook->contacts[index].email, temp);
		break;

	default:
		printf("Invalid choice, try again.\n");
		goto edit_menu;
	}

	printf("\nContact updated successfully.\n");
	printf("\n\nPress Enter to return to menu...");
	while (getchar() != '\n');
	getchar();
}


void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    
    int id;
    char choice;
    listContacts(addressBook, 1);
    
    while(1){
    printf("Enter the id number you want to delete: ");
    scanf("%d", &id);
    if(id >= 0 || id < addressBook->contactCount){
        printf("\nSelect a valid id: ");
        break;
        
    }
}
    printf("\n%s ", addressBook->contacts[id].name);
    printf("\n%s ", addressBook->contacts[id].phone);
    printf("\n%s ", addressBook->contacts[id].email);
    printf("Are you sure you want to delete this contact: (y/n)");

    scanf(" %c", &choice);
    if(choice == 'y' || choice == 'Y'){
        for(int i = id ; i<addressBook->contactCount-1 ; i++){
            addressBook->contacts[i] = addressBook->contacts[i+1];

        }
        addressBook->contactCount--;
        printf("Contact deleted successfully\n");
    }
    else{
        printf("Deletion cancelled\n");
    }
   
}


int valname(char *name){
    int res=0;
    int len = strlen(name);
    for(int i=0; i<len ; i++){
        if((name[i] >= 'A' && name[i] <='Z') || (name[i] >= 'a' && name[i] <= 'z') || (name[i] == ' ') || (name[i] == '.')){
               res = 1 ;
        }
        else{
            res = 0;
            break;
        }
    }
    return res;
}


int valphone(char *number){
    int res=0;
    int len = strlen(number);
    for(int i=0; i<len; i++){
        if(number[i] >= '0' && number[i] <= '9'){
            res = 1;
        }
        else{
            res = 0;
            printf("The number entered is not correct\n");
            break;
        }
    }
    return res;
}


int duphn(char *number, AddressBook *addressbook)
{
    int flag = 1;
    for(int i=0; i<addressbook->contactCount; i++){
        int pcpm = strcmp(addressbook->contacts[i].phone, number);
        if(pcpm == 0){
            flag = 0;
            printf("Entered number is already present in database\n");
        }
        
    }
    return flag;
}


int valemail(char *email) {
    int len = strlen(email);
    int atCount = 0;

    // Length check (minimum reasonable size: a@b.com = 7 chars)
    if (len < 7) {
        printf("The entered email is not correct\n");
        return 0;
    }

    
    for (int i = 0; i < len; i++) {
        char c = email[i];

        if ((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9') ||
            c == '@' || c == '-' || c == '_' || c == '.') {
            
            if (c == '@') {
                atCount++;
            }
        } else {
            printf("The entered email is not correct\n");
            return 0;
        }
    }

    
    if (atCount != 1) {
        printf("The entered email is not correct\n");
        return 0;
    }

    
    if (email[0] == '@' || email[len - 1] == '@') {
        printf("The entered email is not correct\n");
        return 0;
    }

    
    if (strcmp(email + len - 4, ".com") != 0) {
        printf("The entered email is not correct\n");
        return 0;
    }

    return 1;
}
int duemail(char *mail, AddressBook *addressbook)
{
    int flag = 1;
    for(int i=0; i<addressbook->contactCount ; i++){
        int len = strcmp(addressbook->contacts[i].email, mail);
        if(len == 0){
            flag = 0;
            break;
        }
    }
    return flag;
}