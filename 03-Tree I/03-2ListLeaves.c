#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MaxTree 10
#define Tree int
#define Null -1  // not NULL

struct QNode {
    int *Data;
    int Front, Rear;  
    int MaxSize;        
};
typedef struct QNode *Queue;
 
Queue CreateQueue( int MaxSize )
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (int *)malloc(MaxSize * sizeof(int));
    Q->Front = Q->Rear = 0;
    Q->MaxSize = MaxSize;
    return Q;
}
 
int IsFull( Queue Q )
{
    return ((Q->Rear+1)%Q->MaxSize == Q->Front);
}
 
void AddQ( Queue Q, int X )
{
    if ( IsFull(Q) ) {
        printf("full queue.");
    }
    else {
        Q->Rear = (Q->Rear+1)%Q->MaxSize;
        Q->Data[Q->Rear] = X;
    }
}
 
int IsEmpty( Queue Q )
{
    return (Q->Front == Q->Rear);
}
 
int DeleteQ( Queue Q )
{
    if ( IsEmpty(Q) ) { 
        printf("empty queue.");
    }
    else  {
        Q->Front =(Q->Front+1)%Q->MaxSize;
        return Q->Data[Q->Front];
    }
}

struct TreeNode {
    Tree Left;
    Tree Right;
} T[MaxTree];

Tree BuildTree(struct TreeNode T[]) {
    int N, Root, i;
    char cl, cr;
    scanf("%d\n", &N); //number of nodes
    if(N == 0) return Null;
    int check[N];
    if(N) {
        for(i = 0; i < N; i++) 
            check[i] = 0; // if used by other nodes
        for(i = 0; i < N; i++) {
            scanf("%c %c\n", &cl, &cr);
            // index of left son
            if(cl != '-') {
                T[i].Left = cl - '0';
                check[T[i].Left] = 1;
            }
            else T[i].Left = Null;
            // index of right son
            if(cr != '-') {
                T[i].Right = cr - '0';
                check[T[i].Right] = 1;
            }
            else T[i].Right = Null;
        }
        // the root should not be used by any other nodes
        for(i = 0; i < N; i++)
            if(!check[i]) break;
        Root = i;
    }
    return Root;
}

void ListLeaves(Tree R) {
    if(R == Null) 
        return;
    Tree r;
    Queue Q;
    Q = CreateQueue(MaxTree);
    AddQ(Q, R);
    int result[10], i = 0, k;
    while(!IsEmpty(Q)) {
        r = DeleteQ(Q);
        if(T[r].Left == Null && T[r].Right == Null){
            result[i] = r;
            i++;
        }
        if(T[r].Left != Null) AddQ(Q, T[r].Left);
        if(T[r].Right != Null) AddQ(Q, T[r].Right);
    }
    for(k = 0; k < i - 1; k++)
        printf("%d ", result[k]);
    printf("%d", result[i-1]);
}

int main() {
    Tree R;
    R = BuildTree(T);
    ListLeaves(R);
    return 0;
}
