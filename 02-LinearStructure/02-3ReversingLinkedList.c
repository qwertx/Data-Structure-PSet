#include <stdio.h>
#include <stdlib.h>

typedef struct ANode *Arr;
struct ANode{
    int AData;
    int NextAddr;
} A[100001];

typedef struct LNode* List;
struct LNode{
    int LData;
    int Addr;
    List NextL;
};

int N, K, ActualLength = 0;

void ReadData() {
    int first, i;
    int addr, data, next;
    scanf("%d %d %d", &first, &N, &K);
    A[100000].AData = first; // remember the first index
    for(i = 0; i < N; i++) {
        scanf("%d %d %d", &addr, &data, &next);
        A[addr].AData = data;
        A[addr].NextAddr = next;
    }
    return;
}

List BuildLink() {
    int current;
    List Head, NN;
    List PtrL;
    current = A[100000].AData;
    Head = (List)malloc(sizeof(struct LNode));
    PtrL = Head;
    while(current != -1) { // add nodes
        NN = (List)malloc(sizeof(struct LNode));
        NN->LData = A[current].AData;
        NN->Addr = current;
        NN->NextL = NULL;
        PtrL->NextL = NN;
        current = A[current].NextAddr;
        PtrL = PtrL->NextL;
        ActualLength++;
    }
    return Head;
}

List Reverse(List Head) {
    int count = 1;
    List New, Old, Temp;
    New = Head->NextL;
    Old = New->NextL;

    while(count < K) {
        Temp = Old->NextL;
        Old->NextL = New;
        New = Old;
        Old = Temp;
        count++;
    }
    Head->NextL->NextL = Old;
    return New;
}

int main() {
    List currentHead, result;
    int i, time, rest, isFirstPrint = 1; 
    ReadData(); 
    if(N == 1) {
        printf("%05d %d -1", A[100000].AData, A[A[100000].AData].AData);
        return 0;
    }
    currentHead = BuildLink();
    time = ActualLength / K;
    // reverse and print
    while(time--) {
        result = Reverse(currentHead);
        currentHead->NextL = result;
        i = 0;
        while(i < K) { 
            if((result->NextL != NULL) && !isFirstPrint)
                printf("%05d\n%05d %d ", result->Addr, result->Addr, result->LData);
            else if(result->NextL == NULL)
                printf("%05d\n%05d %d -1", result->Addr, result->Addr, result->LData);
            if(isFirstPrint) {
                printf("%05d %d ", result->Addr, result->LData);
                isFirstPrint = 0;
            }
            result = result->NextL;
            currentHead->NextL = currentHead->NextL->NextL;
            i++;
        }
    }
    // deal with the remain numbers
    while(currentHead->NextL != NULL) {
        if(currentHead->NextL->NextL != NULL) // not the last print
            printf("%05d\n%05d %d ", currentHead->NextL->Addr, currentHead->NextL->Addr, currentHead->NextL->LData);
        else
            printf("%05d\n%05d %d -1", currentHead->NextL->Addr, currentHead->NextL->Addr, currentHead->NextL->LData);
        currentHead->NextL = currentHead->NextL->NextL;
    }
    return 0;
}
