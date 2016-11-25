#include <stdio.h>
#include <stdlib.h>

typedef long ElementType;

// standard interface:
// void X_Sort(ElementType A[], int N);

// bubble sort
void swap(ElementType *a, ElementType *b) {
    ElementType temp = *a;
    *a = *b;
    *b = temp;
}

void BubbleSort(ElementType A[], int N) {
    int i, P, flag;
    for(P = N - 1; P > 0; P--) {
        flag = 0; // if swapped this time
        for(i = 0; i < P; i++) {
            if(A[i] > A[i+1]) {
                swap(&A[i], &A[i+1]);
                flag = 1;
            }
        }
        if(flag == 0) break;
    }
}

// insertion sort
void InsertionSort(ElementType A[], int N) {
    int i, P;
    ElementType temp;
    for(P = 1; P < N; P++) {
        temp = A[P];
        for(i = P; i>0 && A[i-1]>temp; i--)
            A[i] = A[i-1]; // move forward
        A[i] = temp; // insert
    }
}

// shell sort
void ShellSortOriginal(ElementType A[], int N) {
    int P, D, i;
    ElementType temp;
    for(D = N / 2; D > 0; D /= 2) {
        for(P = D; P < N; P++) { // insertion sort
            temp = A[P];
            for(i = P; i>=D && A[i-D]>temp; i -= D)
                A[i] = A[i-D];
            A[i] = temp;
        }
    }
}

// shell sort with Sedgewick sequence
void ShellSortImproved(ElementType A[], int N) {
    int Si, D, P, i;
    ElementType temp;
    int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};
    for(Si = 0; Sedgewick[Si] > N; Si++) // determine the largest number in the sequence
        ;
    for(D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si]) {
        for(P = D; P < N; P++) {
            temp = A[P];
            for(i = P; i>=D && A[i-D]>temp; i -= D)
                A[i] = A[i-D];
            A[i] = temp;
        }
    }
}

// selection sort
int ScanForMin(ElementType A[], int L, int R) {
    int i;
    int minPos = L;
    for(i = L + 1; i <= R; i++) {
        if(A[i] < A[minPos])
            minPos = i;
    }
    return minPos;
}

void SelectionSort(ElementType A[], int N) {
    int MinPosition, i;
    for(i = 0; i < N; i++) {
        MinPosition = ScanForMin(A, i, N-1);
        swap(&A[i], &A[MinPosition]);
    }
}

// heap sort using a MinHeap
void PercDown(ElementType A[], int P, int N) { // the index of current root is P and adjust it to a MinHeap
    int parent, child;
    ElementType X;
    X = A[P]; // the current root
    for(parent = P; (parent * 2 + 1) < N; parent = child) { // if Parent * 2 > N-1 , so the current parent has no son
        child = parent * 2 + 1; // left son
        if((child != N - 1) && (A[child] > A[child+1])) // the node is not last and larger than right son
            child++; // child is the smaller element of parents' two sons (right son)
        if(X <= A[child])
            break; // the right position found
        else
            A[parent] = A[child]; // larger son become parent
    }
    A[parent] = X; // place X in the right position
}

ElementType DeleteMin(ElementType A[], int N) {
    int parent, child;
    ElementType Min, temp;
    Min = A[0]; // get the root
    temp = A[N-1];
    N--;
    for(parent = 0; (parent * 2 + 1) < N; parent = child) {
        child = parent * 2 + 1; // left son
        if((child != N - 1) && (A[child] > A[child+1]))
            child++;
        if(temp <= A[child])
            break;
        else
            A[parent] = A[child];
    }
    A[parent] = temp;
    return Min;
}

void HeapSortMin(ElementType A[], int N) {
    int i;
    ElementType temp[N];
    for(i = N / 2; i >= 0; i--) // build heap
        PercDown(A, i, N);
    for(i = 0; i < N; i++)
        temp[i] = DeleteMin(A, N-i); // get the min element
    for(i = 0; i < N; i++)
        A[i] = temp[i];
}

