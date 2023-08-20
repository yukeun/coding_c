#include <stdio.h>

int N;
int X[100+10];
int Y[100+10];
void InputData(void){
    scanf("%d", &N);
    for (int i=0; i<N; i++){
        scanf("%d %d", &X[i], &Y[i]);
    }
}

struct Celcius{
    int low;
    int high;
};

struct Celcius bucket[100 * 100 * 100 + 10];
struct Celcius ref[100 * 100 * 100 + 10];

int static comp(struct Celcius *first, struct Celcius *second){
    if ((*(first)).high > (*(second)).high) return 1;
    else  return -1;
}

void init_sort(void){
    for(int i = 0; i < N; i++){
        bucket[i].low = X[i];
        bucket[i].high = Y[i];
    }
    qsort(bucket, N, sizeof(bucket[0]), comp);
    // printf("After Sorting...\n");
    for(int i = 0; i < N; i++){
        // printf("bucket[%d] low : %d, high : %d\n", i, bucket[i].low, bucket[i].high);
    }

}

int Solve(void){
    int cnt = 1;
    ref[0] = bucket[0];

    for(int i = cnt; i < N; i++){
        if(bucket[i].low > ref[cnt-1].high){
            ref[cnt] = bucket[i];
            cnt++;
        }
    }
    return cnt;
}

int main(void){
    int ans = -1;

    InputData();// 입력받는 부분
    init_sort();
    // 여기서부터 작성
    ans = Solve();

    printf("%d\n", ans);// 출력하는 부분
    return 0;
}