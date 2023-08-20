#include <stdio.h>
#include <stdlib.h>
int N;
int S[10000+10];
int E[10000+10];
int present;                    // 도서관 최장시간
int absent;                     // 도서관x 최장시간

void InputData(void){
    scanf("%d", &N);
    for (int i=0; i<N; i++){
        scanf("%d %d", &S[i], &E[i]);
    }
}

struct student{
    int start;
    int end;
};

int static comp(struct student* first, struct student* second){
    if ((*(first)).start > (*(second)).start) return 1;
    else return -1;
}

struct student bucket[100 * 100 * 100 + 10];

void init_sort(void){
    for(int i=0; i < N; i++){
        bucket[i].start = S[i];
        bucket[i].end = E[i];
    }
    qsort(bucket, N, sizeof(bucket[0]), comp);
    /*or(int i =0; i < N; i++){
        printf("bucket[%d] start : %d, end : %d\n", i, bucket[i].start, bucket[i].end);
    }*/
}

void Solve(void){
    int current_time = 0;
    int absent_time = 0;
    // 참고로 result에는 현재 카운트 되는 시간만을 담는다
    // 먼저 제일 앞에있는 것 부터...
    int cur_start = bucket[0].start;
    int cur_end = bucket[0].end;
    current_time = cur_end - cur_start;
    if(current_time > present) present = current_time;          // 초반에 갱신해주기
    for(int i = 1; i < N; i++){
        if(bucket[i].start > cur_end){
            absent_time = (bucket[i].start - cur_end);
            cur_start = bucket[i].start;
            cur_end = bucket[i].end;
            current_time = cur_end - cur_start;
        }
        else{
            if (cur_end >= bucket[i].end) continue;
            else{
                current_time += (bucket[i].end - cur_end);
                cur_end = bucket[i].end;
            }
            
        }
        if (current_time > present) present = current_time;
        if (absent_time > absent) absent = absent_time;
    }
}

int main(void){
    InputData();// 입력받는 부분
    init_sort();
    // 여기서부터 작성
    Solve();
    printf("%d %d\n", present, absent);// 출력하는 부분
    return 0;
}