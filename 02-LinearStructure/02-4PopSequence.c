#include <stdio.h>
#include <stdlib.h>

int M, N, K;

typedef struct SNode *Stack;
struct SNode{
    int Data[1000];
    int Top;
};

int Push(Stack PtrS, int item){
    if(PtrS->Top == M - 1){
        return -1;
    }
    else{
        PtrS->Data[++(PtrS->Top)] = item;
        return 0;
    }
}

int Pop(Stack PtrS){
    if(PtrS->Top == -1){
        printf("Empty Stack.");
        return -1;
    }
    else{
        return (PtrS->Data[(PtrS->Top)--]);
    }
}

int Check(int arr[]) {
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->Top = -1;
    int current = 1, popped = 0, i = 0, flag, s;
    for( ; current <= arr[i]; current++) { // first number
        flag = Push(S, current);
        if(flag == -1) return -1;
    }
    while(popped != N) {
        if(S->Data[S->Top] == arr[i]) {
            s = Pop(S);
            i++;
            popped++;
        }
        else if((S->Top == -1) || S->Data[S->Top] < arr[i]) {
            while((S->Top == -1) || ((S->Data[S->Top] != arr[i]) && (current <= arr[i]))) {
                flag = Push(S, current);
                if(flag == -1) return -1;
                current++;
            }
        }
        else 
            return -1;
    }
    return 0;
}

int main() {
    int i, j, result;
    scanf("%d %d %d", &M, &N, &K);
    int arr[N];
    for(i = 0; i < K; i++) {
        for(j = 0; j < N; j++)
            scanf("%d", &arr[j]);
        result = Check(arr);
        if(result == 0) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
