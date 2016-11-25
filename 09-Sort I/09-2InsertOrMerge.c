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

void Merge(ElementType A[], ElementType temp[], int L, int R, int REnd) {
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
        Merge(A, temp, i, i + length, i + 2 * length - 1); // merge a pair of subsequences
    if(i + length < N) //there are two subsequences left
        Merge(A, temp, i, i + length, N - 1);
    else { // only one subsequence left
        for(j = i; j < N; j++)
            temp[j] = A[j];
    }
}

void MergeSortIteration(ElementType A[], ElementType B[], int N) {
    int length = 1, flag, i; // the initial length of subsequences
    ElementType *temp;
    temp = malloc(N * sizeof(ElementType));
    if(temp != NULL) {
        while(length < N) {
            // from A to temp
            Merge_Pass(A, temp, N, length); 
            length *= 2;
            flag = Check(temp, B, N);
            if(flag == 1) {
                Merge_Pass(temp, A, N, length);
                free(temp);
                return;
            }
            // from temp to A
            Merge_Pass(temp, A, N, length);
            length *= 2;
            flag = Check(A, B, N);
            if(flag == 1) {
                Merge_Pass(A, temp, N, length);
                for(i = 0; i < N; i++)
                    A[i] = temp[i];
                free(temp);
                return;
            }
        }
    }
    else
        printf("Out of Memory.\n");
}

int main() {
    int N, i, flag;
    int *Ai, *Am, *B;
    scanf("%d", &N);
    Ai = malloc(N * sizeof(int)); // initial sequence for InsertionSort
    Am = malloc(N * sizeof(int)); // initial sequence for MergeSort
    B = malloc(N * sizeof(int));
    for(i = 0; i < N; i++)
        scanf("%d", &Ai[i]);
    for(i = 0; i < N; i++)
        Am[i] = Ai[i];
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
        MergeSortIteration(Am, B, N);
        printf("Merge Sort\n");
        printf("%d", Am[0]);
        for(i = 1; i < N; i++)
            printf(" %d", Am[i]);
    }
    free(Ai);
    free(Am);
    free(B);
    return 0;
}
