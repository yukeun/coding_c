#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int K = 0;
int N = 0;
long long code[100 * 100 * 100 + 10] = {0,};
long long result = 0;

int static comp(int *first, int *second){
    if ((*first) > (*second)) return 1;
    else return -1;
}

void InputData(void){
    scanf(" %d", &K);
    scanf(" %d", &N);
    for(int i = 0; i < K; i++){
        scanf(" %lld", &code[i]);
    }
    qsort(code, K, sizeof(code[0]), comp);
}

int cut(long long mid){
    int sum = 0;
    for(int i = 0; i < K; i++){
        sum += (code[i] / mid);
        //printf("i : %d, sum : %d\n", i, sum);
    }

    if (sum == N) return 1;
    else if(sum > N) return 2;
    else return 0;
}

void Binary_Search(long long min, long long max){
    long long start = min;
    long long end = max;
    while(start <= end){
        long long mid = (start + end) / 2;
        //printf("mid : %d\n", mid);
        int temp = cut(mid);
        /*if(temp == 1){
            result = mid;
            return;
        }*/
        if(temp == 2 || temp == 1){
            result = mid;
            start = mid + 1;
        }
        else end = mid - 1;
    }
}

int main(void){
    InputData();
    Binary_Search(1, code[K-1]);
    printf("%lld\n", result);
    return 0;
}