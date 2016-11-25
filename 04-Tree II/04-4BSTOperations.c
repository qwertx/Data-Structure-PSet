#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

void PreorderTraversal( BinTree BT ) {
    if(BT) {
        printf(" %d", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}

void InorderTraversal( BinTree BT ) {  
    if(BT) {
        InorderTraversal(BT->Left);
        printf(" %d", BT->Data);
        InorderTraversal(BT->Right);
    }
} 

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );

int main() {
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->Data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");

    return 0;
}

BinTree Insert( BinTree BST, ElementType X ) {
    if(!BST) {
        BST = (BinTree)malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
    }
    else if(X < BST->Data)
        BST->Left = Insert(BST->Left, X);
    else if(X > BST->Data)
        BST->Right = Insert(BST->Right, X);
    return BST;
}

BinTree Delete( BinTree BST, ElementType X ) {
    Position Temp;
    if(!BST) {
        printf("Not Found\n");   
    }
    else if(X < BST->Data)
        BST->Left = Delete(BST->Left, X);
    else if(X > BST->Data)
        BST->Right = Delete(BST->Right, X);
    // X is found
    else if(BST->Left && BST->Right) { // X has both left and right tree
        Temp = FindMin(BST->Right);
        BST->Data = Temp->Data;
        BST->Right = Delete(BST->Right, BST->Data);
    }
    else { // X no left or right tree
        Temp = BST;
        if(!BST->Left) // no left son
            BST = BST->Right;
        else if(!BST->Right) // no right tree
            BST = BST->Left;
        free(Temp);
    }
    return BST;
}

Position Find( BinTree BST, ElementType X ) {
    while(BST) {
        if(X > BST->Data)
            BST = BST->Right;
        else if(X < BST->Data)
            BST = BST->Left;
        else
            return BST;
    }
    return NULL;
}

Position FindMin( BinTree BST ) {
    if(BST) {
        while(BST->Left)
            BST = BST->Left;
    }
    return BST;
}

Position FindMax( BinTree BST ) {
    if(!BST) return NULL;
    else if(!BST->Right)
        return BST;
    else
        return FindMax(BST->Right);
}
