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
        ElementType *new_base = (ElementType *)realloc(L->data, (L->capacity + LIST_INCREMENT) * sizeof(ElementType *));
        if (!new_base){
            return ERROR;
        }
        L->data = new_base;
        L->capacity += LIST_INCREMENT;
    }
    for(int j=L->length; j>i; j--) {
        L->data[j] = L->data[j-1];
    }
    L->data[i-1] = e;
    L->length++;
    return OK;
}

Status SqList_Delete(SqList *L, int i, ElementType *e) {
    if (i<1 || i > L->length) {
        return ERROR;
    }
    *e = L->data[i-1];
    for(int j=i; j < L->length; j++) {
        L->data[j-1] = L->data[j];
    }
    L->length--;
    return OK;
}

int SqList_Find(const SqList *L, ElementType e) {
    for(int j=0; j<L->length; j++) {
        if(L->data[j]==e) {
            return j+1;
        }
    }
    return 0;
}

void SqList_Print(const SqList *L) {
    if (L->length == 0) {
        printf("SqList is Empty\n");
        return;
    }
    for (int i = 0; i < L->length; ++i) {
        printf("%d ", L->data[i]);
    }
    printf("\n");
}

void SqList_Partition(SqList *L) {
    int low = 0;
    int high = L->length-1;
    ElementType pivot = L->data[low];
    if (L->length < 2) {
        return;
    }
    while (low < high) {

        while (low < high && L->data[high] > pivot) {
            high--;
        }
        if (low < high) {
            L->data[low] = L->data[high];
            low++;
        }

        while (low < high && L->data[low] <= pivot) {
            low++;
        }
        if (low < high) {
            L->data[high] = L->data[low];
            high--;
        }
    }
    L->data[low] = pivot;
}