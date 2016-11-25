#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct AVLNode *Position;
typedef Position AVLTree;
typedef struct AVLNode {
    ElementType Data;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

int GetHeight(AVLTree A) {
    if(!A)
        return 0;
    else
        return A->Height;
}

int Max(int a, int b) {
    return a > b ? a : b;
}

AVLTree SingleLeftRotation(AVLTree A) {
    // LL Rotation
    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A;
    // update height
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Left), A->Height) + 1;
    return B;
}

AVLTree SingleRightRotation(AVLTree A) {
    // RR Rotation
    AVLTree B = A->Right;
    A->Right = B->Left;
    B->Left = A;
    // update height
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(A->Height, GetHeight(B->Right)) + 1;
    return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A) {
    // LR Rotation
    // step 1: RR Rotation for B and C
    A->Left = SingleRightRotation(A->Left);
    // step 2: LL Rotation for A and C
    return SingleLeftRotation(A);
}

AVLTree DoubleRightLeftRotation(AVLTree A) {
    // RL Rotation
    // step 1: LL Rotation for B and C
    A->Right = SingleLeftRotation(A->Right);
    // step 2: RR Rotation for A and C
    return SingleRightRotation(A);
}

AVLTree Insert(AVLTree T, ElementType X) {
    if(!T) { // empty tree
        T = (AVLTree)malloc(sizeof(struct AVLNode)); // build a new tree
        T->Data = X;
        T->Height = 0;
        T->Left = NULL;
        T->Right = NULL;
    }
    else if(X < T->Data) { // insert to the left tree
        T->Left = Insert(T->Left, X);
        // if need left rotation
        if(GetHeight(T->Left) - GetHeight(T->Right) == 2) {
            if(X < T->Left->Data)
                T = SingleLeftRotation(T);
            else
                T = DoubleLeftRightRotation(T);
        }
    }
    else if(X > T->Data) { // insert to the right tree
        T->Right = Insert(T->Right, X);
        // if need right rotation
        if(GetHeight(T->Left) - GetHeight(T->Right) == -2) {
            if(X > T->Right->Data)
                T = SingleRightRotation(T);
            else
                T = DoubleRightLeftRotation(T);
        }
    }
    // else X == T->Data, no need to insert
    T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
    return T;
}

int main() {
    int n, e, i;
    AVLTree T;
    scanf("%d", &n);
    for(i = 0; i < n; i++) {
        scanf("%d", &e);
        T = Insert(T, e);    
    }
    printf("%d", T->Data);
    return 0;   
}
