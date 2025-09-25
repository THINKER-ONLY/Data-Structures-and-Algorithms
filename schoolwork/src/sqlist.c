#include "sqlist.h"

Status SqList_Init(SqList *L) {
    L->data = (ElementType *)malloc(LIST_INIT_SIZE * sizeof(ElementType *));
    if (!L->data){
        return ERROR;
    }
    L->length = 0;
    L->capacity = LIST_INIT_SIZE;
    return OK;
}

Status SqList_Destroy(SqList *L) {
    if (L->data){
        free(L->data);
        L->data = NULL;
    }
    L->length = 0;
    L->capacity = 0;
    return OK;
}

Status SqList_Insert(SqList *L, int i, ElementType e) {
    if (i < 1 || i > L->length + 1) {
        return ERROR;
    }
    if (L->length >= L->capacity) {
        ElementType *new_base = (ElementType *)realloc(L->data, (L->capacity + LIST_INCREMENT) * sizeof(ElementType *))
        if (!L->new_base){
            return ERROR;
        }
        L->data = new_base;
        L->capacity += LIST_INCREMENT;
    }
    for(int j=L->length; j>i; j--) {
        L->data[j] = L->data[j-1]
    }
    L->data[i-1] = e;
    L->length++;
    return OK;
}

Status SqList_Delete(SqList *L, int i, ElementType *e);
int SqList_Find(const SqList *L, ElementType e);
void SqList_Print(const SqList *L);