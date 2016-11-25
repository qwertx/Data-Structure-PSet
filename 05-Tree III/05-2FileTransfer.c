#include <stdio.h>

#define MaxSize 10000
typedef int ElementType;
typedef int SetName;
typedef ElementType SetType[MaxSize];

SetName Find(SetType S, ElementType X) { // all elements are initialized to -1 by default
    for( ; S[X] >= 0; X = S[X])
        ;
    return X;
}

SetName Find2(SetType S, ElementType X) { // path compressed with recursion
    if(S[X] < 0)
        return X;
    else   // each node in the recursion path is attached to the root of the set so the path is compressed
        return S[X] = Find2(S, S[X]); // find the root and assign to X's father node and then return
}

void Union(SetType S, SetName Root1, SetName Root2) { // compare by height
    if(S[Root2] < S[Root1]) // root2 is higher than root1
        S[Root1] = Root2;
    else {
        if(S[Root2] == S[Root1])
            S[Root1]--; // the height of root1 add 1
        S[Root2] = Root1;
    }
}

void Union2(SetType S, SetName Root1, SetName Root2) { // compare by size
    if(S[Root2] < S[Root1]) { // root2 is larger than root1
        S[Root2] += S[Root1];
        S[Root1] = Root2;
    }
    else {
        S[Root1] += S[Root2];
        S[Root2] = Root1;
    }
}

void Initialization(SetType S, int n) {
    int i;
    for(i = 0; i < n; i++)
        S[i] = -1;
}

void Input_connection(SetType S) {
    ElementType u, v;
    SetName Root1, Root2;
    scanf("%d %d", &u, &v);
    Root1 = Find(S, u-1); // SetType index begins from 0
    Root2 = Find(S, v-1);
    if(Root1 != Root2)
        Union(S, Root1, Root2);
}

void Check_connection(SetType S) {
    ElementType u, v;
    SetName Root1, Root2;
    scanf("%d %d", &u, &v);
    Root1 = Find(S, u-1);
    Root2 = Find(S, v-1);
    if(Root1 == Root2)
        printf("yes\n");
    else
        printf("no\n");
}

void Check_network(SetType S, int n) {
    int i, counter = 0;
    for(i = 0; i < n; i++) {
        if(S[i] < 0)
            counter++;
    }
    if(counter == 1)
        printf("The network is connected.\n");
    else
        printf("There are %d components.\n", counter);
}

int main() {
    SetType S;
    int n;
    char in;
    scanf("%d\n", &n);
    Initialization(S, n);
    do {
        scanf("%c", &in);
        switch(in) {
            case 'I': 
                Input_connection(S);
                break;
            case 'C':
                Check_connection(S);
                break;
            case 'S':
                Check_network(S, n);
                break;
        }
    } while(in != 'S');
    return 0;
}
