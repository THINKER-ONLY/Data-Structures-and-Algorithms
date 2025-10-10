#ifndef SQSTACK_H
#define SQSTACK_H

#include <stdio.h>
#include <stdlib.h>

#ifndef STATUS_DEFINED
#define STATUS_DEFINED
typedef int Status;
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#endif

typedef int ElementType;

typedef struct
{
    ElementType *base;
    int top;
    int capacity;
} SqStack;

Status SqStack_Init(SqStack *S);

void SqStack_Destroy(SqStack *S);

int SqStack_IsEmpty(const SqStack *S);

Status SqStack_Push(SqStack *S, ElementType e);

Status SqStack_Pop(SqStack *S, ElementType *e);

Status SqStack_GetTop(const SqStack *S, ElementType *e);

#endif