#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *in, *out;

int GetLeftLength(int n) { // compute the size of the left tree of a complete binary tree
    int s = 0, h = 0, X, maxBottomLeft;
    int next = 1;
    while(next <= n) {
        s = next;
        h++;
        next = (next + 1) * 2 - 1;
    }
    X = n - s;
    maxBottomLeft = pow(2, h-1);
    s = (s - 1) / 2;
    if(X <= maxBottomLeft) 
        return s + X;
    else
        return s + maxBottomLeft;
}

void Solve(int inLeft, int inRight, int outRoot) {
    int n, L, LeftOutRoot, RightOutRoot;
    n = inRight - inLeft + 1;
    if(n == 0) return;
    L = GetLeftLength(n);
    out[outRoot] = in[inLeft + L]; // find the root
    LeftOutRoot = outRoot * 2 + 1; // left root index
    RightOutRoot = LeftOutRoot + 1; // right root index
    Solve(inLeft, inLeft + L - 1, LeftOutRoot);
    Solve(inLeft + L + 1, inRight, RightOutRoot);
}

int compare(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    int N, n, i;
    scanf("%d", &N);
    in = (int*)malloc(N * sizeof(int));
    out = (int*)malloc(N * sizeof(int));
    for(i = 0; i < N; i++) {
        scanf("%d", &n);
        in[i] = n;
    }
    qsort(in, N, sizeof(int), compare);
    Solve(0, N-1, 0);
    for(i = 0; i < N; i++) {
        if(i == 0)
            printf("%d", out[i]);
        else
            printf(" %d", out[i]);
    }
    return 0;
}
