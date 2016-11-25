#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode Next;
};
typedef PtrToNode List;

void Attach(ElementType x, List* pCurrent) {
    List L;
    L = (List)malloc(sizeof(struct Node));
    L->Data = x;
    L->Next = NULL;
    (*pCurrent)->Next = L;
    *pCurrent = L;
}

List Read() {
    List L, current;
    int N, x;
    scanf("%d", &N);
    L = (List)malloc(sizeof(struct Node));
    L->Next = NULL;
    current = L;
    while(N--) {
        scanf("%d", &x);
        Attach(x, &current);
    }
    return L;
}

void Print(List L) {
    L = L->Next;
    int flag = 0;
    if(!L) {
        printf("NULL\n");
        return;
    }
    while(L) {
        if(!flag)
            flag = 1;
        else
            printf(" ");
        printf("%d", L->Data);
        L = L->Next;
    }
    printf("\n");
}

List Merge(List L1, List L2) {
    List L, t1 = L1, t2 = L2, current, t;
    t1 = t1->Next;
    t2 = t2->Next;
    L = (List)malloc(sizeof(struct Node));
    L->Next = NULL;
    current = L;
    while(t1 && t2) {
        if(t1->Data < t2->Data) {
            Attach(t1->Data, &current);
            t1 = t1->Next;
        }
        else if(t1->Data > t2->Data) {
            Attach(t2->Data, &current);
            t2 = t2->Next;
        }
        else {
            Attach(t1->Data, &current);
            Attach(t2->Data, &current);
            t1 = t1->Next;
            t2 = t2->Next;
        }
    }
    while(t1) {
        Attach(t1->Data, &current);
        t1 = t1->Next;
    }
    while(t2) {
        Attach(t2->Data, &current);
        t2 = t2->Next;
    }
    L1->Next = NULL;
    L2->Next = NULL;
    return L;
}

int main() {
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}
