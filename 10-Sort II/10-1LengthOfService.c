#include <stdio.h>

int main() {
    int i, count, year, N;
    scanf("%d", &N);
    int A[51] = {0};
    // input
    for(i = 0; i < N; i++) {
        scanf("%d", &year);
        A[year]++;
    }
    // output
    for(i = 0; i < 51; i++) {
        if(A[i] != 0) {
            printf("%d:%d\n", i, A[i]);
            count += A[i];
        }
        if(count == N)
            break;
    }
    return 0;
}