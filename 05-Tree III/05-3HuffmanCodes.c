#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definition of Huffman Tree
typedef struct TreeNode *HuffmanTree;
struct TreeNode {
    int Weight;
    HuffmanTree Left, Right;
};

// definition of MinHeap
typedef struct HeapStruct *MinHeap;
struct HeapStruct {
    HuffmanTree Elements;
    int Size;
};

void Assign(HuffmanTree a, HuffmanTree b) {
    a->Weight = b->Weight;
    a->Left = b->Left;
    a->Right = b->Right;
}

// MinHeap
MinHeap Create(int MaxSize) {
    MinHeap H = malloc(sizeof(struct HeapStruct));
    H->Elements = malloc((MaxSize + 1) * sizeof(struct TreeNode));
    H->Size = 0;
    H->Elements[0].Weight = -1; // the sentinel
    return H;
}

void Insert(MinHeap H, HuffmanTree item) {
    int i;
    i = ++H->Size;
    for( ; H->Elements[i/2].Weight > item->Weight; i /= 2)
        Assign(&(H->Elements[i]), &(H->Elements[i/2]));
    Assign(&(H->Elements[i]), item);
}

HuffmanTree DeleteMin(MinHeap H) {
    int Parent, Child;
    HuffmanTree MinItem, temp;
    MinItem = (HuffmanTree)malloc(sizeof(struct TreeNode));
    temp = (HuffmanTree)malloc(sizeof(struct TreeNode));
    Assign(MinItem, &(H->Elements[1]));
    Assign(temp, &(H->Elements[H->Size--]));
    for(Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
        Child = Parent * 2;
        if((Child != H->Size) && (H->Elements[Child].Weight > H->Elements[Child+1].Weight))
            Child++;  // Child is the smaller element of parents' two sons
        if(temp->Weight <= H->Elements[Child].Weight)
            break;
        else
            Assign(&(H->Elements[Parent]), &(H->Elements[Child]));
    }
    Assign(&(H->Elements[Parent]), temp);
    return MinItem;
}

void PercDown(MinHeap H, int p) { // the root is H->Elements[p]
    int Parent, Child;
    HuffmanTree X;
    X = (HuffmanTree)malloc(sizeof(struct TreeNode));
    Assign(X, &(H->Elements[p]));
    for(Parent = p; Parent * 2 <= H->Size; Parent = Child) {
        Child = Parent * 2;
        if((Child != H->Size) && (H->Elements[Child].Weight > H->Elements[Child+1].Weight))
            Child++;
        if(X->Weight <= H->Elements[Child].Weight)
            break;
        else
            Assign(&(H->Elements[Parent]), &(H->Elements[Child]));
    }
    Assign(&(H->Elements[Parent]), X);
}

void BuildHeap(MinHeap H) {
    // presume that the elements are all in the H->Elements[]
    int i;
    for(i = H->Size / 2; i > 0; i--) {
        PercDown(H, i); // from the last parent node to the root
    }
}

HuffmanTree Huffman(MinHeap H) {
    int i, j, N = H->Size;
    HuffmanTree T;
    for(i = 1; i < N; i++) {
        T = (HuffmanTree)malloc(sizeof(struct TreeNode));
        T->Left = DeleteMin(H);
        T->Right = DeleteMin(H);
        T->Weight = T->Left->Weight + T->Right->Weight;
        Insert(H, T);
    }
    T = DeleteMin(H);
    return T;
}

int WPL(HuffmanTree T, int Depth) {
    if(!T->Left && !T->Right)
        return (Depth * T->Weight);
    else
        return (WPL(T->Left, Depth + 1) + WPL(T->Right, Depth + 1));
}

int InsertData(HuffmanTree T, char code[]) {
    HuffmanTree tmp = T, NewNode;
    int cnt = 0;
    while(code[cnt] != '\0') {
        if(tmp->Weight == 1)
            return 0;
        if(code[cnt] == '0') {
            if(code[cnt+1] == '\0' && (tmp->Left != NULL)) // prefix code
                return 0;
            if(tmp->Left == NULL) {
                NewNode = malloc(sizeof(struct TreeNode));
                NewNode->Left = NULL;
                NewNode->Right = NULL;
                if(code[cnt+1] == '\0')
                    NewNode->Weight = 1;
                else
                    NewNode->Weight = 0;
                tmp->Left = NewNode;
                tmp = NewNode;
            }
            else if(tmp->Left != NULL)
                tmp = tmp->Left;
        }
        else if(code[cnt] == '1') {
            if(code[cnt+1] == '\0' && (tmp->Right != NULL)) // prefix code
                return 0;
            if(tmp->Right == NULL) {
                NewNode = malloc(sizeof(struct TreeNode));
                NewNode->Left = NULL;
                NewNode->Right = NULL;
                if(code[cnt+1] == '\0')
                    NewNode->Weight = 1;
                else
                    NewNode->Weight = 0;
                tmp->Right = NewNode;
                tmp = NewNode;
            }
            else if(tmp->Right != NULL)
                tmp = tmp->Right;
        }
        cnt++;
    }
    return 1;
}

int ReadDataAndCheck(int N, int M, int j, int WPL, int Frequency[]) {
    HuffmanTree sT;
    char code[64];
    char c;
    int sWPL = 0, i, check, flag = 1;
    sT = (HuffmanTree)malloc(sizeof(struct TreeNode));
    sT->Left = NULL;
    sT->Right = NULL;
    sT->Weight = 0; // weight means if it is a leaf node here
    for(i = 0; i < N; i++) {
        if((i == N - 1) && (j == M - 1))
            scanf("%c %s", &c, code);
        else
            scanf("%c %s\n", &c, code);
        if(flag)
            sWPL += strlen(code) * Frequency[i];
            check = InsertData(sT, code);
        if(check == 0)
            flag = 0;
    }
    if(sWPL == WPL && flag)
        return 1;
    else
        return 0;
}

int main() {
    int N, i, j, iWPL, M, result;
    scanf("%d\n", &N);
    int Frequency[N];
    char Character[N];
    MinHeap H = Create(N);
    HuffmanTree T, HeapNode;
    // read characters and frequencies
    for(i = 0; i < N; i++) {
        if(i != N - 1)
            scanf("%c %d ", &Character[i], &Frequency[i]);
        else
            scanf("%c %d\n", &Character[i], &Frequency[i]);
        HeapNode = malloc(sizeof(struct TreeNode));
        HeapNode->Left = NULL;
        HeapNode->Right = NULL;
        HeapNode->Weight = Frequency[i];
        H->Elements[i+1] = *HeapNode;
        H->Size++;
    }
    // calculate WPL
    BuildHeap(H);
    T = Huffman(H);
    iWPL = WPL(T, 0);
    // read student data
    scanf("%d\n", &M);
    for(i = 0; i < M; i++) {
        result = ReadDataAndCheck(N, M, i, iWPL, Frequency);
        if(result == 1)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