// standard heap sort using a MaxHeap
void PercDown1(ElementType A[], int P, int N) { // the index of current root is P and adjust it to a MaxHeap
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

void HeapSort(ElementType A[], int N) {
    int i;
    // build the heap from down to up
    for(i = N / 2; i >= 0; i--) // start from the parent of the last node (last node which has a son node)
        PercDown1(A, i, N); // i is the root index
    for(i = N - 1; i > 0; i--) {
        swap(&A[0], &A[i]); // replace the root with last node (current largest number is in the right position)
        PercDown1(A, 0, i); // adjust the remaining numbers to a MaxHeap
    }
}

// merge sort using recursion
void Merge(ElementType A[], ElementType temp[], int L, int R, int REnd) {
    // L and R is the start position of left and right part
    int LEnd, NumOfElements, Pos, i; // current position of the sorted sequence
    LEnd = R - 1;
    Pos = L;
    NumOfElements = REnd - L + 1; // length of current sequence
    while(L <= LEnd && R <= REnd) {
        if(A[L] <= A[R])
            temp[Pos++] = A[L++];
        else
            temp[Pos++] = A[R++];
    }
    while(L <= LEnd)
        temp[Pos++] = A[L++];
    while(R <= REnd)
        temp[Pos++] = A[R++];
    for(i = 0; i < NumOfElements; i++, REnd--) // move elements back to A
        A[REnd] = temp[REnd];
}

void MSort(ElementType A[], ElementType temp[], int L, int REnd) {
    int center;
    if(L < REnd) { // the sequence is not empty
        center = (L + REnd) / 2;
        MSort(A, temp, L, center); // sort the left half
        MSort(A, temp, center + 1, REnd); // sort the right half
        Merge(A, temp, L, center + 1, REnd); // merge
    }
}

void MergeSortRecursion(ElementType A[], int N) {
    ElementType *temp;
    temp = malloc(N * sizeof(ElementType));
    if(temp != NULL) {
        MSort(A, temp, 0, N - 1);
        free(temp);
    }
    else
        printf("Out of Memory.\n");
}

// merge sort using iteration
void Merge1(ElementType A[], ElementType temp[], int L, int R, int REnd) {
    // the same as Merge() but without the last step
    int LEnd, Pos, i;
    LEnd = R - 1;
    Pos = L;
    while(L <= LEnd && R <= REnd) {
        if(A[L] <= A[R])
            temp[Pos++] = A[L++];
        else
            temp[Pos++] = A[R++];
    }
    while(L <= LEnd)
        temp[Pos++] = A[L++];
    while(R <= REnd)
        temp[Pos++] = A[R++];
}

void Merge_Pass(ElementType A[], ElementType temp[], int N, int length) { // the merge in one time, length is the size of subsequence 
    int i, j;
    for(i = 0; i < N - 2 * length; i += 2 * length)
        Merge1(A, temp, i, i + length, i + 2 * length - 1); // merge a pair of subsequences
    if(i + length < N) //there are two subsequences left
        Merge1(A, temp, i, i + length, N - 1);
    else { // only one subsequence left
        for(j = i; j < N; j++)
            temp[j] = A[j];
    }
}

void MergeSortIteration(ElementType A[], int N) {
    int length = 1; // the initial length of subsequences
    ElementType *temp;
    temp = malloc(N * sizeof(ElementType));
    if(temp != NULL) {
        while(length < N) {
            // from A to temp
            Merge_Pass(A, temp, N, length); 
            length *= 2;
            // from temp to A, so we can ensure that A gets the right sequence at last
            Merge_Pass(temp, A, N, length);
            length *= 2;
        }
        free(temp);
    }
    else
        printf("Out of Memory.\n");
}

// helper function for qsort() in C library
int compare(const void *a, const void *b) {
    return *(long*)a - *(long*)b;
}

int main() {
    int N, i;
    long *A;
    // input
    scanf("%d", &N);
    A = malloc(N * sizeof(long));
    for(i = 0; i < N; i++)
        scanf("%ld", &A[i]);
    // sort test
//    BubbleSort(A, N);
//    InsertionSort(A, N);
//    ShellSortOriginal(A, N);
//    ShellSortImproved(A, N);
    SelectionSort(A, N);
//    HeapSortMin(A, N);
//    HeapSort(A, N);
//    MergeSortRecursion(A, N);
//    MergeSortIteration(A, N);
//    qsort(A, N, sizeof(long), compare); // a quick sort in C library
    // output
    printf("%ld", A[0]);
    for(i = 1; i < N; i++) {
        printf(" %ld", A[i]);
    }
    return 0;
}
