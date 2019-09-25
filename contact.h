//
//  contact.h
//  Average
//
//  Created by Reagan Soltis on 11/29/17.
//  Copyright © 2017 Reagan Soltis. All rights reserved.
//

#ifndef contact_h
#define contact_h


#endif /* contact_h */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct info {
    char *name;
    char *value;
    struct info *next;
} Info;

////////////////////////////////////////////////////////////////////////////////////////

typedef struct contact {
    char *name;
    Info *information;
    struct contact *next;
} Contact;

////////////////////////////////////////////////////////////////////////////////////////

Contact* addContact(Contact *, char *);
void addInformation(Contact *, char *, char *, char *);
void printContact(Contact *, char *);
int count(Contact *);
void print(Contact *);
Contact* addContactOrdered(Contact *, char *);
void addInformationOrdered(Contact *, char *, char *, char *);
Contact *removeContact(Contact *, char *);
void removeInformation(Contact *, char *, char *);

////////////////////////////////////////////////////////////////////////////////////////
