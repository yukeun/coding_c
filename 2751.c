#include <stdio.h>
#include <stdlib.h>

int N;
int arr[1000010];

int static comp(void *first, void *second){
    int a = (*(int*)first);
    int b = (*(int*)second);
    if (a > b)return 1;
    else return -1;
}

void InputData(void){
    scanf(" %d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &arr[i]);
    }
    qsort(arr, N, sizeof(arr[0]), comp);
}

int main(void){
    InputData();
    for(int i = 0; i < N; i++){
        printf("%d\n", arr[i]);
    }
    return 0;
}