#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
#define MaxVertexNum 500
#define INFINITY 65535
typedef int Vertex; // use array index for Vertex

// definition of edge
typedef struct ENode *PtrToENode;
struct ENode {
    Vertex V1, V2;
    int length;
    int cost;
};
typedef PtrToENode Edge;

// definition of graph node
typedef struct GNode *PtrToGNode;
struct GNode {
    int Nv;
    int Ne;
    int G[MaxVertexNum][MaxVertexNum]; // G[i][j] is length and G[j][i] is cost (i < j)
};
typedef PtrToGNode MGraph;

// initialization a graph with no edge
MGraph CreateGraph(int VertexNum) {
    Vertex V, W;
    MGraph Graph;
    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    // Vertex number starts from 0 to (Graph->Nv - 1)
    for(V = 0; V < Graph->Nv; V++) {
        for(W = 0; W < Graph->Nv; W++) {
            Graph->G[V][W] = INFINITY;
        }
    }
    return Graph;
}

void InsertEdge(MGraph Graph, Edge E) {
    // insert length between 2 cities
    Graph->G[E->V1][E->V2] = E->length;
    // insert cost between 2 cities
    Graph->G[E->V2][E->V1] = E->cost;
}

Vertex FindMinDist(MGraph Graph, int dist[], int collected[]) {
    // return the vertex with the smallest dist of uncollected vertex
    Vertex MinV, V;
    int MinDist = INFINITY;
    for(V = 0; V < Graph->Nv; V++) {
        if(collected[V] == false && dist[V] < MinDist) {
            MinDist = dist[V];
            MinV = V;
        }
    }
    if(MinDist < INFINITY)
        return MinV;
    else
        return -1;
}

void Dijkstra(MGraph Graph, int dist[], int cost[], Vertex S) {
    int collected[Graph->Nv];
    int tmpL, tmpC;
    Vertex V, W;
    // initialization
    // G[i][j] = INFINITY if edge<i, j> does not exist
    for(V = 0; V < Graph->Nv; V++) {
        if(V < S) {
            dist[V] = Graph->G[V][S];
            cost[V] = Graph->G[S][V];
        }      
        else if(V > S) {
            dist[V] = Graph->G[S][V];
            cost[V] = Graph->G[V][S];
        }
        collected[V] = false;
    }
    // collect start vertex
    dist[S] = 0;
    cost[S] = 0;
    collected[S] = true;
    while(1) {
        // find min of uncollected
        V = FindMinDist(Graph, dist, collected);
        if(V == -1)
            break;
        collected[V] = true;
        for(W = 0; W < Graph->Nv; W++) {
            if(collected[W] == false && Graph->G[V][W] < INFINITY) { // if not collected and has edge
                // check length and cost between V and W
                if(V < W) {
                    tmpL = Graph->G[V][W];
                    tmpC = Graph->G[W][V];
                }
                else {
                    tmpL = Graph->G[W][V];
                    tmpC = Graph->G[V][W];
                }
                if(dist[V] + tmpL < dist[W]) { // if adding V makes dist[W] smaller
                    dist[W] = dist[V] + tmpL;
                    cost[W] = cost[V] + tmpC;
                }
                else if((dist[V] + tmpL == dist[W]) && (cost[V] + tmpC < cost[W])) {
                    cost[W] = cost[V] + tmpC;
                }
            }
        }
    }
}

int main() {
    int N, M, S, D, i;
    int c1, c2, length, charge;
    MGraph G;
    Edge E;
    // num of cities, num of highways, start and destination point
    scanf("%d %d %d %d", &N, &M, &S, &D);
    int dist[N], cost[N];
    G = CreateGraph(N);
    G->Ne = M;
    for(i = 0; i < M; i++) {
        E = (Edge)malloc(sizeof(struct ENode));
        scanf("%d %d %d %d", &c1, &c2, &length, &charge);
        // make sure the length is in the lower triangle in the matrix
        if(c1 < c2) {
            E->V1 = c1;
            E->V2 = c2;
        }
        else {
            E->V1 = c2;
            E->V2 = c1;
        }
        E->length = length;
        E->cost = charge;
        InsertEdge(G, E);
    }
    Dijkstra(G, dist, cost, S);
    printf("%d %d", dist[D], cost[D]);
    return 0;
}
