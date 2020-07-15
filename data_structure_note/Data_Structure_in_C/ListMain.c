#include <stdio.h>
#include "ArrayList.h"
#include "NameCard.h"

int main(void)
{
    List list;
    ListInit(&list);
    NameCard * p[3];
    NameCard * np;

    ListInit(&list);

    p[0] = MakeNameCard("가가", "010-1111-1111");
    LInsert(&list, p[0]);

    p[1] = MakeNameCard("나나", "010-2222-2222");
    LInsert(&list, p[1]);

    p[2] = MakeNameCard("다다", "010-3333-3333");
    LInsert(&list, p[2]);

    if(LFirst(&list, &np))
    {
        ShowNameCardInfo(np);

        while(LNext(&list, &np))
        {
            ShowNameCardInfo(np);
        }
    }

    if(LFirst(&list, &np))
    {
        if(!NameCompare(np, "나나"))
            ShowNameCardInfo(np);

        while(LNext(&list, &np))
        {
            if(!NameCompare(np, "나나"))
                ShowNameCardInfo(np);
        }
    }

    if(LFirst(&list, &np))
    {
        if(!NameCompare(np, "다다"))
            ChangePhoneNum(np, "010-4444-4444");

        while(LNext(&list, &np))
        {
            if(!NameCompare(np, "다다"))
                ChangePhoneNum(np, "010-4444-4444");
        }
    }

    if(LFirst(&list, &np))
    {
        ShowNameCardInfo(np);

        while(LNext(&list, &np))
        {
            ShowNameCardInfo(np);
        }
    }

    if(LFirst(&list, &np))
    {
        if(!NameCompare(np, "다다"))
            LRemove(&list);

        while(LNext(&list, &np))
        {
            if(!NameCompare(np, "다다"))
                LRemove(&list);
        }
    }

    if(LFirst(&list, &np))
    {
        ShowNameCardInfo(np);

        while(LNext(&list, &np))
        {
            ShowNameCardInfo(np);
        }
    }

    return 0;
}