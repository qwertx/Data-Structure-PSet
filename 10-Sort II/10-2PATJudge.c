#include <stdio.h>
#include <stdlib.h>

struct UserNode {
    int perfect;
    int total;
    int PSet[5];
    int answered;
};
typedef struct UserNode *User;

typedef struct SNode *PtrToSNode;
struct SNode {
    int id;
    PtrToSNode next;
};

// bucket head
typedef struct HeadNode *Bucket;
struct HeadNode {
    PtrToSNode head, current;
};

int FullMarks[5];

void Initialize(User U) {
    int i;
    U->perfect = 0;
    U->total = -1;
    U->answered = 0;
    for(i = 0; i < 5; i++)
        U->PSet[i] = -1; // -1 represent never submitted
}

void ReadData(User *A) {
    int id, Problem, score;
    scanf("%d %d %d", &id, &Problem, &score);
    id--;
    Problem--;
    if(score != -1 && ((*A)[id].answered == 0))
        (*A)[id].answered = 1;
    if(score == -1) // did not pass compiler
        score = 0;
    if((*A)[id].total == -1 && ((*A)[id].answered == 1)) // no total scores yet
        (*A)[id].total = 0;
    if((*A)[id].PSet[Problem] == FullMarks[Problem]) // has got the FullMarks
        return;
    if((*A)[id].PSet[Problem] == -1) { // never submit this problem before
        (*A)[id].PSet[Problem] = score;
        (*A)[id].total += score;
    }
    if((*A)[id].PSet[Problem] < score) { // update current score and total score
        (*A)[id].total -= (*A)[id].PSet[Problem];
        (*A)[id].PSet[Problem] = score;
        (*A)[id].total += score;
    }
    if(score == FullMarks[Problem])
        (*A)[id].perfect++;
}

void Insert(User A[], Bucket B, int id) {
    PtrToSNode tmp;
    int perfect;
    tmp = (PtrToSNode)malloc(sizeof(struct SNode));
    tmp->id = id;
    if(B->head == NULL) {
        tmp->next = NULL;
        B->head = tmp;
        B->current = tmp;
        return;
    }
    B->current = B->head;
    perfect = (*A)[id].perfect;
    // compare with head
    if(perfect > ((*A)[B->head->id].perfect)) {
        tmp->next = B->head;
        B->head = tmp;
        return;
    }
    if(perfect == ((*A)[B->head->id].perfect) && id < B->head->id) {
        tmp->next = B->head;
        B->head = tmp;
        return;
    }
    // filter down
    // sort by perfectly solved problems
    while(B->current->next != NULL && perfect < ((*A)[B->current->next->id].perfect))
        B->current = B->current->next;
    // sort by id
    while(B->current->next != NULL && perfect == ((*A)[B->current->next->id].perfect) && id > B->current->next->id)
        B->current = B->current->next;
    // insert after current
    tmp->next = B->current->next;
    B->current->next = tmp;
}

int Print(User A[], Bucket B, int rank, int NoP) {
    int id, i, rankcount = 0;
    B->current = B->head;
    while(B->current != NULL) {
        id = B->current->id;
        printf("%d %05d %d", rank, id + 1, (*A)[id].total);
        for(i = 0; i < NoP; i++) {
            if((*A)[id].PSet[i] == -1)
                printf(" -");
            else
                printf(" %d", (*A)[id].PSet[i]);
        }
        printf("\n");
        B->current = B->current->next;
        rankcount++;
    }
    return rankcount;
}

void Sort(User A[], int f, int N, int NoP) {
    int i, rank = 1, rankcount, total;
    Bucket B;
    f++;
    B = (Bucket)malloc(f * sizeof(struct HeadNode));
    // initialize buckets
    for(i = 0; i < f; i++) {
        B[i].head = NULL;
        B[i].current = NULL;
    }
    // insert and sort
    for(i = 0; i < N; i++) {
        total = (*A)[i].total;
        if(total == -1 || ((*A)[i].answered == 0))
            continue;
        Insert(A, &B[total], i);
    }
    // print
    for(i = f - 1; i >= 0; i--) {
        if(B[i].head == NULL)
            continue;
        rankcount = Print(A, &B[i], rank, NoP);
        rank += rankcount;
    }
    free(B);
}

int main() {
    int NoU, NoP, NoS; // number of users, problems and submittions
    int full = 0, i;
    scanf("%d %d %d", &NoU, &NoP, &NoS);
    User A;
    A = (User)malloc(NoU * sizeof(struct UserNode));
    // initialization
    for(i = 0; i < NoU; i++)
        Initialize(&A[i]);
    // read scores
    for(i = 0; i < NoP; i++) {
        scanf("%d", &FullMarks[i]);
        full += FullMarks[i];
    }
    // read user data
    for(i = 0; i < NoS; i++)
        ReadData(&A);
    // Sort the data and print
    Sort(&A, full, NoU, NoP);
    free(A);
    return 0;
}
