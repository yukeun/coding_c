#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int N = 0;
int M = 0;
/*
5
4 1 5 2 3
5
1 3 7 9 5
*/
int find[100 * 100 * 100 + 10] = {0,};
int array[100 * 100 * 100 + 10] = {0,};

int static comp(int* first, int* second){
    if ((*first) > (*second)) return 1;
    else return -1;
}

void inputData(void){
    scanf(" %d", &N);
    for(int i = 0; i < N; i++){
        scanf(" %d", &find[i]);
    }
    scanf(" %d", &M);
    for(int i = 0; i < M; i++){
        scanf(" %d", &array[i]);
    }

    qsort(find, N, sizeof(find[0]), comp);
}

int Binary_Search(int str, int dst, int target){
    int start = str;
    int end = dst;                  // 첨 시작은 최소, 최대 인덱스로 지정한다.
    while(start <= end){
        int mid = (start + end) / 2;

        if (find[mid] == target) return 1;
        
        if (find[mid] > target){
            //mid를 줄여야 한다.
            end = mid - 1;
        }
        else{
            start = mid + 1;
        }
    }
    return 0;    
}



int main(void){
    inputData();
    for(int i = 0; i < M; i++){
        int result = Binary_Search(0, N-1, array[i]);
        printf("%d\n", result);
    }
    return 0;
}