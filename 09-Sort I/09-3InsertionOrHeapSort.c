#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

int Check(ElementType A[], ElementType B[], int N) {
    int i, flag = 1;
    for(i = 0; i < N; i++) { // check after each insertion
        if(A[i] != B[i]) {
            flag = 0;
            break;
        }
    }
    return flag;
}

int InsertionSort(ElementType A[], ElementType B[], int N) {
    int i, P, flag; // 0 for unequal with B, 1 for initial state and equal, 2 for one more insertion loop
    ElementType temp;
    for(P = 1; P < N; P++) {
        if(flag != 2)
            flag = 1;
        temp = A[P];
        for(i = P; i>0 && A[i-1]>temp; i--)
            A[i] = A[i-1];
        A[i] = temp;
        if(flag != 2) {
            flag = Check(A, B, N);
        }
        if(flag == 2) // has done insertion one more time
            return flag;
        if(flag == 1) // the same with the given sequence
            flag++; 
    }
    if(flag == 0)
        return flag;
}

void swap(ElementType *a, ElementType *b) {
    ElementType temp = *a;
    *a = *b;
    *b = temp;
}

void PercDown(ElementType A[], int P, int N) { // the index of current root is P and adjust it to a MaxHeap
    int parent, child;
    ElementType X;
    X = A[P]; // the current root
    for(parent = P; (parent * 2 + 1) < N; parent = child) { // if Parent * 2 > N-1 , so the current parent has no son
        child = parent * 2 + 1; // left son
        if((child != N - 1) && (A[child] < A[child+1])) // the node is not last and smaller than right son
            child++; // child is the larger element of parents' two sons (right son)
        if(X >= A[child])
            break; // the right position found
        else
            A[parent] = A[child]; // larger son become parent
    }
    A[parent] = X; // place X in the right position
}

void HeapSort(ElementType A[], ElementType B[], int N) {
    int i, flag;
    // build the heap from down to up
    for(i = N / 2; i >= 0; i--) // start from the parent of the last node (last node which has a son node)
        PercDown(A, i, N); // i is the root index
    for(i = N - 1; i > 0; i--) {
        swap(&A[0], &A[i]); // replace the root with last node (current largest number is in the right position)
        PercDown(A, 0, i); // adjust the remaining numbers to a MaxHeap
        flag = Check(A, B, N);
        if(flag == 1) {
            i--;
            swap(&A[0], &A[i]);
            PercDown(A, 0, i);
            return;
        }
    }
}

int main() {
    int N, i, flag;
    int *Ai, *Ah, *B;
    scanf("%d", &N);
    Ai = malloc(N * sizeof(int)); // initial sequence for InsertionSort
    Ah = malloc(N * sizeof(int)); // initial sequence for HeapSort
    B = malloc(N * sizeof(int));
    for(i = 0; i < N; i++)
        scanf("%d", &Ai[i]);
    for(i = 0; i < N; i++)
        Ah[i] = Ai[i];
    for(i = 0; i < N; i++)
        scanf("%d", &B[i]);
    flag = InsertionSort(Ai, B, N);
    if(flag == 2) {
        printf("Insertion Sort\n");
        printf("%d", Ai[0]);
        for(i = 1; i < N; i++)
            printf(" %d", Ai[i]);
    }
    else {
        HeapSort(Ah, B, N);
        printf("Heap Sort\n");
        printf("%d", Ah[0]);
        for(i = 1; i < N; i++)
            printf(" %d", Ah[i]);
    }
    free(Ai);
    free(Ah);
    free(B);
    return 0;
}