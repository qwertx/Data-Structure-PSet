#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 1000
#define INFINITY 65535
typedef int Vertex;
typedef int WeightType;

// definition of edge
typedef struct ENode *PtrToENode;
struct ENode {
    Vertex V1, V2;
    WeightType Weight;
};
typedef PtrToENode Edge;

// definition of graph node
typedef struct GNode *PtrToGNode;
struct GNode {
    int Nv;
    int Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph CreateGraph(int VertexNum) {
    Vertex V, W;
    MGraph Graph;
    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for(V = 0; V < Graph->Nv; V++) {
        for(W = 0; W < Graph->Nv; W++)
            Graph->G[V][W] = INFINITY;
    }
    return Graph;
}

void InsertEdge(MGraph Graph, Edge E) {
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->G[E->V2][E->V1] = E->Weight;
}

Vertex FindMinDist(MGraph Graph, WeightType dist[]) {
    Vertex MinV, V;
    WeightType MinDist = INFINITY;
    for(V = 0; V < Graph->Nv; V++) {
        if(dist[V] != 0 && dist[V] < MinDist) {
            MinDist = dist[V];
            MinV = V;
        }
    }
    if(MinDist < INFINITY) // MinDist found
        return MinV;
    else
        return -1;
}

int Prim(MGraph Graph) {
    WeightType dist[MaxVertexNum], TotalWeight;
    Vertex V, W;
    int VCount;
    // initialization
    // the default start point is 0
    for(V = 0; V < Graph->Nv; V++) {
        dist[V] = Graph->G[0][V];
    }
    TotalWeight = 0;
    VCount = 0;
    dist[0] = 0;
    VCount++;
    while(1) {
        V = FindMinDist(Graph, dist);
        if(V == -1)
            break;
        TotalWeight += dist[V];
        dist[V] = 0;
        VCount++;
        // update MST
        for(W = 0; W < Graph->Nv; W++) {
            if(dist[W] != 0 && Graph->G[V][W] < INFINITY) {
                if(Graph->G[V][W] < dist[W]) { // collect V makes dist[W] smaller
                    dist[W] = Graph->G[V][W];
                }
            }
        }
    }
    if(VCount < Graph->Nv)
        TotalWeight = -1;
    return TotalWeight;
}

int main() {
    int MinCost;
    MGraph G;
    Edge E;
    int N, M, i;
    scanf("%d %d", &N, &M);
    G = CreateGraph(N);
    for(i = 0; i < M; i++) {
        E = (Edge)malloc(sizeof(struct ENode));
        scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
        E->V1--;
        E->V2--;
        InsertEdge(G, E);
    }
    MinCost = Prim(G);
    printf("%d", MinCost);
    free(G);
    return 0;
}
