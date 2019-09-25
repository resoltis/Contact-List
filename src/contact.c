//
//  contact.c
//  David Cordes
//  CS100- 001
//  Created by Reagan Soltis on 11/29/17.
//
// This program allows you to create a list of contacts with information. The contacts have the name as well as a list of information. The program allows you to put the contacts and/or information in order as well as remove information and/or contacts at any given time. At any time, the user can print one contact or all of the contacts and quit when finished.

#include <stdio.h>
#include "contact.h"
#include <stdbool.h>


//Goes through the list to see if a contact with the specified name already exists
int findName(Contact *myContacts, char *search){
    Contact * current = myContacts;
    
    while (current != NULL) {
        if ( strcmp(current ->name, search) == 0){
            return 1;
        }
        else {
            return 0;
        }
    }
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// add a new contact to your list of contacts
//	   1. Make sure a contact by that name does not exist (print an error message and exit if it exists)
//	   2. Add a new contact with that name (add-at-front)
Contact* addContact(Contact *myContacts, char *contactName) {
    
    if (myContacts == NULL) {
        Contact* Node;
        Node = malloc( sizeof(Contact));
        Node -> name = contactName;
        Node -> next = NULL;
        Node -> information = NULL;
        myContacts = Node;
        return myContacts;
        
    }
    if ( findName(myContacts, contactName) == 1) {
        printf("\tError: This contact name already exists");
        return 0;
    }
    Contact * Node;
    Node = malloc( sizeof(Contact));
    Node -> name = contactName;
    Node -> next = myContacts;
    Node -> information = NULL;
    myContacts = Node;
    
    return myContacts;
    
}


/////////////////////////////////////////////////////////////////////////////////////////////
// adds a new piece of inforamtion to the specified contact
//   1. Make sure a contact by that name exists (so you can add information to it)
//   2. If the informational item already exists, update the information's value to the new value
//   3. Otherwise, add the piece of information to the end of the contact's information list (add-at-end)

void addInformation(Contact *myContacts, char *contactName, char *infoName, char *infoValue) {
    Contact *current;
    Contact *newCont = NULL;
    Info* currentInfo = NULL;
    bool exists = false;
    
    //Check if the contact exists
    for (current = myContacts; current != NULL; current = current -> next) {
        if (strcmp(current -> name, contactName) == 0) {
            exists = true;
            newCont = current;
            currentInfo = current -> information;
        }
    }
    if (exists == false) {
        printf("\tError: %s is not an existing name\n", contactName);
        return;
    }
    //Check if the infomation exists and if so, update it
    if (currentInfo != NULL) {
        Info *newInfo;
        for (newInfo = currentInfo; newInfo != NULL; newInfo = newInfo -> next) {
            if (strcmp(newInfo->name, infoName) == 0) {
                printf("\t%s already exists, replacing the information\n", newInfo->name);
                newInfo->value = infoValue;
                return;
            }
        }
    }
    
        //Information does not exist, create it
        Info* newInfo;
        newInfo = malloc(sizeof(Info));
        newInfo -> name = malloc(strlen(infoName) * sizeof(char));
        newInfo -> value = malloc(strlen(infoValue) * sizeof(char));
        
        strcpy(newInfo -> name, infoName);
        strcpy(newInfo -> value, infoValue);
        newInfo -> next = NULL;
        
        //add it to the end of the list
        if (newCont -> information == NULL) {
            newCont -> information = newInfo;
            return;
            }
    
        //Find the last term
    for (currentInfo = newCont -> information; currentInfo != NULL; currentInfo = currentInfo -> next) {
        if (currentInfo -> next == NULL) {
            currentInfo -> next = newInfo;
            return;
        }
    }
    return;
}



/////////////////////////////////////////////////////////////////////////////////////////////
// prints all the information for a given contact
//	1. Make sure a contact with that name exists
//	2. Print the name of the contact
//	3. print all the informational items <name|value> associated with that contact
void printContact(Contact *myContacts, char *contactName) {
    for (Contact* currentContact = myContacts; currentContact != NULL; currentContact = currentContact-> next) {
        if (strcmp(currentContact->name, contactName) == 0) {
            printf("\tContact name is: %s\n", currentContact->name);
            if (currentContact -> information == NULL) {
                return;
            }
            Info *currentInfo = currentContact -> information;
            while (currentInfo != NULL) {
                printf("\t\t%s: %s\n", currentInfo->name, currentInfo->value);
                currentInfo = currentInfo->next;
            }
        }
    }
       return;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// returns the size of a given contact list
//	Iterate through the contact list to count the number of contacts, return that count
int count(Contact *myContacts) {
    int count = 0;
    Contact *currentContact;
    
    for (currentContact = myContacts; currentContact != NULL; currentContact = currentContact -> next) {
        count += 1;
        }
    return count;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// prints all your contacts
//	For each contact
//	   a.  Print the name of the contact
//	   b.  Print all the <information name|information value> pairs in that contact
//	Note: this code can call other functions as needed
void print(Contact *myContacts) {
    
    Contact* currentContact;
    
    for (currentContact = myContacts; currentContact != NULL; currentContact = currentContact -> next) {
        printContact(currentContact, currentContact -> name);
    }
    return;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// add a new contact (in alphabetical order)
//	1. Make sure a contact by that name does not exist
//	2. Add a new contact with that name (add-in-order)
Contact *addContactOrdered(Contact *myContacts, char *contactName) {
    
    Contact* currentContact;
    
    if (myContacts == NULL) return addContact(myContacts, contactName);
    
    for (currentContact = myContacts; currentContact != NULL; currentContact = currentContact -> next) {
        if (strcmp(currentContact->name, contactName) == 0) {
            printf("\tError: %s already exists\n", currentContact->name);
            return myContacts;
        }
    }
    
    if (strcmp(myContacts -> name, contactName) > 0) {
        return addContact(myContacts, contactName);
    }
    for (currentContact = myContacts; currentContact->next != NULL; currentContact = currentContact-> next) {
        if (strcmp(currentContact -> next -> name, contactName) < 0) continue;
        
        currentContact -> next = addContact(currentContact->next, contactName);
        return myContacts;
    }
    currentContact->next = addContact(NULL, contactName);
    return myContacts;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// adds a new info to the specified contact (in alphabetical order)
//	1. Make sure a contact by that name exists (so you can add an info to it)
//	2. If the informational item already exists, update the item (replace its value with the new value)
//	3. Otherwise, add the new info to the contact (add-in-order)
void addInformationOrdered(Contact *myContacts, char *contactName, char *infoName, char *infoValue) {
    
    //Error Message
    if (myContacts == NULL) {
        printf("Error: The list is empty\n");
        return;
    }
    //Information is already in the list
    while (myContacts != NULL) {
        if (strcmp(myContacts->name, contactName) == 0) {
            if (myContacts-> information != NULL) {
                Info *node = myContacts -> information;
                while (node) {
                    if (strcmp(node->name, infoName) == 0) {
                        printf("\t Already exists, replacing the information with %s\n", infoValue);
                        node -> name = infoName;
                        node -> value = infoValue;
                        return;
                    }
                    node = node -> next;
                }
            }
            //Adding Information
            Info* newInfo;
            newInfo = malloc(sizeof(Info));
            newInfo -> value = malloc(strlen(infoValue) + 1);
            newInfo -> name = malloc (strlen(infoName) + 1);
            strcpy(newInfo-> value, infoValue);
            strcpy(newInfo-> name, infoName);
            newInfo -> next = NULL;
            
            if (myContacts -> information == NULL) {
                myContacts -> information = newInfo;
                return;
            }
            //Change it to alphabetical order
            if (strcmp(infoName, myContacts -> information -> name) < 0) {
                newInfo -> next = myContacts -> information;
                myContacts -> information = newInfo;
                return;
            
            }
            Info* previous = myContacts -> information;
            Info* current = myContacts -> information -> next;
            while (current && strcmp(current-> name, infoName) < 0) {
                previous = current;
                current = current -> next;
            }
            previous -> next = newInfo;
            newInfo -> next = current;
            return;
        }
        myContacts = myContacts -> next;
    }
    return;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// remove information from a contact
//	1. Make sure a contact with that name exists
//	2. Make sure the informational item exists in that contact
//	3. Remove that piece of information from the contact
void removeInformation(Contact *myContacts, char *contactName, char *infoName) {
    
    //Error Message
    if (myContacts == NULL) {
        printf("Error: The list is empty\n");
        return;
    }
    if (strcmp(myContacts->information->name, infoName) == 0) {
        Info *node = myContacts->information->next;
        free(myContacts->information);
        myContacts->information = node;
        return;
    }
    Info *previous = myContacts -> information;
    Info *current = myContacts -> information -> next;
    while (current && strcmp(current->name, infoName) != 0) {
        previous = current;
        current = current -> next;
    }
    if (current == NULL) {
        printf("The name does not exist.\n");
        return;
    }
    previous -> next = current -> next;
    free (current);
    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// remove a contact (and all the informational items for that contact)
//	1. Make sure a contact with that name exists
//	2. Remove that contact
Contact *removeContact(Contact *myContacts, char *contactName) {
    
    //removing when there is an empty list
    if (myContacts == NULL){
        printf("Empty list: There are no contacts to remove\n");
        return myContacts;
    }
    //removing the first contact
    if (strcmp(myContacts -> name, contactName) == 0) {
        Contact* node = myContacts -> next;
        free(myContacts);
        return node;
    }
    //removing for every other case
    Contact* previous = myContacts;
    Contact* current = myContacts -> next;
    while (current && strcmp(current -> name, contactName) != 0) {
        previous = current;
        current = current -> next;
    }
    //Error message
    if (current == NULL) {
        printf("Error: the name does not exist\n");
        return myContacts;
    }
    
    //remove the contact
    previous -> next = current -> next;
    free(current);
    return myContacts;
}
