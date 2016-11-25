#include <iostream>

int Max3(int a, int b, int c){
    int t = a > b ? a : b;
    return c > t ? c : t;
}

int DivideAndConquer(int A[], int left, int right){
    if(left == right){
        if(A[left] > 0) return left;
        else return 0;
    }
    
    int center = (left + right) / 2;
    int maxLeftSum = DivideAndConquer(A, left, center);
    int maxRightSum = DivideAndConquer(A, center + 1, right);
    
    int maxLeftBorderSum = 0, leftBorderSum = 0;
    for(int i = center; i >= left; i--){
        leftBorderSum += A[i];
        if(leftBorderSum > maxLeftBorderSum){
            maxLeftBorderSum = leftBorderSum;
        }
    }
    
    int maxRightBorderSum = 0, rightBorderSum = 0;
    for (int j = center + 1; j <= right; j++) {
        rightBorderSum += A[j];
        if(rightBorderSum > maxRightBorderSum) {
            maxRightBorderSum = rightBorderSum;
        }
    }
    
    return Max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}

int MaxSubseqSum(int A[], int N){
    return DivideAndConquer(A, 0, N-1);    
}

int MaxSubSumLinear(int A[], int N){
    int ThisSum = 0, MaxSum = 0;
    for(int i = 0; i < N; i++){
        ThisSum += A[i];
        if(ThisSum > MaxSum)
            MaxSum = ThisSum;
        else if(ThisSum < 0)
            ThisSum = 0;
    }
    return MaxSum;   
}

int main() {
    int K;
    std::cin >> K;
    if(K <= 0 || K > 100000) return -1;
    int *arr = new int[K];
    for(int i = 0; i < K; i++){
        std::cin >> arr[i];
    }
    std::cout << MaxSubSumLinear(arr, K);
    delete []arr;
    return 0;
}
