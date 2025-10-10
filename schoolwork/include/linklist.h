#ifndef LINKLIST_H
#define LINKLIST_H

#include <stdio.h>
#include <stdlib.h>

#ifndef STATUS_DEFINED
#define STATUS_DEFINED
typedef int Status;
#define OK 1
#define ERROR 0
#endif

typedef int ElementType;

typedef struct LNode
{
    ElementType data;
    struct LNode *next;
} LNode, *LinkList;

Status LinkList_Init(LinkList *L);

void LinkList_Create_HeadInsert(LinkList L, ElementType data[], int n);

void LinkList_Create_TailInsert(LinkList L, ElementType data[], int n);

void LinkList_Destory(LinkList *L);

Status LinkList_Insert(LinkList L, int i, ElementType e);

Status LinkList_Delete(LinkList L, int i, ElementType *e);

LNode* LinkList_LocateElem(LinkList L, ElementType e);

void LinkList_Traverse(LinkList L);

#endif