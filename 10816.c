/*
10
6 3 2 10 10 10 -10 -10 7 3
8
10 9 -5 2 3 4 5 -10
*/
#include <stdio.h>
#include <stdlib.h>

int N;
int sang_card[500010] = {0,};
int M;
int arr[500010] = {0,};

int static comp(void *first, void *second){
    int a = (*(int *)first);
    int b = (*(int *)second);
    if (a > b) return 1;
    else return -1;
}

void InputData(void){
    scanf(" %d", &N);
    for(int i = 0; i < N; i++){
        scanf(" %d", &sang_card[i]);
    }
    scanf(" %d", &M);
    for(int i = 0; i < M; i++){
        scanf(" %d", &arr[i]);
    }

    qsort(sang_card, N, sizeof(sang_card[0]), comp);
}

int lower_bound(int target){
    // target 이상의 값이 나오는 최소 위치
    int start = 0;
    int end = N-1;
    while(end - start > 0){
        int mid = (start + end) / 2;
        if(sang_card[mid] >= target){
            end = mid;
        }
        else start = mid + 1;
    }
    return end;
}
int upper_bound(int target){
    int start = 0;
    int end = N - 1;
    while(end - start > 0){
        int mid = (start + end) / 2;
        if(sang_card[mid] > target){
            end = mid;
        }
        else start = mid + 1;
    }
    if (sang_card[end] == target){
        return end + 1;
    }
    else return end;
}


int main(void){
    InputData();
    for(int i = 0; i < M; i++){
        int target = arr[i];
        int lower_idx = lower_bound(target);
        int upper_idx = upper_bound(target);
        printf("%d ", upper_idx - lower_idx);
    }
    return 0;
}
