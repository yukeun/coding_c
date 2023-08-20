#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N = 0;              // 나무 개수
long long M = 0;              // 필요한 나무길이의 합
int tree[100 * 100 * 100 + 10] = {0,};
int result = 0;

int static comp(int *first, int *second){
    if ((*first) > (*second)) return 1;
    else return -1;
}

void InputData(void){
    scanf(" %d", &N);
    scanf(" %lld", &M);
    for(int i = 0; i < N; i++){
        scanf(" %d", &tree[i]);
    }

    qsort(tree, N, sizeof(tree[0]), comp);
}

int cut(int high){
    long long sum = 0;
    int cut_result = 0;
    for(int i = 0; i < N; i++){
        cut_result = tree[i] - high;
        if (cut_result <= 0) continue;
        sum += cut_result;
    }

    if (sum < M) return 0;
    if (sum > M) return 2;
    if (sum == M) return 1;
}

void Binary_Search(int min, int max){
    int start = min;
    int end = max;
    while(start <= end){
        int mid = (start + end) / 2;
        int temp = cut(mid);
        //printf("mid : %d\n", mid);
        if(temp == 1){
            result = mid;
            return;
        }
        if(temp == 2){
            result = mid;
            start = mid + 1;
        }
        else end = mid - 1;
    }
}

int main(void){
    InputData();
    Binary_Search(0, tree[N-1]);
    printf("%d\n", result);
    return 0;
}