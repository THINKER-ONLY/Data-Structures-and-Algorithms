#include "sqqueue.h"
#include <stdlib.h>

Status SqQueue_Init(SqQueue *Q)
{
    if (Q == NULL) return ERROR;
    Q->base = (ElementType *)malloc(MAX_QUEUE_SIZE * sizeof(ElementType));
    if (!Q->base) return ERROR;
    Q->head = 0;
    Q->tail = 0;
    return OK;
}

void SqQueue_Destroy(SqQueue *Q)
{
    if (Q == NULL) return ERROR;
    if (Q->base) 
    {
        free(Q->base);
        Q->base = NULL;
    }
    Q->head = 0;
    Q->tail = 0;
    return OK;
}

int SqQueue_IsEmpty(const SqQueue *Q)
{
    if (Q == NULL) return 1;
    return Q->head == Q->tail;
}

int SqQueue_IsFull(const SqQueue Q)
{
    return (Q.head + 1) % MAX_QUEUE_SIZE == Q.tail;
}

int SqQueue_GetLength(const SqQueue Q)
{
    return (Q.head - Q.tail + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

Status SqQueue_EnQueue(SqQueue *Q, ElementType e)
{
    if (SqQueue_IsFull(*Q)) return ERROR;
    Q->base[Q->tail] = e;
    Q->tail = (Q->tail + 1) % MAX_QUEUE_SIZE;
    return OK;
}

Status SqQueue_DeQueue(SqQueue *Q, ElementType *e)
{
    if (SqQueue_IsEmpty(Q)) return ERROR;
    *e = Q->base[Q->head];
    Q->head = (Q->head + 1) % MAX_QUEUE_SIZE;
    return OK;
}