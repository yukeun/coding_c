#include <stdio.h>
#define MAXN ((int)1e5)
int N;//영화수
typedef struct{
    int s, e;
}DATA;

DATA bucket[MAXN + 10];
DATA A[MAXN + 10];

int static comp(DATA *first, DATA *second){
    if ((*(first)).e > (*(second)).e) return 1;
    else return -1;
}

void init_sort(void){
    qsort(A, N, sizeof(A[0]), comp);
    /*for(int i = 0; i < N; i++){
        printf("A[%d] s : %d, e : %d\n", i, A[i].s, A[i].e);
    }*/
}
void InputData(void){
    scanf("%d", &N);
    for (int i=0; i<N; i++){
        scanf("%d %d", &A[i].s, &A[i].e);
    }
}

int Solve(void){
    int cnt = 0;
    bucket[0].s = 0;
    bucket[0].e = 0;                            // 초기화
    for(int i = 0; i < N; i++){
        int time = A[i].e - A[i].s;             // 상영시간
        if (time >= 2 && A[i].s >= bucket[cnt].e){
            bucket[cnt+1].s = A[i].s;
            bucket[cnt+1].e = A[i].e;
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