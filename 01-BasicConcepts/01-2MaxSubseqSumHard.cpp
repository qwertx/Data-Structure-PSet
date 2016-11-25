#include <iostream>

int MaxSubSumLinear(int A[], int N){
    int ThisSum = 0, MaxSum = 0, left, currentLeft = A[0], right;
    for(int i = 0; i < N; i++){
        ThisSum += A[i];      
        if(ThisSum > MaxSum){
            MaxSum = ThisSum;
            left = currentLeft;
            right = A[i];
        } 
        else if(ThisSum < 0){
            ThisSum = 0;       
            currentLeft = A[i+1];
        }   
    }
    
    if(MaxSum == 0){
        left = A[0];
        right = A[N-1];
        for(int i = 0; i < N; i++){
            if(A[i] == 0){
                left = 0;
                right = 0;
                break;
            }
        }
    }
    std::cout << MaxSum << ' ' << left << ' ' << right;   
}

int main() {
    int K;
    std::cin >> K;
    if(K < 0 || K > 10000) return -1;
    int *arr = new int[K];
    for(int i = 0; i < K; i++){
        std::cin >> arr[i];
    }
    MaxSubSumLinear(arr, K);
    delete []arr;
    return 0;
}
