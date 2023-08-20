/*
입력
첫째 줄에는 지방의 수를 의미하는 정수 N이 주어진다. N은 3 이상 10,000 이하이다. 
다음 줄에는 각 지방의 예산요청을 표현하는 N개의 정수가 빈칸을 사이에 두고 주어진다. 
이 값들은 모두 1 이상 100,000 이하이다. 그 다음 줄에는 총 예산을 나타내는 정수 M이 주어진다. 
M은 N 이상 1,000,000,000 이하이다. 

출력
첫째 줄에는 배정된 예산들 중 최댓값인 정수를 출력한다. 

예제 입력 1 
4
120 110 140 150
485
예제 출력 1 
127
예제 입력 2 
5
70 80 30 40 100
450
예제 출력 2 
100
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int N = 0;
long long total = 0;
int area[100 * 100 * 100 + 10];
int result = 0;

int static comp(int *first, int *second){
    if ((*first) > (*second)) return 1;
    else return -1;
}

void InputData(void){
    scanf(" %d", &N);
    for(int i = 0; i < N; i++){
        scanf(" %d", &area[i]);
    }
    scanf(" %d", &total);

    //printf("N : %d, total : %d\n", N, total);
    qsort(area, N, sizeof(area[0]), comp);
}

int calculate(int cost){
    long long wallet = total;
    int red_card = 0;
    for(int i = 0; i < N; i++){

        if (area[i] <= cost){
            wallet -= area[i];
            continue;
        }
        wallet -= cost;

        if (wallet < 0){
            red_card = 1;
            break;
        }
    }
    if(red_card || wallet < 0) return 0;          // wallet이 마이너스면 0
    if(wallet > 0) return 2;        // wallet이 플러스면 2          // 얘를 답으로 임시저장하고 예산 줄이기
    if (wallet == 0) return 1;      // 예산을 적정하게 잡았으면 1
}

void Binary_Search(int min, int max){
    int start = min;
    int end = max;
    while(start <= end){
        int mid = (start + end) / 2;
        int temp_result = calculate(mid);
        if (temp_result == 1){
            result = mid;
            return;
        }
        else if (temp_result == 2){
            result = mid;
            start = mid + 1;
        }
        else end = mid - 1;
    }
}


int main(void){
    InputData();
    Binary_Search(0, area[N-1]);
    printf("%d\n", result);
    return 0;
}