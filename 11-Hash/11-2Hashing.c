#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXTABLESIZE 100000
typedef int ElementType;
typedef int Index;
typedef Index Position;

typedef enum {
    Legitimate, Empty, Deleted
} EntryType;

typedef struct HashEntry Cell;
struct HashEntry {
    ElementType Data;
    EntryType Info;
};

typedef struct TblNode *HashTable;
struct TblNode {
    int TableSize;
    Cell *Cells;
};

int flag = 1; // if the first print

int NextPrime(int N) {
    // the min prime number > N but <= MAXTABLESIZE
    int i, p = (N % 2) ? (N + 2) : (N + 1);
    if(N == 1)
        return 2;
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

HashTable CreateTable (int TableSize) {
    HashTable H;
    int i;
    H = (HashTable)malloc(sizeof(struct TblNode));
    // find table size
    H->TableSize = NextPrime(TableSize);
    H->Cells = (Cell*)malloc(H->TableSize * sizeof(Cell));
    for(i = 0; i < H->TableSize; i++)
        H->Cells[i].Info = Empty; // empty is 1
    return H;
}

int Hash(ElementType Key, int size) {
    return Key % size;
}

Position Find(HashTable H, ElementType Key) {
    // Quadratic Probing
    Position CurrentPos, NewPos;
    int CNum = 0; // time of conflict
    NewPos = CurrentPos = Hash(Key, H->TableSize);
    while(H->Cells[NewPos].Info != Empty && H->Cells[NewPos].Data != Key && CNum < 10000) {
        CNum++;
        NewPos = CurrentPos + CNum * CNum;
        if(NewPos >= H->TableSize)
            NewPos = NewPos % H->TableSize;
    }
    if(H->Cells[NewPos].Info == Legitimate)
        return -1;
    else
        return NewPos;
}

void Insert(HashTable H, ElementType Key) {
    Position Pos = Find(H, Key);
    if(Pos != -1) {
        H->Cells[Pos].Info = Legitimate;
        H->Cells[Pos].Data = Key;
        if(flag == 1) {
            printf("%d", Pos);
            flag = 0;
            return;
        }
        else {
            printf(" %d", Pos);
            return;
        }
    }
    else {
        printf(" -");
        return;
    }
}

int main() {
    int M, N, i, tmp;
    HashTable H;
    scanf("%d %d", &M, &N);
    H = CreateTable(M);
    for(i = 0; i < N; i++) {
        scanf("%d", &tmp);
        Insert(H, tmp);
    }
    return 0;
}
