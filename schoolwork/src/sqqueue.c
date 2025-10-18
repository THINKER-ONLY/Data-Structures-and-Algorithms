#include "sqqueue.h"

SqQueue SqQueue_Init(SqQueue *Q)
{
    if (Q == NULL) return ERROR;
    Q->base = (ElementType *)malloc(MAX_QUEUE_SIZE * sizeof(SqQueue))
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
    S->head=0;
    S->tail=0;
}

int SqQueue_IsEmpty(const SqQueue *Q)
{
    if (Q == NULL) return TRUE;
    return Q->top == 0 ? TRUE : FALSE;
}
int SqQueue_IsFull(const SqQueue Q);
int SqQueue_GetLength(const SqQueue Q);
Status SqQueue_EnQueue(SqQueue *Q, ElementType e);
Status SqQueue_DeQueue(SqQueue *Q, ElementType *e);