#include <stdio.h>
#include <stdlib.h>

struct Num{
    int num;
    int mod;
    int indegree;
    int min; // the min index affects its degree
    int id; // the id and max index affects its degree
};
typedef struct Num *PTR;
struct Num Numbers[1000];

// definition of MinHeap
typedef struct HeapStruct *MinHeap;
struct HeapStruct {
    PTR Elements;
    int Size;
};

void Assign(PTR a, PTR b) {
    a->num = b->num;
    a->mod = b->mod;
    a->indegree = b->indegree;
    a->min = b->min;
    a->id = b->id;
}

// MinHeap functions
MinHeap Create(int MaxSize) {
    MinHeap H = malloc(sizeof(struct HeapStruct));
    H->Elements = malloc((MaxSize + 1) * sizeof(struct Num));
    H->Size = 0;
    H->Elements[0].num = -1; // the sentinel
    return H;
}

void Insert(MinHeap H, PTR item) {
    int i;
    i = ++H->Size;
    for( ; H->Elements[i/2].num > item->num; i /= 2)
        Assign(&(H->Elements[i]), &(H->Elements[i/2]));
    Assign(&(H->Elements[i]), item);
}

PTR DeleteMin(MinHeap H) {
    int Parent, Child;
    PTR MinItem, temp;
    MinItem = (PTR)malloc(sizeof(struct Num));
    temp = (PTR)malloc(sizeof(struct Num));
    Assign(MinItem, &(H->Elements[1]));
    Assign(temp, &(H->Elements[H->Size--]));
    for(Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
        Child = Parent * 2;
        if((Child != H->Size) && (H->Elements[Child].num > H->Elements[Child+1].num))
            Child++;  // Child is the smaller element of parents' two sons
        if(temp->num <= H->Elements[Child].num)
            break;
        else
            Assign(&(H->Elements[Parent]), &(H->Elements[Child]));
    }
    Assign(&(H->Elements[Parent]), temp);
    return MinItem;
}

void PercDown(MinHeap H, int p) { // the root is H->Elements[p]
    int Parent, Child;
    PTR X;
    X = (PTR)malloc(sizeof(struct Num));
    Assign(X, &(H->Elements[p]));
    for(Parent = p; Parent * 2 <= H->Size; Parent = Child) {
        Child = Parent * 2;
        if((Child != H->Size) && (H->Elements[Child].num > H->Elements[Child+1].num))
            Child++;
        if(X->num <= H->Elements[Child].num)
            break;
        else
            Assign(&(H->Elements[Parent]), &(H->Elements[Child]));
    }
    Assign(&(H->Elements[Parent]), X);
}

void BuildHeap(MinHeap H) {
    // presume that the elements are all in the H->Elements[]
    int i;
    for(i = H->Size / 2; i > 0; i--) {
        PercDown(H, i); // from the last parent node to the root
    }
}
// end of MinHeap

int CanAffect(PTR a, PTR b, int N) { // if delete b will affect indegree of a
    if(a->id >= a->min) {
        if((b->id) >= (a->min) && (b->id) <= (a->id))
            return 1;
        else
            return 0;
    }
    else {
        if((b->id) >= (a->min) && (b->id) <= N - 1)
            return 1;
        else if((b->id) >= 0 && (b->id) <= (a->id))
            return 1;
        else
            return 0;
    }
}

void Sort(struct Num Numbers[], MinHeap H, int N, int Empty) {
    int i, j;
    PTR Min;
    for(i = 0; i < N - Empty; i++) {
        Min = DeleteMin(H);
        if(i != N - Empty - 1)
            printf("%d ", Min->num);
        else
            printf("%d", Min->num);
        for(j = 0; j < N; j++) {
            if(Numbers[j].indegree != -1 && CanAffect(&Numbers[j], Min, N)) {
                if(Numbers[j].indegree > 0)
                    Numbers[j].indegree--;
            }
            if(Numbers[j].indegree == 0) {
                Insert(H, &Numbers[j]);
                Numbers[j].indegree = -1;
            }
        }
    }
}

int main() {
    int N, i, Empty = 0;
    MinHeap H;
    scanf("%d", &N);
    H = Create(N);
    // input
    for(i = 0; i < N; i++) {
        scanf("%d", &Numbers[i].num);
        // empty cell
        if(Numbers[i].num < 0) {
            Numbers[i].mod = -1;
            Numbers[i].indegree = -1;
            Numbers[i].min = -1;
            Numbers[i].id = -1;
            Empty++;
            continue;
        }
        Numbers[i].mod = Numbers[i].num % N;
        if(i >= Numbers[i].mod)
            Numbers[i].indegree = i - Numbers[i].mod;
        else
            Numbers[i].indegree = N - Numbers[i].mod + i;
        Numbers[i].min = Numbers[i].mod;
        Numbers[i].id = i;
        // if indegree is 0 then add to heap
        if(Numbers[i].indegree == 0) {
            Insert(H, &Numbers[i]);
            Numbers[i].indegree = -1;
        }
    }
    // sort and output
    Sort(Numbers, H, N, Empty);
    return 0;
}
