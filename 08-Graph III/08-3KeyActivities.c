#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100
typedef int Vertex;
typedef int WeightType;

// definition of an edge
typedef struct ENode *PtrToENode;
struct ENode { 
    Vertex V1, V2;
    WeightType Weight;
};
typedef PtrToENode Edge;

// definition of adjacent vertex
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
    Vertex AdjV;
    WeightType Weight;
    PtrToAdjVNode Next;
};

// definition of list heads
typedef struct Vnode {
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

// definition of graph
typedef struct GNode *PtrToGNode;
struct GNode {
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

// Queue
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

// Graph
LGraph CreateGraph(int VertexNum) {
    Vertex V;
    LGraph Graph;
    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for(V = 0; V < Graph->Nv; V++)
        Graph->G[V].FirstEdge = NULL;
    return Graph;
}

void InsertEdge(LGraph Graph, Edge E) {
    PtrToAdjVNode NewNode;
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
    // insert v2 to the head of v1
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;
    // insert <v2, v1> for later convinence
    // note the Weight is negative here
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    if(E->Weight != 0)
        NewNode->Weight = E->Weight * -1;
    else    
        NewNode->Weight = -66666; // some random number
    // insert v1 to the head of v2
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}

int TopSort(LGraph Graph, Vertex Earliest[]) {
    int Indegree[MaxVertexNum], cnt;
    Vertex V;
    PtrToAdjVNode W;
    Queue Q = CreateQueue(Graph->Nv);
    // initialize Indegree[]
    for(V = 0; V < Graph->Nv; V++)
        Indegree[V] = 0;
    // get Indegree
    for(V = 0; V < Graph->Nv; V++)
        for(W = Graph->G[V].FirstEdge; W; W = W->Next)
            if(W->Weight >= 0) 
                Indegree[W->AdjV]++;
    // enqueue
    for(V = 0; V < Graph->Nv; V++)
        if(Indegree[V] == 0)
            AddQ(Q, V);
    // TopSort
    for(V = 0; V < Graph->Nv; V++)
        Earliest[V] = 0;
    cnt = 0;
    while(!IsEmpty(Q)) {
        V = DeleteQ(Q);
        cnt++;
        for(W = Graph->G[V].FirstEdge; W; W = W->Next) {
            if(W->Weight >= 0) {
                if(Earliest[W->AdjV] < Earliest[V] + W->Weight)
                    Earliest[W->AdjV] = Earliest[V] + W->Weight;
                if(--Indegree[W->AdjV] == 0) // if delete V makes Indegree of W->AdjV to 0
                    AddQ(Q, W->AdjV);
            }
        }    
    }
    if(cnt != Graph->Nv)
        return -1; // cycle in Graph
    else
        return 1;
}

void GetLatest(LGraph Graph, int Latest[], int Earliest[], int NEnd[], int EndE) {
    int OutDegree[MaxVertexNum];
    Vertex V, end;
    PtrToAdjVNode W;
    Queue Q = CreateQueue(Graph->Nv);
    // initialize Outdegree[]
    for(V = 0; V < Graph->Nv; V++)
        OutDegree[V] = 0;
    // get Indegree
    for(V = 0; V < Graph->Nv; V++)
        for(W = Graph->G[V].FirstEdge; W; W = W->Next)
            if(W->Weight < 0) 
                OutDegree[W->AdjV]++;
    // initialize Latest[]
    for(V = 0; V < Graph->Nv; V++)
        Latest[V] = EndE;
    // find all ending point
    for(V = 0; V < Graph->Nv; V++) {
        if(NEnd[V] == 0) {
            Latest[V] = EndE;
            AddQ(Q, V);
        }
    }
    while(!IsEmpty(Q)) {
        V = DeleteQ(Q);
        for(W = Graph->G[V].FirstEdge; W; W = W->Next) {
            if(W->Weight < 0) {
                if((W->Weight != -66666) && (Latest[W->AdjV] > Latest[V] + W->Weight))
                    Latest[W->AdjV] = Latest[V] + W->Weight;
                else if((W->Weight == -66666) && (Latest[W->AdjV] > Latest[V]))
                    Latest[W->AdjV] = Latest[V];
                if(--OutDegree[W->AdjV] == 0)
                    AddQ(Q, W->AdjV);
            }
        }
    }
}

void GetKey(LGraph Graph, int Latest[], int Earliest[], int NEnd[], int IsKey[][MaxVertexNum]) {
    Vertex i, j, x, y;
    PtrToAdjVNode W;
    // initialize IsKey[]
    for(i = 0; i < Graph->Nv; i++)
        for(j = 0; j < Graph->Nv; j++)
            IsKey[i][j] = 0;
    for(i = 0; i < Graph->Nv; i++) {
        for(W = Graph->G[i].FirstEdge; W; W = W->Next) {
            if((W->Weight >= 0) && (Latest[W->AdjV] - Earliest[i] - W->Weight == 0))
                IsKey[i][W->AdjV] = 1;
        }
    }
    // output
    for(i = 0; i < Graph->Nv; i++)
        for(j = Graph->Nv - 1; j >= 0; j--)
            if(IsKey[i][j] == 1) {
                x = i + 1;
                y = j + 1;
                printf("%d->%d\n", x, y); 
            }
}

int main() {
    int success, EndE, EndL, flag = 1;
    int NEnd[MaxVertexNum] = {0}; // if an vertex is not an end
    LGraph G;
    Edge E;
    int N, M, i;
    Vertex W;
    Vertex Earliest[MaxVertexNum], Latest[MaxVertexNum], IsKey[MaxVertexNum][MaxVertexNum];
    scanf("%d %d", &N, &M);
    G = CreateGraph(N);
    for(i = 0; i < M; i++) {
        E = (Edge)malloc(sizeof(struct ENode));
        scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
        E->V1--;
        E->V2--;
        NEnd[E->V1] = 1;
        InsertEdge(G, E);
    }
    success = TopSort(G, Earliest);
    // not success
    if(success == -1) {
        printf("0");
        free(G);
        return 0;
    }
    // find the largest ending vertex
    for(i = 0; i < N; i++) {
        if(flag && NEnd[i] == 0) {
            EndE = Earliest[i];
            flag = 0;
        }
        if(NEnd[i] == 0 && EndE < Earliest[i])
            EndE = Earliest[i];
    }
    printf("%d\n", EndE); 
    GetLatest(G, Latest, Earliest, NEnd, EndE);
    GetKey(G, Latest, Earliest, NEnd, IsKey);
    free(G);
    return 0;
}
