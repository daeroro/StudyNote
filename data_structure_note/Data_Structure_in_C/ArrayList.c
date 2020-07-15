#include <stdio.h>
#include "ArrayList.h"

void ListInit(List * plist)
{
    plist->numOfData = 0;
    plist->curPos = -1;
}

void LInsert(List * plist, LData data)
{
    if(plist->numOfData >= LIST_LEN)
    {
        printf("리스트가 꽉 찼습니다\n");
        return;
    }

    plist->arr[plist->numOfData] = data;
    plist->numOfData++;
}

int LFirst(List * plist, LData * pdata)
{
    if(plist->numOfData == 0)
    {
        printf("리스트가 비었습니다\n");
        return FALSE;
    }

    *pdata = plist->arr[0];
    plist->curPos = 0;
    return TRUE;
}

int LNext(List * plist, LData * pdata)
{
    if(plist->curPos >= plist->numOfData-1)
    {
        return FALSE;
    }

    plist->curPos++;
    *pdata = plist->arr[plist->curPos];

    return TRUE;
}

LData LRemove(List * plist)
{
    LData rData = plist->arr[plist->curPos];
    int rPos = plist->curPos;
    int rNum = plist->numOfData;

    for(int i=rPos; i<rNum-1; i++)
    {
        plist->arr[i] = plist->arr[i+1];
    }

    plist->numOfData--;
    plist->curPos--;

    return rData;
}

int LCount(List * plist)
{
    return plist->numOfData;
}