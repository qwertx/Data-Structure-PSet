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

int Visited[10] = {0};

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

void Visit(Vertex V) {
    printf("%d ", V);
}

void DFS(Graph G, Vertex S, void (*Visit)(Vertex)) {
    Vertex W;
    Visit(S);
    Visited[S] = 1;
    for(W = 0; W < G->Nv; W++) {
        if(!Visited[W] && HasEdge(G, S, W))
            DFS(G, W, Visit);
    }
}

void BFS(Graph G, Vertex S, void (*Visit)(Vertex)) {
    Queue Q;
    Vertex V, W;
    Q = CreateQueue(G->Nv);
    Visit(S);
    Visited[S] = 1; // true
    AddQ(Q, S);
    while(!IsEmpty(Q)) {
        V = DeleteQ(Q);
        for(W = 0; W < G->Nv; W++) {
            if(!Visited[W] && HasEdge(G, V, W)) {
                Visit(W);
                Visited[W] = 1;
                AddQ(Q, W);
            }
        }
    }
}

void ListComponents(Graph G) {
    Vertex V;
    int i;
    for(V = 0; V < G->Nv; V++) {
        if(!Visited[V]) {
            printf("{ ");
            DFS(G, V, Visit);
            printf("}\n");
        }
    }
    for(i = 0; i < 10; i++)
        Visited[i] = 0;
    for(V = 0; V < G->Nv; V++) {
        if(!Visited[V]) {
            printf("{ ");
            BFS(G, V, Visit);
            printf("}\n");
        }  
    }
}

int main() {
    int Nv, Ne, i;
    Vertex V, W;
    Graph G;
    scanf("%d %d", &Nv, &Ne);
    G = Create(Nv);
    for(i = 0; i < Ne; i++) {
        scanf("%d %d", &V, &W);
        InsertEdge(G, V, W);
    }
    ListComponents(G);
    return 0;
}
