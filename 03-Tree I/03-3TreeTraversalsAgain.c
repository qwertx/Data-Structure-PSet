#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// pre[] is the sequence of preorder traversal so do the in[] and post[]
// preL, intL and postL is the first element in the pre[], in[] and post[] of current tree
int *pre, *in, *post;

void Solve(int preL, int inL, int postL, int n) {
    int root, i, L, R;
    if(n == 0)
        return; // no left or right tree
    if(n == 1) {
        post[postL] = pre[preL];
        return;
    }
    root = pre[preL];
    post[postL+n-1] = root;
    for(i = 0; i < n; i++) { // find the correspond position in inL[]
        if(in[inL+i] == root)
            break;
    }
    L = i; // numbers of elements in the left tree
    R = n - L - 1; // numbers of elements in the right tree
    Solve(preL + 1, inL, postL, L); // the left tree
    Solve(preL + L + 1, inL + L + 1, postL + L, R); // the right tree
}

int main() {
    char s[5]; 
    int N, n, i;
    int pushT = 0, currentPop = 0, popT = 0; // numbers of push and current pop position
    scanf("%d", &N);
    pre = (int*)malloc(N * sizeof(int));
    in = (int*)malloc(N * sizeof(int));
    post = (int*)malloc(N * sizeof(int));
    int isPopped[N]; // 1 stands for the number is popped from stack
    for(i = 0; i < N * 2; i++) {
        scanf("%s", s);
        if(strcmp(s, "Push") == 0) {
            scanf("%d", &n);
            pre[pushT] = n; // simulate push
            pushT++;
            while(currentPop != pushT)
                currentPop++;
        }
        else {
            in[popT] = pre[currentPop-1]; // simulate pop
            isPopped[currentPop-1] = 1;
            while((currentPop > 0) && (isPopped[currentPop-1] == 1))
                currentPop--;
            popT++;
        }    
    }
    Solve(0, 0, 0, N);
    for(i = 0; i < N; i++) {
        if(i == 0)
            printf("%d", post[i]);
        else
            printf(" %d", post[i]);
    }
    return 0;
}
