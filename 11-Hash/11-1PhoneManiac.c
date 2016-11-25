#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXD 5 // the number of char used in Hash()
#define MAXTABLESIZE 1000000
#define KEYLENGTH 11
typedef char ElementType[KEYLENGTH + 1]; // end of string is '\0'
typedef int Index;

typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
    int Count;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

typedef struct TblNode *HashTable;
struct TblNode {
    int TableSize;
    List Heads;
};

int NextPrime(int N) {
    // the min prime number > N but <= MAXTABLESIZE
    int i, p = (N % 2) ? (N + 2) : (N + 1);
    while(p <= MAXTABLESIZE) {
        for(i = (int)sqrt(p); i > 2; i--) {
	    if(!(p % i))
	        break; // p is not a prime
	}
	if(i == 2)
	    break; // p is a prime
	else
	    p += 2; // next number
    }
    return p;
}

HashTable CreateTable(int TableSize) {
    HashTable H;
    int i;
    H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = NextPrime(TableSize);
    H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode));
    for(i = 0; i < H->TableSize; i++) {
        H->Heads[i].Data[0] = '\0';
        H->Heads[i].Next = NULL;
        H->Heads[i].Count = 0;
    }
    return H;
}

int Hash(int Key, int P) {
    return Key % P;
}

Position Find(HashTable H, ElementType Key) {
    Position P;
    Index Pos;
    Pos = Hash(atoi(Key + KEYLENGTH - MAXD), H->TableSize); // convert string into number
    P = H->Heads[Pos].Next;
    while(P && strcmp(P->Data, Key))
        P = P->Next;
    return P; // return NULL if not found
}

void Insert(HashTable H, ElementType Key) {
    Position P, NewCell;
    Index Pos;
    P = Find(H, Key);
    if(!P) { // not found
        NewCell = (Position)malloc(sizeof(struct LNode));
        strcpy(NewCell->Data, Key); // copy Key into NewCell->Data
        NewCell->Count = 1;
        Pos = Hash(atoi(Key + KEYLENGTH - MAXD), H->TableSize);
        // insert NewCell into List Head
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell;
        return;
    }
    else {
        P->Count++;
        return;
    }
}

void DestroyTable(HashTable H) {
    int i;
    Position P, Tmp;
    for(i = 0; i < H->TableSize; i++) {
        P = H->Heads[i].Next;
        while(P) {
            Tmp = P->Next;
            free(P);
            P = Tmp;
        }
    }
    free(H->Heads);
    free(H);
}

void ScanAndOutput(HashTable H) {
    int i, MaxCnt = 0, PCnt = 0;
    ElementType MinPhone;
    List Ptr;
    MinPhone[0] = '\0'; // empty string
    // scan the table
    for(i = 0; i < H->TableSize; i++) {
        Ptr = H->Heads[i].Next;
        while(Ptr) {
            if(Ptr->Count > MaxCnt) { // update max count
                MaxCnt = Ptr->Count;
                strcpy(MinPhone, Ptr->Data);
                PCnt = 1; // number of persons with max call count
            }
            else if(Ptr->Count == MaxCnt) {
                PCnt++;
                if(strcmp(MinPhone, Ptr->Data) > 0) // update the smallest phone number
                    strcpy(MinPhone, Ptr->Data);
            }
            Ptr = Ptr->Next;
        }
    }
    printf("%s %d", MinPhone, MaxCnt);
    if(PCnt > 1)
        printf(" %d", PCnt);
    printf("\n");
}

int main() {
    int N, i;
    ElementType Key;
    HashTable H;
    scanf("%d", &N);
    H = CreateTable(N * 2);
    for(i = 0; i < N; i++) {
        scanf("%s", Key);
        Insert(H, Key);
        scanf("%s", Key);
        Insert(H, Key);
    }
    ScanAndOutput(H);
    DestroyTable(H);
    return 0;
}
