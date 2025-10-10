#include "linklist.h"

Status LinkList_Init(LinkList *L)
{
    if (L == NULL) return ERROR;
    *L = (LinkList)malloc(sizeof(LNode));
    if (*L == NULL) return ERROR;
    (*L)->next = NULL;
    return OK;
}

void LinkList_Create_HeadInsert(LinkList L, ElementType data[], int n)
{
    if (L == NULL || data == NULL || n <= 0) return;
    L->next = NULL;
    for (int i = 0; i < n; i++)
    {
        LNode *newnode = (LNode *)malloc(sizeof(LNode));
        if (!newnode) return;
        newnode->data = data[i];
        newnode->next = L->next;
        L->next = newnode;
    }
}

void LinkList_Create_TailInsert(LinkList L, ElementType data[], int n)
{
    if (L == NULL || data == NULL || n <= 0) return;
    LNode *tail = L;
    for (int i = 0; i < n; i++)
    {
        LNode *newnode = (LNode *)malloc(sizeof(LNode));
        if (!newnode) return;
        newnode->data = data[i];
        newnode->next = NULL;
        tail->next = newnode;
        tail = newnode;
    }
}

void LinkList_Destory(LinkList *L)
{
    if (L == NULL || *L == NULL) return;
    LNode *p = *L;
    while (p != NULL)
    {
        LNode *temp = p;
        p = p->next;
        free(temp);
    }
    *L = NULL;
}

Status LinkList_Insert(LinkList L, int i, ElementType e)
{
    if (L == NULL || i < 1) return ERROR;
    LNode *p = L;
    int j = 0;
    while (p != NULL && j < i - 1)
    {
        p = p->next;
        j++;
    }
    if (p == NULL) return ERROR;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    if (!s) return ERROR;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

Status LinkList_Delete(LinkList L, int i, ElementType *e)
{
    if (L == NULL || e == NULL || i < 1) return ERROR;
    LNode *p = L;
    int j = 0;
    while(p != NULL && j < i - 1)
    {
        p = p->next;
        j++;
    }
    if (p == NULL || p->next == NULL) return ERROR;
    LNode *q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);
    return OK;
}

LNode* LinkList_LocateElem(LinkList L, ElementType e)
{
    if (L == NULL) return NULL;
    LNode *p = L->next;
    while (p != NULL && p->data != e) {
        p = p->next;
    }
    return p;
}

void LinkList_Traverse(LinkList L)
{
    if (L == NULL) {
        printf("链表未初始化或为 NULL。\n");
        return;
    }
    LNode *p = L->next;
    if (p == NULL) {
        printf("链表为空。\n");
        return;
    }
    while (p != NULL) {
        printf("%d", p->data);
        if (p->next) printf(" -> ");
        p = p->next;
    }
    printf(" -> NULL\n");
}