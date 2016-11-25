#include <stdio.h>
#include <stdlib.h>

typedef int Vertex;

struct QNode {
    int *Data;
    int rear;
    int front;
    int size;
};
typedef struct QNode *Queue;

struct GNode {
    int Nv;
    int *A;
};
typedef struct GNode *Graph;

int *Visited;

Queue CreateQueue(int N) {
    Queue Q;
    Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (int*)malloc(N * sizeof(int));
    Q->front = 0;
    Q->rear = 0;
    Q->size = N;
    return Q;
}

int IsEmpty(Queue Q) {
    return (Q->front == Q->rear) ? 1 : 0;
}

void AddQ(Queue PtrQ, int item) {
    PtrQ->rear = (PtrQ->rear + 1) % PtrQ->size;
    PtrQ->Data[PtrQ->rear] = item; 
}

int DeleteQ(Queue PtrQ) {
    PtrQ->front = (PtrQ->front + 1) % PtrQ->size;
    return PtrQ->Data[PtrQ->front];
}

Graph Create(int N) {
    Vertex V, W;
    Graph G;
    G = (Graph)malloc(sizeof(struct GNode));
    G->A = (int*)malloc((N*(N+1)/2) * sizeof(int));
    G->Nv = N;
    for(V = 0; V < G->Nv; V++) {
        for(W = 0; W <= V; W++)
            G->A[V*(V+1)/2+W] = 0; // no edge
    }
    return G;
}

void InsertEdge(Graph G, Vertex V, Vertex W) {
    if(V < W)
        G->A[W*(W+1)/2+V] = 1; // has edge
    else
        G->A[V*(V+1)/2+W] = 1;
}

int HasEdge(Graph G, Vertex V, Vertex W) {
    if(V < W)
        return (G->A[W*(W+1)/2+V] == 1) ? 1 : 0;
    else
        return (G->A[V*(V+1)/2+W] == 1) ? 1 : 0;
}

int BFS(Graph G, Vertex V) {
    Queue Q;
    Vertex W, last = V, tail; // last node of the last level
    int count = 1, level = 0;
    Q = CreateQueue(G->Nv);
    Visited[V] = 1; // true
    AddQ(Q, V);
    while(!IsEmpty(Q)) {
        V = DeleteQ(Q);
        for(W = 0; W < G->Nv; W++)
            if(!Visited[W] && HasEdge(G, V, W)) {
                Visited[W] = 1;
                AddQ(Q, W);
                count++;
                tail = W; // tail of the current level
            }
        if(V == last) {
            level++;
            last = tail;
        }
        if(level == 6)
            break;
    }
    free(Q);
    return count;
}

void SDS(Graph G) {
    int i, j, count;
    float percent;
    for(i = 0; i < G->Nv; i++) {
        for(j = 0; j < G->Nv; j++)
            Visited[j] = 0;
        count = BFS(G, i);
        percent = (float)count / (G->Nv) * 100.0;
        printf("%d: %.2f%%\n", i+1, percent);
    }
}

int main() {
    int Nv, Ne, i;
    Vertex V, W;
    Graph G;
    scanf("%d %d", &Nv, &Ne);
    Visited = malloc(Nv * sizeof(int));
    for(i = 0; i < Nv; i++)
        Visited[i] = 0;
    G = Create(Nv);
    for(i = 0; i < Ne; i++) {
        scanf("%d %d", &V, &W);
        InsertEdge(G, V-1, W-1);
    }
    SDS(G);
    free(G);
    free(Visited);
    return 0;
}
