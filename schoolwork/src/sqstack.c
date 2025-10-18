#include "maze_types.h"
#include "sqstack.h"

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

Status SqStack_Init(SqStack *S)
{
    if (S == NULL) return ERROR;
    S->base = (ElementType *)malloc(STACK_INIT_SIZE * sizeof(ElementType));
    if (!S->base) return ERROR;
    S->top = 0;
    S->capacity = STACK_INIT_SIZE;
    return OK;
}

void SqStack_Destroy(SqStack *S)
{
    if (S == NULL) return;
    if (S->base) 
    {
        free(S->base);
        S->base = NULL;
    }
    S->top = 0;
    S->capacity = 0;
}

int SqStack_IsEmpty(const SqStack *S)
{
    if (S == NULL) return TRUE;
    return S->top == 0 ? TRUE : FALSE;
}

Status SqStack_Push(SqStack *S, ElementType e)
{
    if (S == NULL) return ERROR;
    if (S->top >= S->capacity)
    {
        ElementType *newbase = (ElementType *)realloc(S->base, (S->capacity + STACK_INCREMENT) * sizeof(ElementType));
        if (!newbase) return ERROR;
        S->base = newbase;
        S->capacity += STACK_INCREMENT;
    }
    S->base[S->top] = e;
    S->top++;
    return OK;
}

Status SqStack_Pop(SqStack *S, ElementType *e)
{
    if (S == NULL || e == NULL) return ERROR;
    if (SqStack_IsEmpty(S)) return ERROR;
    S->top--;
    *e = S->base[S->top];
    return OK;
}

Status SqStack_GetTop(const SqStack *S, ElementType *e)
{
    if (S == NULL || e == NULL) return ERROR;
    if (SqStack_IsEmpty(S)) return ERROR;
    *e = S->base[S->top - 1]; 
    return OK;
}