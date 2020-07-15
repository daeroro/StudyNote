#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NameCard.h"

NameCard * MakeNameCard(char * name, char * phone)
{
    NameCard * new = (NameCard*)malloc(sizeof(NameCard));
    strncpy(new->name, name, NAME_LEN);
    strncpy(new->phone, phone, PHONE_LEN);

    return new;
}

void ShowNameCardInfo(NameCard * pcard)
{
    printf("name : %s phone : %s\n", pcard->name, pcard->phone);
}

int NameCompare(NameCard * pcard, char * name)
{
    return strcmp(pcard->name, name);
}

void ChangePhoneNum(NameCard * pcard, char * phone)
{
    strcpy(pcard->phone, phone);
}