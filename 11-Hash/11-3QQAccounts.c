#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXTABLESIZE 1000000

typedef struct LNode *PtrToLNode;
struct LNode {
    long long number;
    char pwd[17];
    PtrToLNode Next;
};
typedef PtrToLNode Account;
typedef PtrToLNode List;

typedef struct TblNode *HashTable;
struct TblNode {
    int TableSize;
    List Heads;
};

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

HashTable CreateTable(int TableSize) {
    HashTable H;
    int i;
    H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = NextPrime(TableSize);
    H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode));
    for(i = 0; i < H->TableSize; i++) {
        H->Heads[i].pwd[0] = '\0';
        H->Heads[i].number = 0;
        H->Heads[i].Next = NULL;
    }
    return H;
}

int Hash(int Key, int P) {
    return Key % P;
}

Account Find(HashTable H, long long AccNum) {
    Account P;
    int Pos;
    Pos = Hash(AccNum, H->TableSize); // convert string into number
    P = H->Heads[Pos].Next;
    while(P && (P->number != AccNum))
        P = P->Next;
    return P; // return NULL if not found
}

void DestroyTable(HashTable H) {
    int i;
    Account P, Tmp;
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

void NewAccount(HashTable H, long long AccNum, char pwd[]) {
    Account P, NewCell;
    int Pos;
    P = Find(H, AccNum);
    if(!P) { // not found
        NewCell = (Account)malloc(sizeof(struct LNode));
        strcpy(NewCell->pwd, pwd);
        NewCell->number = AccNum;
        Pos = Hash(AccNum, H->TableSize);
        // insert NewCell into List Head
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell;
        printf("New: OK\n");
        return;
    }
    else {
        printf("ERROR: Exist\n");
        return;
    }
}

void Login(HashTable H, long long AccNum, char pwd[]) {
    Account P;
    P = Find(H, AccNum);
    if(!P) { // not found
        printf("ERROR: Not Exist\n");
        return;
    }
    else if(!strcmp(pwd, P->pwd)) {
        printf("Login: OK\n");
        return;
    }
    else {
        printf("ERROR: Wrong PW\n");
        return;
    }
}

int main() {
    int i, N;
    char inst;
    long long AccNum;
    char pwd[17];
    HashTable H;
    scanf("%d\n", &N);
    H = CreateTable(N);
    for(i = 0; i < N; i++) {
        scanf("%c %lld %s", &inst, &AccNum, pwd);
        switch(inst) {
            case 'L':
                Login(H, AccNum, pwd);
                break;
            case 'N':
                NewAccount(H, AccNum, pwd);
                break;
        }
        if(i != N - 1)
            scanf("\n");
    }
    DestroyTable(H);
    return 0;
}
