#include <stdio.h>
#include "sqlist.h"

int main() {
    SqList list;
    SqList_Init(&list);

    int data[] = {72, 6, 55, 88, 59, 42, 46, 73, 49, 91};
    int n = sizeof(data) / sizeof(data[0]);

    for(int i=0; i<n; i++){
        SqList_Insert(&list, i+1, data[i]);
    }
    printf("\n");
    SqList_Print(&list);

    printf("\n\n");
    SqList_Partition(&list);

    printf("\n");
    SqList_Print(&list);
    
    SqList_Destroy(&list);

    return 0;
}