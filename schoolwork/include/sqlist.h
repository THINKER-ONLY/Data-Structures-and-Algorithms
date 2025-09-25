#ifndef SQLIST_H
#define SQLIST_H

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 50 

typedef int Status;
typedef int ElementType;

typedef struct{
    ElementType *data;
    int length;
    int capacity;
} sqlist;

Status SqList_Init(SqList *L);
Status SqList_Destroy(SqList *L);
Status SqList_Insert(SqList *L, int i, ElementType e);
Status SqList_Delete(SqList *L, int i, ElementType *e);
int SqList_Find(const SqList *L, ElementType e);
void SqList_Print(const SqList *L);
void SqList_Partition(SqList *L);

#endif