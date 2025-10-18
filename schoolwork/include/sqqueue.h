#ifndef SQQUEUE_H
#define SQQUEUE_H

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
#define MAX_QUEUE_SIZE 10

typedef struct
{
    ElementType *base;
    int head;
    int tail;
} SqQueue;

Status SqQueue_Init(SqQueue *Q);
void SqQueue_Destroy(SqQueue *Q);
int SqQueue_IsEmpty(const SqQueue *Q);
int SqQueue_IsFull(const SqQueue Q);
int SqQueue_GetLength(const SqQueue Q);
Status SqQueue_EnQueue(SqQueue *Q, ElementType e);
Status SqQueue_DeQueue(SqQueue *Q, ElementType *e);

#endif