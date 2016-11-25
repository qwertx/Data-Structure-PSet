#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct VNode {
    int x;
    int y;
    int visited;
    int id;
};
typedef struct VNode *Vertex;

struct GNode {
    int Nv;
    Vertex A;
};
typedef struct GNode *Graph;

struct QNode {
    int *Data;
    int rear;
    int front;
    int size;
};
typedef struct QNode *Queue;

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

int FirstJump(Vertex V, int D) {
    float L;
    int re;
    re = V->x * V->x + V->y * V->y;
    L = sqrt(re) - 7.5;
    if(L <= D)
        return re;
    else
        return 0;
}

int Jump(Vertex V, Vertex W, int D) {
    float L;
    int DeltaX, DeltaY;
    DeltaX = V->x - W->x;
    DeltaY = V->y - W->y;
    L = sqrt(DeltaX * DeltaX + DeltaY * DeltaY);
    if(L <= D)
        return 1;
    else
        return 0;
}

int IsSafe(Vertex V, int D) {
    int x, y;
    x = V->x;
    y = V->y;
    if((x + D >= 50) || (x - D <= -50) || (y + D >= 50) || (y - D <= -50))
        return 1;
    else
        return 0;
}

void Unweighted(Graph G, int dist[], int path[], int first[], int D) {
    Queue Q;
    Vertex tmp;
    int V;
    int isfirst = 1, i, canfirst;
    Q = CreateQueue(G->Nv);
    do {
        if(isfirst) {
            for(i = 0; i < G->Nv; i++) {
                tmp = &(G->A[i]);
                canfirst = FirstJump(tmp, D);
                if(!(tmp->visited) && canfirst) { // if not visited and can jump over
                    first[i] = canfirst;
                    dist[i] = 1;
                    path[i] = -666; // some random number
                    tmp->visited = 1;
                    AddQ(Q, i);
                }
            }
            isfirst = 0;
        }
        else {
            V = DeleteQ(Q);
            for(i = 0; i < G->Nv; i++) {
                tmp = &(G->A[i]);
                if(!(tmp->visited) && Jump(&(G->A[V]), tmp, D)) { // if not visited and can jump over
                    dist[i] = dist[V] + 1;
                    path[i] = V;
                    tmp->visited = 1;
                    AddQ(Q, i);
                }
            }
        }
    } while(!IsEmpty(Q)); 
}

int TraceBack(int i, int path[], int first[]) {
    while(path[i] != -666) {
        i = path[i];
    }
    return first[i];
}

int ScanForMin(int dist[], int first[], int path[], Graph G, int D) {
    int MinFirstLength, FirstLength, i, Min = G->Nv; // some big number
    for(i = 0; i < G->Nv; i++) {
        if(dist[i] != -1 && dist[i] < dist[Min] && IsSafe(&(G->A[i]), D))
            Min = i;
    }
    if(Min == G->Nv) // no way out
        return -1;
    MinFirstLength = TraceBack(Min, path, first);
    for(i = 0; i < G->Nv; i++) {
        if(dist[i] == dist[Min] && IsSafe(&(G->A[i]), D)) {
            FirstLength = TraceBack(i, path, first);
            if(FirstLength < MinFirstLength) {
                MinFirstLength = FirstLength;
                Min = i;
            }
        }
    }
    return Min;
}

void Print(Graph G, int i, int S, int path[], int dist[]) {
    int Output[S];
    int j = 0, k = i;
    while(k != -666) {
        Output[j] = k;
        k = path[k];
        j++;
    }
    printf("%d\n", dist[i] + 1);
    for(j = S - 1; j >= 0; j--) {
        k = Output[j];
        printf("%d %d\n", G->A[k].x, G->A[k].y);
    }
}

void Save007(Graph G, int N, int D) {
    Vertex V;
    int i, Min, step;
    int dist[N+1], path[N], first[N]; // distance of first jump (if can)
    for(i = 0; i < N; i++) {
        dist[i] = -1;
        path[i] = -1;
        first[i] = -1;
    }
    dist[N] = 1000;
    Unweighted(G, dist, path, first, D);
    // scan for min
    Min = ScanForMin(dist, first, path, G, D);
    if(Min == -1) {
        printf("0\n");
        return;
    }
    step = dist[Min];
    Print(G, Min, step, path, dist);
}

int main() {
    int N, D, i, x, y;
    Graph G;
    Vertex V;
    scanf("%d %d", &N, &D);
    G = (Graph)malloc(sizeof(struct GNode));
    G->A = (Vertex)malloc(N * sizeof(struct VNode));
    G->Nv = N;
    for(i = 0; i < N; i++) {
        V = &(G->A[i]);
        scanf("%d %d", &x, &y);
        V->x = x;
        V->y = y;
        V->visited = 0;
        V->id = i;
    }
    if(D > 42.5) {
        printf("1\n");
        return 0;
    }
    Save007(G, N, D);
    free(G);
    return 0;
}
