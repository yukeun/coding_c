#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int N, M;   // 1 <= N <= 500,000, 1 <= M <= 500,000
int card[500010] = {0,};
int card2[500010] = {0,};
int result[500010] = {0,};
int static comp(int *first, int* second){
    if ((*(int*)first) > (*(int*)second)) return 1;
    else return -1;
}
void Inputdata(void){
    scanf(" %d", &N);
    for(int i = 0; i < N; i++){
        scanf(" %d", &card[i]);
    }
    scanf(" %d", &M);
    for(int i = 0; i < M; i++){
        scanf(" %d", &card2[i]);
    }
    qsort(card, N, sizeof(card[0]), comp);
}

int lower_bound(int index){
    int start = 0;
    int end = N - 1;
    int target = card2[index];
    while(start < end){
        int mid = (start + end ) / 2;
        if(card[mid] < target){
            start = mid + 1;
        }
        else end = mid;
    }
    return end;
}
int upper_bound(int index){
    int start = 0;
    int end = N - 1;
    int target = card2[index];
    while(start < end){
        int mid = (start + end ) / 2;
        if(card[mid] <= target){
            start = mid + 1;
        }
        else end = mid;
    }
    if(card[end] == target) return end + 1;
    else return end;
}

int main(void){
    Inputdata();
    for(int i = 0; i < M; i++){
        int lower = lower_bound(i);
        int upper = upper_bound(i);
        printf("%d ", upper - lower);
    }
    return 0;
}