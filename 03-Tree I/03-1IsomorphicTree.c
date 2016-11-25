#include <stdio.h>

#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1  // not NULL

struct TreeNode {
    ElementType Element;
    Tree Left;
    Tree Right;
} T1[MaxTree], T2[MaxTree];

Tree BuildTree(struct TreeNode T[]) {
    int N, Root, i;
    char cl, cr;
    scanf("%d\n", &N); //number of nodes
    if(N == 0) return Null;
    int check[N];

    if(N) {
        for(i = 0; i < N; i++)
            check[i] = 0; // if used by other nodes
        for(i = 0; i < N; i++) {
            scanf("%c %c %c\n", &T[i].Element, &cl, &cr);
            // index of left son
            if(cl != '-') {
                T[i].Left = cl - '0';
                check[T[i].Left] = 1;
            }
            else T[i].Left = Null;
            // index of right son
            if(cr != '-') {
                T[i].Right = cr - '0';
                check[T[i].Right] = 1;
            }
            else T[i].Right = Null;
        }
        // the root should not be used by any other nodes
        for(i = 0; i < N; i++)
            if(!check[i]) break;
        Root = i;
    }
    return Root;
}

int Isomorphic(Tree R1, Tree R2) {
    if((R1 == Null && R2 == Null)) // both empty
        return 1;
    if((R1 == Null && R2 != Null) || (R1 != Null && R2 == Null)) // one of them is empty
        return 0;
    if(T1[R1].Element != T2[R2].Element) // roots are different
        return 0;
    if(T1[R1].Left == Null && T2[R2].Left == Null) // both have no left subtree
        return Isomorphic(T1[R1].Right, T2[R2].Right); 
    if((T1[R1].Left != Null && T2[R2].Left != Null) && 
        (T1[T1[R1].Left].Element == T2[T2[R2].Left].Element)) {   // no need to swap left and right
        return (Isomorphic(T1[R1].Left, T2[R2].Left) && Isomorphic(T1[R1].Right, T2[R2].Right));
    }
    else
        return (Isomorphic(T1[R1].Left, T2[R2].Right) && Isomorphic(T1[R1].Right, T2[R2].Left));
}

int main() {
    Tree R1, R2;
    R1 = BuildTree(T1);
    R2 = BuildTree(T2);
    if(Isomorphic(R1, R2)) printf("Yes");
    else printf("No");
    return 0;
}
