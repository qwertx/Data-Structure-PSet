#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct PolyNode* Polynomial;
struct PolyNode {
    int coef;
    int expon;
    Polynomial link;
};

void Attach(int c, int e, Polynomial *pRear) {
    Polynomial P;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->coef = c;
    P->expon = e;
    P->link = NULL;
    (*pRear)->link = P;
    *pRear = P;
}

Polynomial ReadPoly() {
    Polynomial P, Rear, t;
    int N, c, e;
    scanf("%d", &N); // numbers of elements
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;  // Rear points to an empty node at first
    while(N--) {
        scanf("%d %d", &c, &e);
        Attach(c, e, &Rear);
    }
    // delete the empty node
    t = P; 
    P = P->link;
    free(t);
    return P;
}

Polynomial Add(Polynomial P1, Polynomial P2) {
    Polynomial P, Rear, t1, t2, t;
    int sum;
    t1 = P1;
    t2 = P2;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;
    while(t1 && t2) {
        if(t1->expon == t2->expon) {
            sum = t1->coef + t2->coef;
            if(sum)
                Attach(sum, t1->expon, &Rear);
            t1 = t1->link;
            t2 = t2->link;
        }
        else if(t1->expon > t2->expon) {
            Attach(t1->coef, t1->expon, &Rear);
            t1 = t1->link;
        }
        else {
            Attach(t2->coef, t2->expon, &Rear);
            t2 = t2->link;
        }
    }
    while(t1) {
        Attach(t1->coef, t1->expon, &Rear);
        t1 = t1->link;
    }
    while(t2) {
        Attach(t2->coef, t2->expon, &Rear);
        t2 = t2->link;
    }
    t = P; 
    P = P->link;
    free(t);
    return P;
}

Polynomial Multi(Polynomial P1, Polynomial P2) {
    Polynomial P, Rear, t1, t2, t;
    int c, e;
    if(!P1 || !P2) // P1 or P2 is empty
        return NULL;
    t1 = P1;
    t2 = P2;
    P = (Polynomial)malloc(sizeof(struct PolyNode)); // temp empty node for Rear to point to at first
    P->link = NULL;
    Rear = P;
    while(t2) { // the first element of P1 times P2 and we get P
        Attach(t1->coef * t2->coef, t1->expon + t2->expon, &Rear);
        t2 = t2->link;
    }
    t1 = t1->link;
    while(t1) {
        t2 = P2; // back to the start position of P2
        Rear = P; // back to the start position of P
        while(t2) {
            e = t1->expon + t2->expon;
            c = t1->coef * t2->coef;
            while(Rear->link && (Rear->link->expon > e)) // move forward and find the insert position
                Rear = Rear->link;
            if(Rear->link && Rear->link->expon == e) { // same exponents
                if(Rear->link->coef + c) // not zero
                    Rear->link->coef += c;
                else {
                    t = Rear->link;
                    Rear->link = t->link;
                    free(t);
                }
            }
            else {
                t = (Polynomial)malloc(sizeof(struct PolyNode));
                t->coef = c;
                t->expon = e;
                t->link = Rear->link;
                Rear->link = t;
                Rear = Rear->link;
            }
            t2 = t2->link;
        }
        t1 = t1->link;
    }
    // delete the first empty node
    t2 = P;
    P = P->link;
    free(t2);
    return P;
}

void PrintPoly(Polynomial P) {
    int flag = 0; // adjust the format of output
    if(!P) { // if empty
        printf("0 0\n");
        return;
    }
    while(P) {
        if(!flag) // if the first node
            flag = 1;
        else
            printf(" ");
        printf("%d %d", P->coef, P->expon);
        P = P->link;
    }
    printf("\n");
}

int main() {
    Polynomial P1, P2, PP, PS;
    P1 = ReadPoly();
    P2 = ReadPoly();
    PP = Multi(P1, P2);
    PrintPoly(PP);
    PS = Add(P1, P2);
    PrintPoly(PS);
    return 0;
}
