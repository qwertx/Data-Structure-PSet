#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct VNode {
    int x;
    int y;
    int visited;
};
typedef struct VNode *Vertex;

struct GNode {
    int Nv;
    Vertex A;
};
typedef struct GNode *Graph;

int FirstJump(Vertex V, int D) {
    float L;
    L = sqrt(V->x * V->x + V->y * V->y) - 7.5;
    if(L <= D)
        return 1;
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

int DFS(Vertex V, Graph G, int D) {
    int answer = 0, i;
    Vertex W;
    V->visited = 1;
    if(IsSafe(V, D))
        answer = 1;
    else {
        for(i = 0; i < G->Nv; i++) {
            W = &(G->A[i]);
            if(!(W->visited) && Jump(V, W, D)) {
                answer = DFS(W, G, D);
                if(answer == 1)
                    break;
            }
        }
    }
    return answer;
}

void Save007(Graph G, int D) {
    Vertex V;
    int i, answer = 0;
    for(i = 0; i < G->Nv; i++) {
        V = &(G->A[i]);
        if(!(V->visited) && FirstJump(V, D)) {
            answer = DFS(V, G, D);
            if(answer == 1)
                break;
        }
    }
    if(answer == 1)
        printf("Yes");
    else
        printf("No");
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
    }
    Save007(G, D);
    free(G);
    return 0;
}
