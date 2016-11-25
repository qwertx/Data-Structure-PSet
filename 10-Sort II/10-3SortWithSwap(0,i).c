#include <stdio.h>

void Sort(int A[], int T[], int Used[], int i, int *cnt) {
    int index = i, startOfCycle = index, hasZero = 0;
    // one cycle
    while(T[index] != startOfCycle) {
    	if(A[index] == 0 && hasZero == 0)
    		hasZero = 1;
    	if(hasZero == 1) {
    		(*cnt) = (*cnt) - 2;
    		hasZero = 2;
    	}
        Used[index] = 1;
        (*cnt)++;
        index = T[index];
    }
    // last element in one cycle
    if(A[index] == 0 && hasZero == 0)
		hasZero = 1;
	if(hasZero == 1) {
		(*cnt) = (*cnt) - 2;
		hasZero = 2;
	}
    Used[index] = 1;
    (*cnt) = (*cnt) + 2;
}

int main() {
    int i, N, cnt = 0;
    scanf("%d", &N);
    int A[N], T[N], Used[N];
    for(i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        // A[i] = 99999 - i;
        Used[i] = 0;
        if(A[i] == i) { // no need to sort
            Used[i] = 1;
        }
        T[A[i]] = i;
    }
    for(i = 0; i < N; i++) {
        if(Used[i] == 0)
            Sort(A, T, Used, i, &cnt);
    }
    printf("%d", cnt);
    return 0;
}
