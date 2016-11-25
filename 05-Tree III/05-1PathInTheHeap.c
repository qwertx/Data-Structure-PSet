#define MAXN 1001
#define MINH -10001

int H[MAXN], size;

void Create() {
    size = 0;
    H[0] = MINH; // sentinal
}

void Insert(int X) {
    int i;
    for(i = ++size; H[i/2] > X; i /= 2) // add 1 to size and trace up to compare
        H[i] = H[i/2]; // move father node down
    H[i] = X;
}

int main() {
    int n, m, x, i, j;
    scanf("%d %d", &n, &m);
    Create();
    for(i = 0; i < n; i++) {
        scanf("%d", &x);
        Insert(x);
    }
    // search and print
    for(i = 0; i < m; i++) {
        scanf("%d", &j);
        printf("%d", H[j]);
        while(j > 1) { // until root
            j /= 2;
            printf(" %d", H[j]);
        }
        printf("\n");
    }
    return 0;
}
